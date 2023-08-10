#include "lua_file.h"
#include "lua_string.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define IS_LETTER(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

typedef struct lua_file
{
    FILE* file;
} lua_file_t;

static int _file_gc(lua_State* L)
{
    lua_file_t* file = lua_touserdata(L, 1);
    if (file->file != NULL)
    {
        fclose(file->file);
        file->file = NULL;
    }

    return 0;
}

/**
 * @brief Open a file and push it on top of stack.
 */
static FILE* lua_fopen(lua_State* L, const char* filename, const char* mode)
{
    int errcode;
    char errbuf[256];
    lua_file_t* file = lua_newuserdata(L, sizeof(lua_file_t));
    file->file = NULL;

    static const luaL_Reg s_file_meta[] = {
        { "__gc",       _file_gc },
        { NULL,         NULL },
    };
    if (luaL_newmetatable(L, "__amalgamate_file") != 0)
    {
        luaL_setfuncs(L, s_file_meta, 0);
    }
    lua_setmetatable(L, -2);

    if ((errcode = fopen_s(&file->file, filename, mode)) != 0)
    {
        strerror_r(errcode, errbuf, sizeof(errbuf));
        luaL_error(L, "Cannot open file `%s': %s(%d).", filename, errbuf, errcode);
        return NULL;
    }

    return file->file;
}

static int _lua_file_load(lua_State* L, const char* path)
{
    int errcode;
    char errbuf[256];

    int sp = lua_gettop(L);
    FILE*  pfile = lua_fopen(L, path, "rb"); /* SP + 1 */

    const size_t bufsz = 4 * 1024;
    char* addr = lua_newuserdata(L, bufsz); /* SP + 2 */

    luaL_Buffer buf;
    luaL_buffinit(L, &buf);
    while (!feof(pfile))
    {
        if ((errcode = ferror(pfile)) != 0)
        {
            goto error;
        }

        size_t nread = fread(addr, 1, bufsz, pfile);
        luaL_addlstring(&buf, addr, nread);
    }

    luaL_pushresult(&buf); /* SP + 3 */

    /* Cleanup. */
    lua_remove(L, sp + 2); /* SP + 2 */
    lua_remove(L, sp + 1); /* SP + 1 */

    return 1;

error:
    strerror_r(errcode, errbuf, sizeof(errbuf));
    return luaL_error(L, "Cannot read file `%s': %s(%d).",
        path, errbuf, errcode);
}

static int _am_load_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    return _lua_file_load(L, path);
}

am_function_t am_func_load_file = {
"load_file", _am_load_file, "string load_file(string path)",
"Load whole file as binary mode and return it.",
"Load whole file as binary mode and return it."
};

static int am_load_txt_file(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* file_type = "\n";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        file_type = lua_tostring(L, 2);
    }

    /* Load file */
    lua_pushcfunction(L, _am_load_file);
    lua_pushvalue(L, 1);
    lua_call(L, 1, 1); // sp+1

    /* Split line */
    lua_pushcfunction(L, am_func_split_line.func);
    lua_insert(L, sp + 1);
    lua_call(L, 1, 1);

    lua_pushcfunction(L, am_func_merge_line.func);
    lua_insert(L, sp + 1);
    lua_pushstring(L, file_type);
    lua_call(L, 2, 1); // sp+1

    return 1;
}

am_function_t am_func_load_txt_file = {
"load_txt_file", am_load_txt_file, "string load_txt_file(string path)",
"Load while file as txt mode and return it.",
"Load while file as txt mode and return it. Line endings is always convert to \"\\n\"."
};

static int _am_is_file_exist(lua_State* L)
{
    FILE* file = NULL;
    const char* path = luaL_checkstring(L, 1);

    int ret = 1;
#if defined(_WIN32)
    if (fopen_s(&file, path, "rb") != 0)
#else
    if ((file = fopen(path, "rb")) == NULL)
#endif
    {
        ret = 0;
    }

    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }

    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_func_is_file_exist = {
"is_file_exist", _am_is_file_exist, "boolean is_file_exist(string path)",
"Check if file is exist.",
"Check if file is exist, return true if it is, false if not exist or cannot\n"
"access it."
};

