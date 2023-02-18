#include "amalgamate.h"
#include "utils/lua_file.h"
#include "utils/lua_json.h"
#include "utils/lua_substitute.h"
#include "filter/__init__.h"
#include <string.h>
#include <stdlib.h>

static const char* s_help =
"amalgamate - Merge your source code into one big file.\n"
"Usage: amalgamate [OPTIONS] -- [FILES]\n"
"\n"
"OPTIONS:\n"
"  -h, --help\n"
"    Show this help and exit.\n"
"\n"
"  --list-filter\n"
"    List all filters and exit.\n"
"\n"
"  --out=[PATH]\n"
"    Path to output file.\n"
"\n"
"  --input=[PATH]\n"
"    Input file path.\n"
"\n"
"  --filter=[STRING|PATH]\n"
"    A sed like string to perform in all group. This string is executed after all\n"
"    `--group-substitute` is executed.\n"
"\n"
"  --verbose\n"
"    Show extra output.\n"
"\n";

static int _amalgamate_gc(lua_State* L)
{
    size_t i;
    amalgamate_ctx_t* ctx = lua_touserdata(L, 1);

    amalgamate_str_destroy(&ctx->out_path);

    if (ctx->out_file != NULL)
    {
        fclose(ctx->out_file);
        ctx->out_file = NULL;
    }

    for (i = 0; i < ctx->file_sz; i++)
    {
        free(ctx->files[i]);
        ctx->files[i] = NULL;
    }
    free(ctx->files);
    ctx->files = NULL;
    ctx->file_sz = 0;

    for (i = 0; i < ctx->filter_sz; i++)
    {
        free(ctx->filters[i]);
        ctx->filters[i] = NULL;
    }
    free(ctx->filters);
    ctx->filters = NULL;
    ctx->filter_sz = 0;

    return 0;
}

static void _amalgamate_tostring_out(lua_State* L, cJSON* json, amalgamate_ctx_t* ctx)
{
    const char* name = "out";
    lua_json_add_string_to_object(L, json, name, ctx->out_path.data);
}

static const char* _amalgamate_to_string(lua_State* L, amalgamate_ctx_t* ctx, int pretty)
{
    int sp = lua_gettop(L);

    /* SP + 1 */
    cJSON* json = lua_json_pushobject(L);

    _amalgamate_tostring_out(L, json, ctx);

    /* SP + 2 */
    const char* str = lua_json_tostring(L, json, pretty);

    /* SP + 1 */
    lua_remove(L, sp + 1);

    return str;
}

static int _amalgamate_tostring(lua_State* L)
{
    amalgamate_ctx_t* ctx = lua_touserdata(L, 1);

    _amalgamate_to_string(L, ctx, 0);
    return 1;
}

static int _setup_arg_out(lua_State* L, amalgamate_ctx_t* ctx, char* str)
{
    amalgamate_str_destroy(&ctx->out_path);
    ctx->out_path = amalgamate_str_make(L, str);
    return 0;
}

static int _setup_arg_filter_expand(lua_State* L, amalgamate_ctx_t* ctx)
{
    ctx->filter_sz++;
    size_t realloc_size = sizeof(char*) * ctx->filter_sz;
    char** new_filters = realloc(ctx->filters, realloc_size);
    if (new_filters == NULL)
    {
        return ERROR_OOM(L);
    }

    ctx->filters = new_filters;
    ctx->filters[ctx->filter_sz - 1] = NULL;

    return 0;
}

static int _setup_arg_filter(lua_State* L, amalgamate_ctx_t* ctx, char* str)
{
    char* ret = NULL;
    char* saveptr = NULL;
    while ((ret = strtok_r(str, ",", &saveptr)) != NULL)
    {
        str = NULL;
        _setup_arg_filter_expand(L, ctx);
        if ((ctx->filters[ctx->filter_sz - 1] = strdup(ret)) == NULL)
        {
            return ERROR_OOM(L);
        }
    }

    return 0;
}

static int _setup_args_expaned_files(lua_State* L, amalgamate_ctx_t* ctx)
{
    ctx->file_sz++;
    size_t realloc_size = sizeof(char*) * ctx->file_sz;
    char** new_files = realloc(ctx->files, realloc_size);
    if (new_files == NULL)
    {
        return ERROR_OOM(L);
    }

    ctx->files = new_files;
    ctx->files[ctx->file_sz - 1] = NULL;

    return 0;
}

static int _setup_arg_input(lua_State* L, amalgamate_ctx_t* ctx, char* str)
{
    char* saveptr = NULL;
    char* ret;
    while ((ret = strtok_r(str, ",", &saveptr)) != NULL)
    {
        str = NULL;
        _setup_args_expaned_files(L, ctx);
        if ((ctx->files[ctx->file_sz - 1] = strdup(ret)) == NULL)
        {
            return ERROR_OOM(L);
        }
    }

    return 0;
}

