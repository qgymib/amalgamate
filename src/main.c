//////////////////////////////////////////////////////////////////////////
// Version
//////////////////////////////////////////////////////////////////////////
#define AMALGAMATE_VERSION_MAJRO    1
#define AMALGAMATE_VERSION_MINOR    0
#define AMALGAMATE_VERSION_PATCH    0

//////////////////////////////////////////////////////////////////////////
// System header
//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////
// 3rd: Lua
//////////////////////////////////////////////////////////////////////////
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

//////////////////////////////////////////////////////////////////////////
// 3rd: cJSON
//////////////////////////////////////////////////////////////////////////
/**
 * @AMALGAMATE:BEG
```lua
local expand_include = require("c:expand_include")
local function proc(data, args)
    local fake_cjson_h = "#include \"cJSON.h\""
    local cjson_h = expand_include.proc(fake_cjson_h, { quote_group = "cjson" })
    local fake_cjson_c = "#include \"cJSON.c\""
    local cjson_c = expand_include.proc(fake_cjson_c, { quote_group = "cjson" })
    local ret = cjson_h .. "\n" .. cjson_c .. "\n"
    return am.msvc_suppress_warning(ret, 4996)
end
return { proc = proc }
```
 */
/**
 * @AMALGAMATE:END
 */

//////////////////////////////////////////////////////////////////////////
// 3rd: cjson.lua
//////////////////////////////////////////////////////////////////////////
/**
 * @AMALGAMATE:BEG
```lua
local expand_include = require("c:expand_include")
local function proc(data, args)
    local data_h = expand_include.proc(data, { quote_group = "cjson" })
    local fake_data = "#include \"cjson.lua.c\""
    local data_c = expand_include.proc(fake_data, { quote_group = "cjson" })
    return data_h .. "\n" .. data_c .. "\n"
end
return { proc = proc }
```
 */
#include "cjson.lua.h"
/**
 * @AMALGAMATE:END
 */

//////////////////////////////////////////////////////////////////////////
// User header
//////////////////////////////////////////////////////////////////////////
/**
 * @AMALGAMATE:BEG
```json
{ "name": "c:expand_include" }
```
 */
#include "config.h"
#include "function/__init__.h"
#include "addon/__init__.h"
#include "amalgamate.h"
/**
 * @AMALGAMATE:END
 */

//////////////////////////////////////////////////////////////////////////
// Embed source file
//////////////////////////////////////////////////////////////////////////
/**
 * @AMALGAMATE:BEG
```json
{ "name": "c:expand_include" }
```
 */
#include "function/__init__.c"
#include "function/lua_dirname.c"
#include "function/lua_dump_hex.c"
#include "function/lua_dump_obj.c"
#include "function/lua_fmtpath.c"
#include "function/lua_is_abspath.c"
#include "function/lua_is_file_exist.c"
#include "function/lua_load_file.c"
#include "function/lua_load_txt_file.c"
#include "function/lua_log_i.c"
#include "function/lua_merge_line.c"
#include "function/lua_msvc_suppress_warning.c"
#include "function/lua_search_file.c"
#include "function/lua_sha256.c"
#include "function/lua_split_line.c"
#include "function/lua_split_line_by_pattern.c"
#include "function/lua_strcasecmp.c"
#include "function/lua_table_is_array.c"
#include "function/lua_write_file.c"
#include "addon/__init__.c"
#include "addon/c_dump_hex.c"
#include "addon/c_expand_include.c"
#include "addon/txt_black_hole.c"
#include "amalgamate.c"
/**
 * @AMALGAMATE:END
 */

//////////////////////////////////////////////////////////////////////////
// Embed source code
//////////////////////////////////////////////////////////////////////////

#define AMALGAMATE_VERSION_STRINGIFY(x) AMALGAMATE_VERSION_STRINGIFY_2(x)
#define AMALGAMATE_VERSION_STRINGIFY_2(x) #x

#define AMALGAMATE_VERSION_STRING   \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_MAJRO) \
    "." \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_MINOR) \
    "." \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_PATCH)

typedef struct amalgamate_ctx
{
    lua_State* L;
} amalgamate_ctx_t;

static amalgamate_ctx_t G = { NULL };