static char* _am_dirname(char* s)
{
    size_t i;
    if (!s || !*s) return ".";
    i = strlen(s) - 1;
    for (; s[i] == '/'; i--) if (!i) return "/";
    for (; s[i] != '/'; i--) if (!i) return ".";
    for (; s[i] == '/'; i--) if (!i) return "/";
    s[i + 1] = 0;
    return s;
}

static int _lua_dirname(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    char* cpy_path = strdup(path);

    char* name = _am_dirname(cpy_path);
    lua_pushstring(L, name);
    free(cpy_path);

    return 1;
}

am_function_t am_func_dirname = {
"dirname", _lua_dirname, "string dirname(string s)",
"Break string `s` into directory component and return it.",
"dirname() returns the string up to, but not including, the final '/'. If path\n"
"does not contain a slash, dirname() returns the string \".\"."
};

static int _am_fmtpath(lua_State* L)
{
    int sp = lua_gettop(L);
    luaL_checktype(L, 1, LUA_TSTRING);

    const char* delim = "/";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        delim = lua_tostring(L, 2);
    }

    /*
     * ```lua
     * param_1 = string.gsub(param_1, "\\\\", "/")
     * ```
     */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, sp + 1, "gsub"); // sp+2
    lua_pushvalue(L, 1); // sp+3
    lua_pushstring(L, "\\\\"); // sp+4
    lua_pushstring(L, "/"); // sp+5
    lua_call(L, 3, 1); // sp+2
    lua_replace(L, 1); // sp+1

    /*
     * ```lua
     * param_1 = string.gsub(param_1, "/", param_2)
     * ```
     */
    lua_getfield(L, sp + 1, "gsub"); // sp+2
    lua_pushvalue(L, 1); // sp+3
    lua_pushstring(L, "/"); // sp+4
    lua_pushstring(L, delim); // sp+5
    lua_call(L, 3, 1); // sp+2
    lua_replace(L, 1); // sp+1

    lua_pop(L, 1);
    lua_pushvalue(L, 1);

    return 1;
}

am_function_t am_func_fmtpath = {
"fmtpath", _am_fmtpath, "string fmtpath(string path[, string delim])",
"Format path into unified path string.",
"The first parameter is a string contains the path to format. The second optional\n"
"parameter is a string decide what the delimiter is, which by default is \"\\n\".\n"
"\n"
"EXAMPLE\n"
"If we have path string \"path/to\\\\foo\\\\bar\", the result of call\n"
"`fmtpath(path, \"/\")` is:\n"
"\"path/to/foo/bar\"."
};

static int _am_write_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 2, &data_sz);

    FILE* file = NULL;
    int file_need_close = 0;

    if (strcmp(path, ":stdout") == 0)
    {
        file = stdout;
    }
    else if (strcmp(path, ":stderr") == 0)
    {
        file = stderr;
    }
    else
    {
#if defined(_WIN32)
        if (fopen_s(&file, path, "wb") != 0)
#else
        if ((file = fopen(path, "wb")) == NULL)
#endif
        {
            return luaL_error(L, "open `%s` failed.", path);
        }
        file_need_close = 1;
    }

    size_t write_cnt = fwrite(data, data_sz, 1, file);
    if (file_need_close)
    {
        fclose(file);
        file = NULL;
    }

    if (write_cnt != 1)
    {
        return luaL_error(L, "write file failed.");
    }

    return 0;
}

am_function_t am_func_write_file = {
"write_file", _am_write_file, "nil write_file(string path, string data)",
"Write data to file.",

"Open file as binary mode and write data into it.\n"
"\n"
"If the file is not exist, the file will be created. If the file is exist, the\n"
"content of the file is cleared before write."
};

static int _am_is_abs_path(lua_State* L)
{
    int ret = 0;
    const char* path = luaL_checkstring(L, 1);

    if (path[0] == '/')
    {
        ret = 1;
        goto finish;
    }
    if (IS_LETTER(path[0]) && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
        ret = 1;
        goto finish;
    }

finish:
    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_func_is_abs_path = {
"is_abs_path", _am_is_abs_path, "boolean is_abs_path(string path)",
"Check if parameter is absolute path.",
"Check if parameter is absolute path without actually access it."
};