static int _setup_arg_verbose(lua_State* L, amalgamate_ctx_t* ctx, char* str)
{
    (void)L; (void)str;
    ctx->need_verbose = 1;
    return 0;
}

static int _setup_arg_list_filter(lua_State* L, amalgamate_ctx_t* ctx, char* str)
{
    (void)L; (void)str;
    ctx->need_list_filters = 1;
    return 0;
}

static int _setup_args(lua_State* L, amalgamate_ctx_t* ctx, int argc, char* argv[])
{
#define PARSER_LONGOPT_WITH_VALUE(OPT, FUNC)   \
    do {\
        int ret = -1; const char* opt = OPT;\
        size_t optlen = strlen(opt);\
        if (strncmp(argv[i], opt, optlen) == 0) {\
            if (argv[i][optlen] == '=') {\
                ret = FUNC(L, ctx, argv[i] + optlen + 1);\
            } else if (i < argc - 1) {\
                ret = FUNC(L, ctx, argv[i + 1]); i++;\
            }\
            if (ret != 0) {\
                return luaL_error(L, "Invalid argument to `%s'", opt);\
            }\
            continue;\
        }\
    } while (0)

#define PARSER_LONGOPT_NO_VALUE(OPT, FUNC)   \
    do {\
        const char* opt = OPT;\
        if (strcmp(argv[i], opt) == 0) {\
            FUNC(L, ctx, NULL);\
        }\
    } while (0)

    int i;

    for (i = 0; i < argc; i++)
    {

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            ctx->need_help = 1;
            return 0;
        }

        /* Options. */
        PARSER_LONGOPT_WITH_VALUE("--out", _setup_arg_out);
        PARSER_LONGOPT_WITH_VALUE("--filter", _setup_arg_filter);
        PARSER_LONGOPT_WITH_VALUE("--input", _setup_arg_input);
        PARSER_LONGOPT_NO_VALUE("--verbose", _setup_arg_verbose);
        PARSER_LONGOPT_NO_VALUE("--list-filter", _setup_arg_list_filter);
    }

    if (ctx->need_help || ctx->need_list_filters)
    {
        return 0;
    }

    if (ctx->out_path.data == NULL)
    {
        return luaL_error(L, "Missing option `--out=[PATH]'.");
    }
    if (ctx->filter_sz == 0)
    {
        return luaL_error(L, "Missing option `--filter=[STRING|PATH]'.");
    }

    return 0;

#undef PARSER_LONGOPT_WITH_VALUE
#undef PARSER_LONGOPT_NO_VALUE
}

amalgamate_ctx_t* amalgamate_make(lua_State* L, int argc, char* argv[])
{
    /* Initialize empty object. */
    amalgamate_ctx_t* ctx = lua_newuserdata(L, sizeof(amalgamate_ctx_t));
    memset(ctx, 0, sizeof(*ctx));

    /* Set meta method. */
    static const luaL_Reg s_amalgamate_meta[] = {
        { "__gc",       _amalgamate_gc },
        { "__tostring", _amalgamate_tostring },
        { NULL,         NULL },
    };
    static const luaL_Reg s_amalgamate_method[] = {
        { "substitute", lua_substitute },
        { NULL,         NULL },
    };
    if (luaL_newmetatable(L, "__amalgamate") != 0)
    {
        luaL_setfuncs(L, s_amalgamate_meta, 0);

        luaL_newlib(L, s_amalgamate_method);
        lua_setfield(L, -2, "__index");
    }
    lua_setmetatable(L, -2);

    /* Actual initialize. */
    _setup_args(L, ctx, argc, argv);

    return ctx;
}

static int _amalgamate_is_lua_file(const char* name)
{
    const char* suffix = ".lua";
    size_t suffix_sz = 4;
    size_t name_len = strlen(name);
    if (name_len < suffix_sz)
    {
        return 0;
    }

    return memcmp(name + name_len - 4, suffix, suffix_sz) == 0;
}

static int _amalgamate_load_filter(lua_State* L, const char* name)
{
    int sp = lua_gettop(L);

    if (_amalgamate_is_lua_file(name))
    {
        if (luaL_dofile(L, name) != LUA_OK)
        {
            return lua_error(L);
        }
    }
    else
    {
        amalgamate_filter_t* filter = amalgamate_get_filter(L, name);
        lua_pushcfunction(L, filter->entry); /* SP + 2 */
        lua_call(L, 0, 1); /* SP + 2 */
    }

    /* The return value should be a table */
    lua_settop(L, sp + 1);
    luaL_checktype(L, sp + 1, LUA_TTABLE);

    return 1;
}