static const char* s_help =
"amalgamate v" AMALGAMATE_VERSION_STRING " - Merge your source code into one big file.\n"
"Usage: amalgamate [OPTIONS] -- [FILES]\n"
"\n"
"OPTIONS:\n"
"  --input=PATH\n"
"    Input file path.\n"
"\n"
"  --output=PATH\n"
"    Path to output file.\n"
"\n"
"  --iquote=PATH\n"
"  --iquote=GROUP=PATH\n"
"    Add the directory dir to the list of directories to be searched. If `GROUP`\n"
"    exist, add the directory to the group. This option affect how to search the\n"
"    file (see `--man=search_file` for details).\n"
"\n"
"  --logfile=PATH\n"
"    Where to store log output. And exists content will be erased.\n"
"\n"
"  --list-addon\n"
"    List builtin addons and exit.\n"
"\n"
"  --list-function\n"
"    List builtin functions and exit.\n"
"\n"
"  --man=STRING\n"
"    Show manual of function or addon.\n"
"\n"
"  -v, --version\n"
"    Show software version and exit.\n"
"\n"
"  -h, --help\n"
"    Show this help and exit.\n"
"\n"
"  --verbose\n"
"    Show extra output.\n"
"\n";

static int _setup_arg_output(lua_State* L, int idx, char* str)
{
    lua_pushcfunction(L, am_f_fmtpath.addr);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "output");
    return 0;
}

static int _setup_arg_input(lua_State* L, int idx, char* str)
{
    /* Save input file path */
    lua_pushcfunction(L, am_f_fmtpath.addr);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "input");

    return 0;
}

static int _setup_arg_iquote_with_group(lua_State* L, int idx, const char* group, const char* path)
{
    int sp = lua_gettop(L);

    lua_getfield(L, idx, "iquote"); // sp+1
    if (lua_getfield(L, -1, group) != LUA_TTABLE) // sp+2
    {
        lua_pop(L, 1);
        lua_newtable(L);
    }

    lua_pushstring(L, path); // sp+3
    lua_seti(L, sp + 2, luaL_len(L, sp + 2) + 1); // sp+2

    lua_setfield(L, sp + 1, group); // sp+1
    lua_setfield(L, idx, "iquote");

    return 0;
}

static int _setup_arg_iquote(lua_State* L, int idx, char* str)
{
    const char* pos = strstr(str, "=");
    if (pos == NULL)
    {
        return _setup_arg_iquote_with_group(L, idx, "", str);
    }

    lua_pushlstring(L, str, pos - str);

    const char* group = lua_tostring(L, -1);
    int ret = _setup_arg_iquote_with_group(L, idx, group, pos + 1);
    lua_pop(L, 1);

    return ret;
}

static int _setup_arg_man(lua_State* L, int idx, char* str)
{
    (void)idx;

    lua_pushcfunction(L, am_function_manual);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);

    if (lua_type(L, -1) == LUA_TSTRING)
    {
        goto show_man;
    }
    lua_pop(L, 1);

    lua_pushcfunction(L, am_addon_manual);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);

    if (lua_type(L, -1) == LUA_TSTRING)
    {
        goto show_man;
    }
    lua_pop(L, 0);

    return luaL_error(L, "No manual for %s.", str);

show_man:
    fprintf(stdout, "%s\n", lua_tostring(L, -1));
    exit(EXIT_SUCCESS);
}

static void _clear_log_file(const char* str)
{
    FILE* file;
    char buf[64];

    int ret = fopen_s(&file, str, "wb");
    if (ret != 0)
    {
        strerror_r(ret, buf, sizeof(buf));
        fprintf(stderr, "open `%s` failed: %s(%d).\n", str, buf, ret);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    file = NULL;
}

static int _setup_arg_logfile(lua_State* L, int idx, char* str)
{
    lua_pushstring(L, str);
    lua_setfield(L, idx, "logfile");

    if (str[0] != ':')
    {
        _clear_log_file(str);
    }

    return 0;
}

static int _setup_arg_verbose(lua_State* L, int idx, char* str)
{
    (void)str;
    lua_pushboolean(L, 1);
    lua_setfield(L, idx, "verbose");
    return 0;
}

static int _setup_arg_list_addon(lua_State* L, int idx, char* str)
{
    (void)idx; (void)str;
    lua_pushcfunction(L, am_addon_list);
    lua_call(L, 0, 1);
    fprintf(stdout, "%s", lua_tostring(L, -1));
    exit(EXIT_SUCCESS);
}

static int _setup_arg_list_function(lua_State* L, int idx, char* str)
{
    (void)idx; (void)str;
    lua_pushcfunction(L, am_list_function);
    lua_call(L, 0, 1);
    fprintf(stdout, "%s\n", luaL_checkstring(L, -1));
    exit(EXIT_SUCCESS);
}

static int _parser_arguments(lua_State* L, int idx, int argc, char* argv[])
{
#define PARSER_LONGOPT_WITH_VALUE(OPT, FUNC)   \
    do {\
        int ret = -1; const char* opt = OPT;\
        size_t optlen = strlen(opt);\
        if (strncmp(argv[i], opt, optlen) == 0) {\
            if (argv[i][optlen] == '=') {\
                ret = FUNC(L, idx, argv[i] + optlen + 1);\
            } else if (i < argc - 1) {\
                ret = FUNC(L, idx, argv[i + 1]); i++;\
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
            FUNC(L, idx, NULL);\
        }\
    } while (0)

    int i;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("%s\n", s_help);
            exit(EXIT_SUCCESS);
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("v%s\n", AMALGAMATE_VERSION_STRING);
            exit(EXIT_SUCCESS);
        }

        PARSER_LONGOPT_WITH_VALUE("--output", _setup_arg_output);
        PARSER_LONGOPT_WITH_VALUE("--input", _setup_arg_input);
        PARSER_LONGOPT_WITH_VALUE("--iquote", _setup_arg_iquote);
        PARSER_LONGOPT_WITH_VALUE("--man", _setup_arg_man);
        PARSER_LONGOPT_WITH_VALUE("--logfile", _setup_arg_logfile);
        PARSER_LONGOPT_NO_VALUE("--verbose", _setup_arg_verbose);
        PARSER_LONGOPT_NO_VALUE("--list-addon", _setup_arg_list_addon);
        PARSER_LONGOPT_NO_VALUE("--list-function", _setup_arg_list_function);
    }

    return 0;

#undef PARSER_LONGOPT_WITH_VALUE
#undef PARSER_LONGOPT_NO_VALUE
}

