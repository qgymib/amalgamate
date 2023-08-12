#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "addon/__init__.h"
#include "function/__init__.h"
#include "function/lua_file.h"
#include "amalgamate.h"
#include "preproccess.h"
#include "pcre2.lua.h"
#include "cjson.lua.h"
#include "config.h"

typedef struct amalgamate_ctx
{
    lua_State* L;
} amalgamate_ctx_t;

static amalgamate_ctx_t G = { NULL };

static const char* s_help =
"amalgamate - Merge your source code into one big file.\n"
"Usage: amalgamate [OPTIONS] -- [FILES]\n"
"\n"
"OPTIONS:\n"
"  -h, --help\n"
"    Show this help and exit.\n"
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
"  --output=PATH\n"
"    Path to output file.\n"
"\n"
"  --input=PATH\n"
"    Input file path.\n"
"\n"
" ---iquote=PATH\n"
"    Add the directory dir to the list of directories to be searched.\n"
"\n"
"  --verbose\n"
"    Show extra output.\n"
"\n";

static int _setup_arg_output(lua_State* L, int idx, char* str)
{
    lua_pushcfunction(L, am_func_fmtpath.func);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "output");
    return 0;
}

static int _setup_arg_input(lua_State* L, int idx, char* str)
{
    /* Save input file path */
    lua_pushcfunction(L, am_func_fmtpath.func);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "input");

    return 0;
}

static int _setup_arg_iquote(lua_State* L, int idx, char* str)
{
    lua_getfield(L, idx, "iquote");

    lua_pushstring(L, str);
    lua_seti(L, -2, luaL_len(L, -2) + 1);

    lua_setfield(L, idx, "iquote");
    return 0;
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
            printf("%s", s_help);
            exit(EXIT_SUCCESS);
        }

        PARSER_LONGOPT_WITH_VALUE("--output", _setup_arg_output);
        PARSER_LONGOPT_WITH_VALUE("--input", _setup_arg_input);
        PARSER_LONGOPT_WITH_VALUE("--iquote", _setup_arg_iquote);
        PARSER_LONGOPT_WITH_VALUE("--man", _setup_arg_man);
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
    lua_pushstring(L, ":stdout");
    lua_setfield(L, idx, "output");
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

    lua_newtable(L); // sp + 1

    _setup_default_arguments(L, sp + 1);
    _parser_arguments(L, sp + 1, argc, argv);
    _check_arguments(L, sp + 1);

    lua_setglobal(L, "arg");
}

static void _am_openlibs(lua_State* L)
{
    /* open pcre2 */
    luaL_requiref(L, "pcre2", luaopen_lpcre2, 1);
    lua_pop(L, 1);

    /* open cjson */
    luaL_requiref(L, "cjson", luaopen_cjson, 1);
    lua_pop(L, 1);

    /* Amalgamate API */
    luaopen_am(L);
    lua_pushcfunction(L, am_preproccess);
    lua_setfield(L, -2, "preproccess");
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

    if (luaL_loadbuffer(L, script, strlen(script), "amalgamate.lua") != LUA_OK)
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