static int _amalgamate_check_filter_result(lua_State* L, const char* filter, int idx)
{
    int ret;
    int sp = lua_gettop(L);

    if ((ret = lua_type(L, idx)) != LUA_TTABLE)
    {
        goto error;
    }

    lua_getfield(L, idx, "file"); /* SP + 1 */
    if (lua_type(L, sp + 1) != LUA_TTABLE)
    {
        goto error;
    }

    lua_settop(L, sp);
    return 0;

error:
    return luaL_error(L,
        "Processer in filter `%s' does not return correct type.", filter);
}

static int _amalgamate_run_with_filter(lua_State* L, const char* filter, int idx)
{
    int sp = lua_gettop(L);

    /* Load filter. */
    _amalgamate_load_filter(L, filter); /* SP + 1 */

    /* Get processer function */
    lua_getfield(L, -1, "processer"); /* SP + 2 */

    /* Push parameter */
    lua_pushvalue(L, idx); /* SP + 3 */

    /* Call processer. */
    lua_call(L, 1, 1); /* SP + 2 */

    /* Check result. */
    _amalgamate_check_filter_result(L, filter, sp + 2);

    /* Save result. */
    lua_replace(L, idx); /* SP + 1 */

    /* Rebalance stack. */
    lua_settop(L, sp);

    return 0;
}

static int _amalgamate_write_foreach_file(lua_State* L, int idx, int key, int val, void* data)
{
    (void)idx; (void)key;
    amalgamate_ctx_t* ctx = data;

    lua_getfield(L, val, "data");

    size_t len = 0;
    const char* dat = luaL_tolstring(L, -1, &len);
    fwrite(dat, 1, len, ctx->out_file);
    fwrite("\n", 1, 1, ctx->out_file);

    return 0;
}

static int _amalgamate_write(lua_State* L, amalgamate_ctx_t* ctx, int idx)
{
    int errcode;
    int sp = lua_gettop(L);

    if ((errcode = fopen_s(&ctx->out_file, ctx->out_path.data, "wb")) != 0)
    {
        strerror_r(errcode, ctx->errbuf, sizeof(ctx->errbuf));
        return luaL_error(L, "Cannot open `%s': %s(%d)",
            ctx->out_path.data, ctx->errbuf, errcode);
    }

    lua_getfield(L, idx, "file"); /* SP + 1 */

    lua_foreach(L, sp + 1, _amalgamate_write_foreach_file, ctx);

    fclose(ctx->out_file);
    ctx->out_file = NULL;

    return 0;
}

static int _amalgamate_load_files(lua_State* L, amalgamate_ctx_t* ctx)
{
    size_t i;
    int sp = lua_gettop(L);

    /*
     * {}
     */
    lua_newtable(L); /* SP + 1 */

    /*
     * {
     *     file: [
     *         { "path": "file path", "data": "file content" },
     *         { "path": "file path", "data": "file content" }
     *     ]
     * }
     */
    lua_newtable(L); /* SP + 2 */
    for (i = 0; i < ctx->file_sz; i++)
    {
        /*
         * { "path": "file path", "data": "file content" }
         */
        lua_newtable(L); /* SP + 3 */

        lua_pushstring(L, ctx->files[i]); /* SP + 4 */
        lua_setfield(L, -2, "path"); /* SP + 3 */

        lua_file_load(L, ctx->files[i]); /* SP + 4 */
        lua_setfield(L, -2, "data"); /* SP + 3 */

        lua_rawseti(L, sp + 2, i + 1); /* SP + 2 */
    }
    lua_setfield(L, -2, "file"); /* SP + 1 */

    return 1;
}

int amalgamate_run(lua_State* L, amalgamate_ctx_t* ctx)
{
    size_t i;
    int sp = lua_gettop(L);

    if (ctx->need_help)
    {
        printf("%s", s_help);
        return 0;
    }

    if (ctx->need_list_filters)
    {
        amalgamate_print_filter();
        return 0;
    }

    if (ctx->need_verbose)
    {
        const char* str = _amalgamate_to_string(L, ctx, 1); /* SP + 1 */
        printf("%s", str);
        lua_pop(L, 1); /* SP */
    }

    /* Load files into stack */
    _amalgamate_load_files(L, ctx); /* SP + 1 */

    /* Process every filter */
    for (i = 0; i < ctx->filter_sz; i++)
    {
        _amalgamate_run_with_filter(L, ctx->filters[i], sp + 1);
    }

    return _amalgamate_write(L, ctx, sp + 1);
}