static void _setup_default_arguments(lua_State* L, int idx)
{
    /* .verbose */
    lua_pushboolean(L, 0);
    lua_setfield(L, idx, "verbose");

    /* .iquote */
    lua_newtable(L);
    lua_setfield(L, idx, "iquote");

    /* .output */
    lua_pushstring(L, AMALGAMATE_DEFAULT_OUTPUT);
    lua_setfield(L, idx, "output");

    lua_pushstring(L, AMALGAMATE_DEFAULT_LOGFILE);
    lua_setfield(L, idx, "logfile");

    lua_pushstring(L, AMALGAMATE_PARSER_PATTERN);
    lua_setfield(L, idx, "parser_pattern");

    lua_pushstring(L, AMALGAMATE_DEFAULT_OUTPUT);
    lua_setfield(L, idx, "default_output");

    lua_pushstring(L, AMALGAMATE_DEFAULT_LOGFILE);
    lua_setfield(L, idx, "default_logfile");
}

static int _check_arguments(lua_State* L, int idx)
{
    if (lua_getfield(L, idx, "input") != LUA_TSTRING)
    {
        return luaL_error(L, "Missing argument `--input`.");
    }
    lua_pop(L, 1);

    return 0;
}

static void _generate_arg_table(lua_State* L, int argc, char* argv[])
{
    int sp = lua_gettop(L);

    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+1

    lua_newtable(L); // sp + 2
    _setup_default_arguments(L, sp + 2);
    _parser_arguments(L, sp + 2, argc, argv);
    _check_arguments(L, sp + 2);

    lua_setfield(L, sp + 1, "config");
    lua_setglobal(L, AMALGAMATE_NAMESPACE);
}

static void _am_openlibs(lua_State* L)
{
    /* open cjson */
    luaL_requiref(L, "cjson", luaopen_cjson, 0);
    lua_pop(L, 1);

    /* Amalgamate API */
    luaopen_am(L);
    lua_setglobal(L, AMALGAMATE_NAMESPACE);
}

static int _pmain(lua_State* L)
{
    luaL_openlibs(L);
    _am_openlibs(L);
    am_addon_init(L);

    int argc = (int)lua_tointeger(L, 1);
    char** argv = lua_touserdata(L, 2);
    _generate_arg_table(L, argc, argv);

    int ret = luaL_loadbuffer(L, amalgamate_script, strlen(amalgamate_script),
        "amalgamate.lua");
    if (ret != LUA_OK)
    {
        return lua_error(L);
    }

    lua_call(L, 0, 0);

    return 0;
}

/**
 * @brief Lua error traceback helper.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
static int _msg_handler(lua_State* L)
{
    const char* msg = lua_tostring(L, 1);
    if (msg == NULL)
    {  /* is error object not a string? */
        if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
            lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
        {
            return 1;  /* that is the message */
        }

        msg = lua_pushfstring(L, "(error object is a %s value)",
            luaL_typename(L, 1));
    }
    luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
    return 1;  /* return the traceback */
}

static void _at_exit(void)
{
    if (G.L != NULL)
    {
        lua_close(G.L);
        G.L = NULL;
    }
}

int main(int argc, char* argv[])
{
    atexit(_at_exit);

    G.L = luaL_newstate();

    lua_pushcfunction(G.L, _msg_handler);
    lua_pushcfunction(G.L, _pmain);
    lua_pushinteger(G.L, argc);
    lua_pushlightuserdata(G.L, argv);
    if (lua_pcall(G.L, 2, 0, 1) != LUA_OK)
    {
        fprintf(stderr, "%s", lua_tostring(G.L, -1));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
