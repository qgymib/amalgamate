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
// 3rd: cjson.lua
//////////////////////////////////////////////////////////////////////////
#include "cjson.lua.h"


//////////////////////////////////////////////////////////////////////////
// User header
//////////////////////////////////////////////////////////////////////////

/*
 * ADDON:   c:expand_include
 * PATH:    config.h
 * SIZE:    906
 * SHA-256: 0b01319bb336beeb09082fc70201af1d25663aa327d1ca72e6142d1862564e26
 */
/* AMALGAMATE c:expand_include config.h [BEG] */
#line 1 "config.h"
#ifndef __AMALGAMATE_CONFIG_H__
#define __AMALGAMATE_CONFIG_H__

/**
 * @brief Global amalgamate namespace for Lua
 */
#ifndef AMALGAMATE_NAMESPACE
#define AMALGAMATE_NAMESPACE "am"
#endif

/**
 * @brief Pattern for searching specific code block.
 */
#ifndef AMALGAMATE_PARSER_PATTERN
#define AMALGAMATE_PARSER_PATTERN   \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:BEG\n"         \
    "```(%w+)\n"                    \
    "(.-)\n"                        \
    "```\n"                         \
    " %*/\n"                        \
    "(.-)\n"                        \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:END\n"         \
    " %*/\n"
#endif

#ifndef AMALGAMATE_DEFAULT_OUTPUT
#define AMALGAMATE_DEFAULT_OUTPUT   ":stdout"
#endif

#ifndef AMALGAMATE_DEFAULT_LOGFILE
#define AMALGAMATE_DEFAULT_LOGFILE  ":stderr"
#endif

#endif
/* AMALGAMATE c:expand_include config.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/__init__.h
 * SIZE:    2332
 * SHA-256: d63e80bc43371bc340e0aaedd133684a78edf567b74b25b27d848e14690eb560
 */
/* AMALGAMATE c:expand_include function/__init__.h [BEG] */
#line 1 "function/__init__.h"
#ifndef __AMALGAMATE_FUNCTION_INIT_H__
#define __AMALGAMATE_FUNCTION_INIT_H__

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if defined(_MSC_VER)

#define strtok_r(str, delim, saveptr)   strtok_s(str, delim, saveptr)
#define strerror_r(errcode, buf, len)   strerror_s(buf,len, errcode)
#define strdup(s)                       _strdup(s)

#else

/**
 * @brief Opens a file.
 * @see fopen()
 * @param[out] pFile    A pointer to the file pointer that will receive the
 *   pointer to the opened file.
 * @param[in] filename  Filename.
 * @param[in] mode      Type of access permitted.
 * @return              Zero if successful; an error code on failure.
 */
int fopen_s(FILE** pFile, const char* filename, const char* mode);

#endif

typedef struct am_function
{
    const char*     name;
    lua_CFunction   addr;
    const char*     proto;
    const char*     brief;
    const char*     document;
} am_function_t;

/**
 * @brief Push a table on top of stack that contains all functions.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int luaopen_am(lua_State* L);

/**
 * @brief Push a string on top of stack that contains all function name and brief.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_list_function(lua_State* L);

/**
 * @brief Search for function manual.
 * @param[in] L     Lua VM.
 * @return          1 if found, or 0 if not found.
 */
int am_function_manual(lua_State* L);

/**
 * @brief Registered builtin functions
 * @{
 */
extern am_function_t am_f_dirname;
extern am_function_t am_f_dump_hex;
extern am_function_t am_f_dump_obj;
extern am_function_t am_f_fmtpath;
extern am_function_t am_f_is_abspath;
extern am_function_t am_f_is_file_exist;
extern am_function_t am_f_load_file;
extern am_function_t am_f_load_txt_file;
extern am_function_t am_f_log_i;
extern am_function_t am_f_merge_line;
extern am_function_t am_f_search_file;
extern am_function_t am_f_sha256;
extern am_function_t am_f_split_line;
extern am_function_t am_f_strcasecmp;
extern am_function_t am_f_table_is_array;
extern am_function_t am_f_write_file;
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
/* AMALGAMATE c:expand_include function/__init__.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/__init__.h
 * SIZE:    1103
 * SHA-256: e1aa73fcd13e955077ba7bffa54283a171b17c9b2719d4e430b9434384393a00
 */
/* AMALGAMATE c:expand_include addon/__init__.h [BEG] */
#line 1 "addon/__init__.h"
#ifndef __AMALGAMATE_ADDON_INIT_H__
#define __AMALGAMATE_ADDON_INIT_H__

/* AMALGAMATE_DISPLACE_INCLUDE: function/__init__.h */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct am_addon
{
    const char*     name;
    lua_CFunction   open;
} am_addon_t;

/**
 * @brief Initialize addons as required mode.
 */
void am_addon_init(lua_State* L);

/**
 * @brief List addons
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_addon_list(lua_State* L);

/**
 * @param[in] Load manual for specific addon.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_addon_manual(lua_State* L);

/**
 * @brief Call script
 * @param[in] L         Lua VM.
 * @param[in] script    Script.
 * @param[in] name      Script name.
 * @return Always 1.
 */
int am_addon_call_script(lua_State* L, const char* script, const char* name);

/**
 * @brief Registered builtin addons
 * @{
 */
extern am_addon_t am_a_c_dump_hex;
extern am_addon_t am_a_c_expand_include;
extern am_addon_t am_a_txt_black_hole;
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
/* AMALGAMATE c:expand_include addon/__init__.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    amalgamate.h
 * SIZE:    190
 * SHA-256: 935d75a5b2d077d8aadfe111c57bb49fc9ce08b5887ab5321658dc2cb073f6ea
 */
/* AMALGAMATE c:expand_include amalgamate.h [BEG] */
#line 1 "amalgamate.h"
#ifndef __AMALGAMATE_SCRIPT_H__
#define __AMALGAMATE_SCRIPT_H__
#ifdef __cplusplus
extern "C" {
#endif

extern const char* amalgamate_script;

#ifdef __cplusplus
}
#endif
#endif
/* AMALGAMATE c:expand_include amalgamate.h [END] */


//////////////////////////////////////////////////////////////////////////
// Embed source file
//////////////////////////////////////////////////////////////////////////

/*
 * ADDON:   c:expand_include
 * PATH:    function/__init__.c
 * SIZE:    2005
 * SHA-256: e8d4633b7b7344628c24af52801b789bcb90fa1eff04810da36d5d856aba8e41
 */
/* AMALGAMATE c:expand_include function/__init__.c [BEG] */
#line 1 "function/__init__.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>
#include <errno.h>

static am_function_t* am_apis[] = {
    &am_f_dirname,
    &am_f_dump_hex,
    &am_f_dump_obj,
    &am_f_fmtpath,
    &am_f_is_abspath,
    &am_f_is_file_exist,
    &am_f_load_file,
    &am_f_load_txt_file,
    &am_f_log_i,
    &am_f_merge_line,
    &am_f_search_file,
    &am_f_sha256,
    &am_f_split_line,
    &am_f_strcasecmp,
    &am_f_table_is_array,
    &am_f_write_file,
};

#if !defined(_MSC_VER)
int fopen_s(FILE** pFile, const char* filename, const char* mode)
{
    if ((*pFile = fopen(filename, mode)) == NULL)
    {
        return errno;
    }
    return 0;
}
#endif

int luaopen_am(lua_State* L)
{
    lua_newtable(L);

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        lua_pushcfunction(L, am_apis[i]->addr);
        lua_setfield(L, -2, am_apis[i]->name);
    }

    return 1;
}

int am_list_function(lua_State* L)
{
    int sp = lua_gettop(L);
    lua_pushstring(L, ""); // sp+1

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        lua_pushvalue(L, sp + 1);
        lua_pushfstring(L, "%s\n    %s\n", am_apis[i]->name, am_apis[i]->brief);
        lua_concat(L, 2);
        lua_replace(L, sp + 1);
    }

    return 1;
}

int am_function_manual(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        if (strcmp(name, am_apis[i]->name) == 0)
        {
            lua_pushfstring(L,
                "[NAME]\n"
                "%s\n"
                "\n"
                "[SYNOPSIS]\n"
                "%s\n"
                "\n"
                "[BRIEF]\n"
                "%s\n"
                "\n"
                "[DOCUMENT]\n"
                "%s\n",
                am_apis[i]->name, am_apis[i]->proto, am_apis[i]->brief, am_apis[i]->document);
            return 1;
        }
    }

    return 0;
}
/* AMALGAMATE c:expand_include function/__init__.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dirname.c
 * SIZE:    864
 * SHA-256: 949469fead3b2455531177f93e7e5bc2f6501fb5979018ec05e33928c68eca04
 */
/* AMALGAMATE c:expand_include function/lua_dirname.c [BEG] */
#line 1 "function/lua_dirname.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

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

am_function_t am_f_dirname = {
"dirname", _lua_dirname, "string dirname(string s)",
"Break string `s` into directory component and return it.",
"dirname() returns the string up to, but not including, the final '/'. If path\n"
"does not contain a slash, dirname() returns the string \".\"."
};
/* AMALGAMATE c:expand_include function/lua_dirname.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dump_hex.c
 * SIZE:    1831
 * SHA-256: 7c93a08b450368a5b333d6151615de09991084bbc95b38b469cd977824bc79ad
 */
/* AMALGAMATE c:expand_include function/lua_dump_hex.c [BEG] */
#line 1 "function/lua_dump_hex.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static char _mmc_ascii_to_char(unsigned char c)
{
    if (c >= 32 && c <= 126)
    {
        return c;
    }
    return '.';
}

static void mmc_dump_hex(luaL_Buffer* buf, const void* data, size_t size, size_t width)
{
    char tmp[64];
    const unsigned char* pdat = (unsigned char*)data;

    size_t idx_line;
    for (idx_line = 0; idx_line < size; idx_line += width)
    {
        snprintf(tmp, sizeof(tmp), "%p: ", (void*)(uintptr_t)idx_line);
        luaL_addstring(buf, tmp);

        /* printf hex */
        size_t idx_colume;
        for (idx_colume = 0; idx_colume < width; idx_colume++)
        {
            const char* postfix = (idx_colume < width - 1) ? "" : "|";

            if (idx_colume + idx_line < size)
            {
                snprintf(tmp, sizeof(tmp), "%02x %s", pdat[idx_colume + idx_line], postfix);
            }
            else
            {
                snprintf(tmp, sizeof(tmp), "   %s", postfix);
            }
            luaL_addstring(buf, tmp);
        }
        luaL_addchar(buf, ' ');
        /* printf char */
        for (idx_colume = 0; (idx_colume < width) && (idx_colume + idx_line < size); idx_colume++)
        {
            luaL_addchar(buf, _mmc_ascii_to_char(pdat[idx_colume + idx_line]));
        }
        luaL_addchar(buf, '\n');
    }
}

static int _am_dump_hex(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    luaL_Buffer buf;
    luaL_buffinit(L, &buf);
    mmc_dump_hex(&buf, data, data_sz, 16);
    luaL_pushresult(&buf);

    return 1;
}

am_function_t am_f_dump_hex = {
"dump_hex", _am_dump_hex, "string dump_hex(string s)",
"Dump string as hex string.",

"Dump string as hex string with ASCII character shown.\n"
};
/* AMALGAMATE c:expand_include function/lua_dump_hex.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dump_obj.c
 * SIZE:    1258
 * SHA-256: 65315e330bf767f1763c48cb89ab23379655227b4d9655634ecd6d0ccad92511
 */
/* AMALGAMATE c:expand_include function/lua_dump_obj.c [BEG] */
#line 1 "function/lua_dump_obj.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_dump_obj(lua_State* L)
{
    if (lua_type(L, 1) != LUA_TTABLE)
    {
        lua_getglobal(L, "tostring");
        lua_pushvalue(L, 1);
        lua_call(L, 1, 1);
        return 1;
    }

    int sp = lua_gettop(L);
    lua_pushstring(L, "{ "); // sp+1: return value

    lua_pushnil(L); // sp+2
    while (lua_next(L, 1) != 0) // sp+3
    {
        lua_pushvalue(L, sp + 1);
        lua_pushstring(L, "[");

        if (lua_type(L, sp + 2) != LUA_TNUMBER)
        {
            lua_pushstring(L, "\"");
            lua_pushvalue(L, sp + 2);
            lua_pushstring(L, "\"");
            lua_concat(L, 3);
        }
        else
        {
            lua_pushvalue(L, sp + 2);
        }
        lua_pushstring(L, "] = ");

        lua_pushcfunction(L, _am_dump_obj);
        lua_pushvalue(L, sp + 3);
        lua_call(L, 1, 1);

        lua_pushstring(L, ",");

        lua_concat(L, 6);
        lua_replace(L, sp + 1);

        lua_pop(L, 1);
    }

    lua_pushstring(L, "} ");
    lua_concat(L, 2);

    return 1;
}

am_function_t am_f_dump_obj = {
"dump_obj",_am_dump_obj, "string dump_obj(object o)",
"Dump object as string.",
"Dump object as string."
};
/* AMALGAMATE c:expand_include function/lua_dump_obj.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_fmtpath.c
 * SIZE:    1478
 * SHA-256: 0b0026a1e86e667e0f3d0cb131d74ae80d67b4b28687f63833ba66843998b1f8
 */
/* AMALGAMATE c:expand_include function/lua_fmtpath.c [BEG] */
#line 1 "function/lua_fmtpath.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

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

am_function_t am_f_fmtpath = {
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
/* AMALGAMATE c:expand_include function/lua_fmtpath.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_is_abspath.c
 * SIZE:    713
 * SHA-256: 21d337477d687c9586a968fe778ef49c73190379cb46f3158a15cb9925b970e2
 */
/* AMALGAMATE c:expand_include function/lua_is_abspath.c [BEG] */
#line 1 "function/lua_is_abspath.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

#define IS_LETTER(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

static int _am_is_abspath(lua_State* L)
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

am_function_t am_f_is_abspath = {
"is_abspath", _am_is_abspath, "boolean is_abspath(string path)",
"Check if parameter is absolute path.",
"Check if parameter is absolute path without actually access it."
};
/* AMALGAMATE c:expand_include function/lua_is_abspath.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_is_file_exist.c
 * SIZE:    714
 * SHA-256: b5e027d35098115d29b4941dd71d730b4ef2291186e07079022ab8037db40fc9
 */
/* AMALGAMATE c:expand_include function/lua_is_file_exist.c [BEG] */
#line 1 "function/lua_is_file_exist.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

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

am_function_t am_f_is_file_exist = {
"is_file_exist", _am_is_file_exist, "boolean is_file_exist(string path)",
"Check if file is exist.",
"Check if file is exist, return true if it is, false if not exist or cannot\n"
"access it."
};
/* AMALGAMATE c:expand_include function/lua_is_file_exist.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_load_file.c
 * SIZE:    2355
 * SHA-256: 499f431bf4089ef459b9f52501ae36be5659b33647af5e8fa053a67405610cdf
 */
/* AMALGAMATE c:expand_include function/lua_load_file.c [BEG] */
#line 1 "function/lua_load_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

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

am_function_t am_f_load_file = {
"load_file", _am_load_file, "string load_file(string path)",
"Load whole file as binary mode and return it.",
"Load whole file as binary mode and return it."
};
/* AMALGAMATE c:expand_include function/lua_load_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_load_txt_file.c
 * SIZE:    913
 * SHA-256: abc28513bbd0ddbada84dd4104644d82a9c19f5d0c04b7c3e06686f0834e3021
 */
/* AMALGAMATE c:expand_include function/lua_load_txt_file.c [BEG] */
#line 1 "function/lua_load_txt_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_load_txt_file(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* file_type = "\n";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        file_type = lua_tostring(L, 2);
    }

    /* Load file */
    lua_pushcfunction(L, am_f_load_file.addr);
    lua_pushvalue(L, 1);
    lua_call(L, 1, 1); // sp+1

    /* Split line */
    lua_pushcfunction(L, am_f_split_line.addr);
    lua_insert(L, sp + 1);
    lua_call(L, 1, 1); // sp+1

    lua_pushcfunction(L, am_f_merge_line.addr);
    lua_insert(L, sp + 1);
    lua_pushstring(L, file_type);
    lua_call(L, 2, 1); // sp+1

    return 1;
}

am_function_t am_f_load_txt_file = {
"load_txt_file", _am_load_txt_file, "string load_txt_file(string path)",
"Load while file as txt mode and return it.",
"Load while file as txt mode and return it. Line endings is always convert to \"\\n\"."
};
/* AMALGAMATE c:expand_include function/lua_load_txt_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_log_i.c
 * SIZE:    1112
 * SHA-256: 0037ccacefa18bd952b44e52f411abc566a8941764338db439250977a760b7aa
 */
/* AMALGAMATE c:expand_include function/lua_log_i.c [BEG] */
#line 1 "function/lua_log_i.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

static int _log_i(lua_State* L)
{
    int sp = lua_gettop(L);
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Format string */
    lua_getglobal(L, "string"); //sp+1
    lua_getfield(L, -1, "format"); //sp+2
    lua_remove(L, sp + 1);
    lua_insert(L, 1);
    lua_call(L, sp, 1); // sp=1
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Write to logfile */
    lua_Debug ar; memset(&ar, 0, sizeof(ar));
    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "nSl", &ar);

    lua_pushcfunction(L, am_f_write_file.addr); // sp=2

    lua_getglobal(L, "arg"); // sp=3
    lua_getfield(L, -1, "logfile"); //sp=4
    lua_remove(L, 3); // sp=3

    lua_pushfstring(L, "[%s:%d] ", ar.source, ar.currentline); // sp=4
    lua_pushvalue(L, 1); // sp=5
    lua_pushstring(L, "\n"); // sp=6
    lua_concat(L, 3); // sp=4

    lua_pushstring(L, "a+b"); // sp+5

    lua_call(L, 3, 0); // sp=1

    return 0;
}

am_function_t am_f_log_i = {
"log_i", _log_i, "nil log_i(string data)",
"Append data into log file.",
"Append data into log file."
};
/* AMALGAMATE c:expand_include function/lua_log_i.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_merge_line.c
 * SIZE:    1121
 * SHA-256: 6e52e32ccb5952d4f6d84d577bbd0c6b7a61aaca0c8f2a90d103240d3f8f9c45
 */
/* AMALGAMATE c:expand_include function/lua_merge_line.c [BEG] */
#line 1 "function/lua_merge_line.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_merge_line(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TSTRING);
    lua_settop(L, 2);

    lua_pushstring(L, ""); // sp:3

    lua_pushnil(L); // key:4

    size_t cnt;
    for (cnt = 0; lua_next(L, 1) != 0; cnt++) // value:5
    {
        lua_pushvalue(L, 3); //sp:6

        if (cnt != 0)
        {
            lua_pushvalue(L, 2); //sp:7
        }

        lua_pushvalue(L, 5); //sp:8
        lua_concat(L, cnt != 0 ? 3 : 2); // sp:6
        lua_replace(L, 3); // sp:5

        lua_pop(L, 1);
    }

    return 1;
}

am_function_t am_f_merge_line = {
"merge_line", _am_merge_line, "string merge_line(table t[, string token])",
"Merge array of strings into a large string.",

"Merge array of strings into a large string, with `token` specific combinator.\n"
"If `token` is not assign, it is treat as `\\n`.\n"
"\n"
"EXAMPLE\n"
"If we have following table:\n"
"```lua\n"
"{ [1]=\"hello\", [2]=\" \", [3]=\"world\" }\n"
"```\n"
"The result of merge_line() will be:\n"
"\"hello\\n \\nworld\"."
};
/* AMALGAMATE c:expand_include function/lua_merge_line.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_search_file.c
 * SIZE:    4922
 * SHA-256: 4ce2c1af638ff4e4303896b52e3303290da00014ef4ac96c369c390b5a1928b0
 */
/* AMALGAMATE c:expand_include function/lua_search_file.c [BEG] */
#line 1 "function/lua_search_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

/**
 * @brief Check if path at \p idx is abspath.
 *
 * The stack is always unchanged.
 *
 * @return  boolean
 */
static int _am_search_file_is_abspath(lua_State* L, const char* file)
{
    lua_pushcfunction(L, am_f_is_abspath.addr);
    lua_pushstring(L, file);
    lua_call(L, 1, 1);

    int ret = lua_toboolean(L, -1);
    lua_pop(L, 1);

    return ret;
}

/**
 * @brief Check if file at \p idx is exist.
 *
 * The stack is always unchanged.
 *
 * @return  boolean
 */
static int _am_search_file_is_exist(lua_State* L, const char* file)
{
    lua_pushcfunction(L, am_f_is_file_exist.addr);
    lua_pushstring(L, file);
    lua_call(L, 1, 1);

    int ret = lua_toboolean(L, -1);
    lua_pop(L, 1);

    return ret;
}

/**
 * @brief Search file at \p idx_path in directory at \p idx_dirname
 * 
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 * 
 * @return 1 if found, 0 if not.
 */
static int _am_search_file_in_directory(lua_State* L, const char* dir, const char* file)
{
    int sp = lua_gettop(L);

    lua_pushstring(L, dir);
    lua_pushstring(L, "/");
    lua_pushstring(L, file);
    lua_concat(L, 3); // sp+1

    if (_am_search_file_is_exist(L, lua_tostring(L, sp + 1)))
    {
        return 1;
    }

    lua_pop(L, 1);
    return 0;
}

/**
 * @brief Search file at \p idx from current directory.
 *
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 *
 * @return 1 if found, 0 if not.
 */
static int _am_serach_file_from_current_directory(lua_State* L, const char* file)
{
    int sp = lua_gettop(L);

    /* Get dirname from input */
    lua_pushcfunction(L, am_f_dirname.addr); // sp+1
    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+2
    lua_getfield(L, -1, "config"); // sp+3
    lua_getfield(L, -1, "input"); // sp+4
    lua_remove(L, sp + 3); // sp+3
    lua_remove(L, sp + 2); // sp+2
    lua_call(L, 1, 1); // sp+1

    const char* dir = lua_tostring(L, sp + 1);
    int ret = _am_search_file_in_directory(L, dir, file);
    lua_remove(L, sp + 1);

    return ret;
}

static int _am_search_file_in_quote(lua_State* L, int quote_idx, const char* group, const char* file)
{
    int i;
    int sp = lua_gettop(L);

    if (lua_getfield(L, quote_idx, group) != LUA_TTABLE) // sp+1
    {
        lua_pop(L, 1);
        return 0;
    }

    for (i = 1;; i++)
    {
        if (lua_geti(L, -1, i) != LUA_TSTRING) // sp+2: directory
        {
            lua_pop(L, 1);
            break;
        }

        const char* dir = lua_tostring(L, sp + 2);
        if (_am_search_file_in_directory(L, dir, file))
        {
            lua_remove(L, sp + 1);
            return 1;
        }
        lua_pop(L, 1);
    }

    return 0;
}

/**
 * @brief Search file at \p idx from iquote table.
 *
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 *
 * @return 1 if found, 0 if not.
 */
static int _am_search_file_from_quote(lua_State* L, const char* group, const char* path)
{
    int ret = 0;
    int sp = lua_gettop(L);

    /* Get iquote table at sp+1 */
    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+1
    lua_getfield(L, -1, "config"); // sp+2
    lua_getfield(L, -1, "iquote"); // sp+3
    lua_remove(L, sp + 2); // sp+2
    lua_remove(L, sp + 1); // sp+1

    if ((ret = _am_search_file_in_quote(L, sp + 1, group, path)) != 0)
    {
        goto finish;
    }

	if ((ret = _am_search_file_in_quote(L, sp + 1, "", path)) != 0)
	{
        goto finish;
	}

finish:
    lua_remove(L, sp + 1);
    return ret;
}

static int _am_search_file_from_current_and_quote(lua_State* L,
    const char* group, const char* file)
{
    if (_am_serach_file_from_current_directory(L, file))
    {
        return 1;
    }

    return _am_search_file_from_quote(L, group, file);
}

static int _am_search_file(lua_State* L)
{
    const char* file = luaL_checkstring(L, 1);
    const char* group = luaL_optstring(L, 2, "");

    /* Check for abspath */
    if (_am_search_file_is_abspath(L, file) == 0)
    {
        return _am_search_file_from_current_and_quote(L, group, file);
    }

    return !!_am_search_file_is_exist(L, file);
}

am_function_t am_f_search_file = {
"search_file", _am_search_file, "string search_file(string path[, string group])",
"Search file in current directory and quote directory.",

"Search file in current directory and quote directory. Return the real path that\n"
"can be opened or nil if failed.\n"
"\n"
"The search policy is:\n"
"1) Search in current directory where input file is.\n"
"2) Search in quote group if `group` option exists.\n"
"3) Search in default quote group \"\".\n"
};
/* AMALGAMATE c:expand_include function/lua_search_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_sha256.c
 * SIZE:    7762
 * SHA-256: 1b9ffed3e8024a3d6a5346f5d39d5cda87eba33d88611893743b3421b95ae577
 */
/* AMALGAMATE c:expand_include function/lua_sha256.c [BEG] */
#line 1 "function/lua_sha256.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/



/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/

typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
static void sha256_init(SHA256_CTX* ctx);
static void sha256_update(SHA256_CTX* ctx, const uint8_t data[], size_t len);
static void sha256_final(SHA256_CTX* ctx, uint8_t hash[]);


/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA-256 hashing algorithm.
              SHA-256 is one of the three algorithms in the SHA2
              specification. The others, SHA-384 and SHA-512, are not
              offered in this implementation.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/

/*************************** HEADER FILES ***************************/


/****************************** MACROS ******************************/
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

/**************************** VARIABLES *****************************/
static const uint32_t k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

/*********************** FUNCTION DEFINITIONS ***********************/
static void sha256_transform(SHA256_CTX* ctx, const uint8_t data[])
{
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

static void sha256_init(SHA256_CTX* ctx)
{
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

static void sha256_update(SHA256_CTX* ctx, const uint8_t data[], size_t len)
{
    uint32_t i;

    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha256_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

static void sha256_final(SHA256_CTX* ctx, uint8_t hash[])
{
    uint32_t i;

    i = ctx->datalen;

    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56)
            ctx->data[i++] = 0x00;
    }
    else {
        ctx->data[i++] = 0x80;
        while (i < 64)
            ctx->data[i++] = 0x00;
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56);
    }

    // Append to the padding the total message's length in bits and transform.
    ctx->bitlen += (uint64_t)(ctx->datalen * 8);
    ctx->data[63] = (uint8_t)ctx->bitlen;
    ctx->data[62] = (uint8_t)(ctx->bitlen >> 8);
    ctx->data[61] = (uint8_t)(ctx->bitlen >> 16);
    ctx->data[60] = (uint8_t)(ctx->bitlen >> 24);
    ctx->data[59] = (uint8_t)(ctx->bitlen >> 32);
    ctx->data[58] = (uint8_t)(ctx->bitlen >> 40);
    ctx->data[57] = (uint8_t)(ctx->bitlen >> 48);
    ctx->data[56] = (uint8_t)(ctx->bitlen >> 56);
    sha256_transform(ctx, ctx->data);

    // Since this implementation uses little endian byte ordering and SHA uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

static int _am_sha256(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (uint8_t*)data, data_sz);

    uint8_t ret[SHA256_BLOCK_SIZE];
    sha256_final(&ctx, ret);

    char buf[65]; size_t i;
    for (i = 0; i < sizeof(ret); i++)
    {
        snprintf(buf + 2 * i, sizeof(buf) - 2 * i, "%02x", ret[i]);
    }

    lua_pushstring(L, buf);
    return 1;
}

am_function_t am_f_sha256 = {
"sha256", _am_sha256, "string sha256(string s)",
"Calcualte SHA-256.",

"Calcualte SHA256 of `s` and return it's string value."
};
/* AMALGAMATE c:expand_include function/lua_sha256.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_split_line.c
 * SIZE:    1783
 * SHA-256: a28d60008fc3a823a748a38c308c8e331afd96a5ea09872264a62eb896ad7660
 */
/* AMALGAMATE c:expand_include function/lua_split_line.c [BEG] */
#line 1 "function/lua_split_line.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_split_line(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    // This will be the return value.
    lua_newtable(L);

    size_t pos;
    const char* start = data;

    for (pos = 0; pos < data_sz; pos++)
    {
        /*
         * There are 3 EOLs:
         * \r\n: CRLF (Windows)
         * \r: CR (Macintosh)
         * \n: LF (Unix)
         * Here we allow mixed line endings, just to parse aggressively.
         */
        if (data[pos] == '\r')
        {
            size_t len = &data[pos] - start;
            lua_pushlstring(L, start, len);
            lua_seti(L, -2, luaL_len(L, -2) + 1);

            if (pos < data_sz - 1 && data[pos + 1] == '\n')
            {
                start = &data[pos + 2];
                pos++;
            }
            else
            {
                start = &data[pos + 1];
            }
            continue;
        }
        else if (data[pos] == '\n')
        {
            size_t len = &data[pos] - start;
            lua_pushlstring(L, start, len);
            lua_seti(L, -2, luaL_len(L, -2) + 1);

            start = &data[pos + 1];
            continue;
        }
    }

    if (start < data + pos)
    {
        size_t len = data + data_sz - start;
        lua_pushlstring(L, start, len);
        lua_seti(L, -2, luaL_len(L, -2) + 1);
    }

    return 1;
}

am_function_t am_f_split_line = {
"split_line", _am_split_line, "table split_line(string s)",
"Split string into array.",

"Split string into array, with line wrap as token. This function automatically\n"
"take care of different endings like `\\r`, `\\n` or `\\r\\n`. Empty line is not\n"
"ignored."
};
/* AMALGAMATE c:expand_include function/lua_split_line.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_strcasecmp.c
 * SIZE:    814
 * SHA-256: eda786d14f01a79d3cb8c1af61fc2a14b230da7d1388b61be9aa5461f817fc2d
 */
/* AMALGAMATE c:expand_include function/lua_strcasecmp.c [BEG] */
#line 1 "function/lua_strcasecmp.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

#if defined(_WIN32)
#   define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif

static int _am_strcasecmp(lua_State* L)
{
    const char* s1 = luaL_checkstring(L, 1);
    const char* s2 = luaL_checkstring(L, 2);

    int ret = strcasecmp(s1, s2);
    lua_pushnumber(L, ret);

    return 1;
}

am_function_t am_f_strcasecmp = {
"strcasecmp", _am_strcasecmp, "number strcasecmp(string s1, string s2)",
"Compare string ignoring the case of the characters.",

"The strcasecmp() function performs a byte-by-byte comparison of the strings `s1`\n"
"and `s2`, ignoring the case of the characters. It returns an integer less than,\n"
"equal to, or greater than zero if `s1` is found, respectively, to be less than,\n"
"to match, or be greater than `s2`."
};
/* AMALGAMATE c:expand_include function/lua_strcasecmp.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_table_is_array.c
 * SIZE:    467
 * SHA-256: 3cc019095e3cf941e406a22c318cd5e3426a17092a197042daa512d9f4c3f587
 */
/* AMALGAMATE c:expand_include function/lua_table_is_array.c [BEG] */
#line 1 "function/lua_table_is_array.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int am_table_is_array(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    int ret = 0;
    if (lua_geti(L, 1, 1) != LUA_TNIL)
    {
        ret = 1;
    }
    lua_pop(L, 1);

    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_table_is_array = {
"table_is_array", am_table_is_array, "boolean table_is_array(table t)",
"Check if a Lua table is array.",

"Check if parameter `t` is an array."
};
/* AMALGAMATE c:expand_include function/lua_table_is_array.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_write_file.c
 * SIZE:    1546
 * SHA-256: 53ed29e955f19651017d3f66a9cd0bc8d5dd1ff0c4e060796420762d98aa11d3
 */
/* AMALGAMATE c:expand_include function/lua_write_file.c [BEG] */
#line 1 "function/lua_write_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

static int _am_file_op(lua_State* L, const char* path, const char* mode,
    const char* data, size_t data_sz)
{
    int ret;
    int file_need_close = 0;
    FILE* file = NULL;

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
        if ((ret = fopen_s(&file, path, mode)) != 0)
        {
            char buf[64];
            strerror_r(ret, buf, sizeof(buf));
            return luaL_error(L, "open `%s` failed: %s(%d).", path, buf, ret);
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
        return luaL_error(L, "write file `%s` failed.", path);
    }

    return 0;
}

static int _am_write_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 2, &data_sz);

    const char* mode = "wb";
    if (lua_type(L, 3) == LUA_TSTRING)
    {
        mode = lua_tostring(L, 3);
    }

    return _am_file_op(L, path, mode, data, data_sz);
}

am_function_t am_f_write_file = {
"write_file", _am_write_file, "nil write_file(string path, string data[, string mode])",
"Write data to file.",

"Open file and write data into it.\n"
"\n"
"By default `mode` is set to \"wb\"."
};
/* AMALGAMATE c:expand_include function/lua_write_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/__init__.c
 * SIZE:    3228
 * SHA-256: e5e336dd371c14f1174c4df336f1fca1399a16af1b1c5809510033973f67f3de
 */
/* AMALGAMATE c:expand_include addon/__init__.c [BEG] */
#line 1 "addon/__init__.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

static am_addon_t* s_addon_list[] = {
    &am_a_c_dump_hex,
    &am_a_c_expand_include,
    &am_a_txt_black_hole,
};

typedef void (*am_addon_load_cb)(lua_State* L, const char* name, int idx, void* arg);

/**
 * @brief Load all addons.
 * @param[in] L     Lua VM.
 * @param[in] cb    Load callback. Can be NULL.
 * @param[in] arg   User data passed to \p cb.
 */
static void _am_addon_load(lua_State* L, am_addon_load_cb cb, void* arg)
{
    size_t i;
    int sp = lua_gettop(L);

    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1);
        if (cb != NULL)
        {
            cb(L, s_addon_list[i]->name, sp + 1, arg);
        }
        lua_settop(L, sp);
    }
}

static void _addon_foreach(lua_State* L, const char* name, int idx, void* arg)
{
    int* p_ret_idx = (int*)arg;
    int ret_idx = *p_ret_idx;

    lua_pushvalue(L, ret_idx);
    lua_pushfstring(L, "%s\n    ", name);
    if (lua_getfield(L, idx, "brief") != LUA_TSTRING)
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NO BRIEF");
    }
    lua_pushstring(L, "\n");
    lua_concat(L, 4);
    lua_replace(L, ret_idx);
}

void am_addon_init(lua_State* L)
{
    _am_addon_load(L, NULL, NULL);
}

int am_addon_list(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_pushstring(L, ""); // sp+1: this will be the return value
    int idx = sp + 1;

    _am_addon_load(L, _addon_foreach, &idx);

    return 1;
}

static void _addon_manual(lua_State* L, const char* name, int ret_idx, int req_idx)
{
    /* NAME */
    lua_pushfstring(L, "[NAME]\n%s\n\n", name);

    /* BRIEF */
    lua_pushstring(L, "[BRIEF]\n");
    if (lua_getfield(L, req_idx, "brief") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n\n");
    }
    lua_concat(L, 2);

    /* DOCUMENT */
    lua_pushstring(L, "[DOCUMENT]\n");
    if (lua_getfield(L, req_idx, "desc") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n");
    }
    lua_concat(L, 2);

    /* Merge string */
    lua_concat(L, 3);

    /* Set return value */
    lua_replace(L, ret_idx);
}

int am_addon_manual(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* name = luaL_checkstring(L, 1);

    lua_pushstring(L, ""); // sp+1: return value.

    size_t i;
    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        if (strcmp(name, s_addon_list[i]->name) == 0)
        {
            luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1); // sp+2
            _addon_manual(L, name, sp + 1, sp + 2);
            lua_pop(L, 1);
            return 1;
        }
    }

    return 0;
}

int am_addon_call_script(lua_State* L, const char* script, const char* name)
{
    if (luaL_loadbuffer(L, script, strlen(script), name) != LUA_OK)
    {
        return lua_error(L);
    }

    lua_call(L, 0, 1);
    return 1;
}
/* AMALGAMATE c:expand_include addon/__init__.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/c_dump_hex.c
 * SIZE:    3071
 * SHA-256: a93680e0147ce5972ffe17bd3dd29a43e8bc57a50283f6e6c9d1ffa59e80c426
 */
/* AMALGAMATE c:expand_include addon/c_dump_hex.c [BEG] */
#line 1 "addon/c_dump_hex.c"
#define LF "\n"
static const char* dump_hex_script = "\n" LF
LF
"local function dump_hex_proc(data, args)" LF
"    local src_data = data" LF
"    local ret = \"\"" LF
LF
"    -- Format arguments" LF
"    if args.include_stdint == nil then" LF
"        args.include_stdint = false" LF
"    end" LF
"    if args.append_eol == nil then" LF
"        args.append_eol = true" LF
"    end" LF
LF
"    -- Handle args.source_file" LF
"    if args.source_file ~= nil then" LF
"        src_data = am.load_file(args.source_file)" LF
"        ret = ret .. data" LF
"    end" LF
LF
"    -- Handle args.include_stdint" LF
"    if args.include_stdint then" LF
"        ret = ret .. \"#include <stdint.h>\\n#include <stddef.h>\\n\"" LF
"    end" LF
LF
"    -- Handle args.name_of_array" LF
"    if args.name_of_array == nil then" LF
"        error(\"missing argument `name_of_array`.\")" LF
"    end" LF
"    ret = ret .. \"const uint8_t \" .. args.name_of_array .. \" = {\\n\"" LF
"    local print_idx = 1" LF
"    for b in string.gmatch(src_data, '.') do" LF
"        if print_idx == 1 then" LF
"            ret = ret .. \"    \"" LF
"        end" LF
"        ret = ret .. string.format(\"0x%02x,\", string.byte(b))" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"            print_idx = 1" LF
"        else" LF
"            print_idx = print_idx + 1" LF
"        end" LF
"    end" LF
"    if args.append_eol then" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"        end" LF
"        ret = ret .. \"0x00\"" LF
"    end" LF
"    ret = ret .. \"\\n};\\n\"" LF
LF
"    -- Handle args.name_of_array_size" LF
"    if args.name_of_array_size ~= nil then" LF
"        ret = ret .. \"const size_t \" .. args.name_of_array_size .. \" = sizeof(\" .. args.name_of_array .. \")\"" LF
"        if args.append_eol then" LF
"            ret = ret .. \" - 1;\\n\"" LF
"        else" LF
"            ret = ret .. \";\\n\"" LF
"        end" LF
"    end" LF
LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = dump_hex_proc," LF
"    desc = " LF
"[[Dump anything into C array." LF
LF
"[ATTRIBUTES]" LF
"\"name_of_array\": [string]" LF
"    The name of dumped array variable." LF
"\"name_of_array_size\": [string]" LF
"    The name of dumped array size variable. If not specificed, the array" LF
"    size is not generated." LF
"\"source_file\": [string]" LF
"    The source file to dump. If not specificed, dump amalgamate content as" LF
"    hex array." LF
"\"include_stdint\": true|false. Default: false." LF
"    Set to true if need to include header file `stdint.h` and `stddef.h`." LF
"\"append_eol\": true|false. Default: true." LF
"    Whether append NULL terminal character to end of dumped array." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_c_dump_hex(lua_State* L)
{
	return am_addon_call_script(L, dump_hex_script, "c:dump_hex.lua");
}

am_addon_t am_a_c_dump_hex = {
	"c:dump_hex",
	_am_c_dump_hex,
};
/* AMALGAMATE c:expand_include addon/c_dump_hex.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/c_expand_include.c
 * SIZE:    4979
 * SHA-256: 2b7d5ff907248fa4ee421ffc6e3507cbe464c5dcd51605bb60c1c86569cdfd1d
 */
/* AMALGAMATE c:expand_include addon/c_expand_include.c [BEG] */
#line 1 "addon/c_expand_include.c"
#define LF  "\n"
static const char* expand_include_script = "\n" LF
LF
"local M = {}" LF
"-- This is the pattern to search `#include` statement." LF
"M.pattern = \"#%s*include%s+\\\"([-_/%.%w]+)\\\"\"" LF
LF
"-- Set default value if not exist" LF
"local function format_default_arguments(args)" LF
"    if args.lineno == nil then" LF
"        args.lineno = true" LF
"    end" LF
"    if args.fileinfo == nil then" LF
"        args.fileinfo = true" LF
"    end" LF
"    if args.displace_include == nil then" LF
"        args.displace_include = true" LF
"    end" LF
"    if args.quote_group == nil then" LF
"        args.quote_group = \"\"" LF
"    end" LF
"    return args" LF
"end" LF
LF
"-- Get file information for matched regex pattern" LF
"local function generate_file_info(include_path, data, args)" LF
"    local info = { include_path = include_path }" LF
"    info.real_path = am.search_file(info.include_path, args.quote_group)" LF
"    if info.real_path == nil then" LF
"        local err_msg = \"file `\" .. info.include_path .. \"` not found.\"" LF
"        error(err_msg)" LF
"    end" LF
"    info.txt_data = am.load_txt_file(info.real_path)" LF
"    info.bin_data = am.load_file(info.real_path)" LF
"    info.sha256 = am.sha256(info.bin_data)" LF
"    info.bin_size = string.len(info.bin_data)" LF
"    return info" LF
"end" LF
LF
"-- Generate file header" LF
"local function generate_file_header(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    local ret = \"/*\\n\"" LF
"    ret = ret .. \" * ADDON:   c:expand_include\\n\"" LF
"    ret = ret .. \" * PATH:    \" .. info.include_path .. \"\\n\"" LF
"    ret = ret .. \" * SIZE:    \" .. string.format(\"%q\", info.bin_size) .. \"\\n\"" LF
"    ret = ret .. \" * SHA-256: \" .. info.sha256 .. \"\\n\"" LF
"    ret = ret .. \" */\\n\"" LF
"    ret = ret .. \"/* AMALGAMATE c:expand_include \" .. info.include_path .. \" [BEG] */\\n\"" LF
"    return ret" LF
"end" LF
LF
"-- Generate file content" LF
"local function generate_file_content(info, args, regex)" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    if args.lineno then" LF
"        ret = ret .. \"#line 1 \\\"\" .. info.include_path .. \"\\\"\\n\"" LF
"    end" LF
"    if args.displace_include then" LF
"        temp = string.gsub(info.txt_data, M.pattern, \"/* AMALGAMATE_DISPLACE_INCLUDE: %1 */\")" LF
"    end" LF
"    ret = ret .. temp .. \"\\n\"" LF
"    return ret" LF
"end" LF
LF
"local function generate_file_tail(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    return \"/* AMALGAMATE c:expand_include \" .. info.include_path .. \" [END] */\\n\"" LF
"end" LF
LF
"-- c:expand_include" LF
"local function expand_include_proc(data, args)" LF
"    -- Local variable" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    local regex = M.regex" LF
LF
"    args = format_default_arguments(args)" LF
LF
"    while true do" LF
"        local off_beg, off_end, group_include = string.find(data, M.pattern)" LF
"        if off_beg == nil then" LF
"            ret = ret .. data" LF
"            break" LF
"        end" LF
LF
"        -- Append data before pattern" LF
"        if off_beg >= 2 then" LF
"            temp = string.sub(data, 1, off_beg - 1)" LF
"            ret = ret .. temp" LF
"        end" LF
LF
"        -- Get file information" LF
"        local info = generate_file_info(group_include, data, args)"
LF
"        -- Generate header" LF
"        temp = generate_file_header(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Append file content" LF
"        temp = generate_file_content(info, args)" LF
"        ret = ret .. temp" LF
LF
"        temp = generate_file_tail(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Update data" LF
"        data = string.sub(data, off_end + 1)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = expand_include_proc," LF
"    brief = \"Replace file content with #include path.\"," LF
"    desc = " LF
"[[Read #include file content and replace the #include statement."LF
LF
"[ATTRIBUTES]" LF
"\"quote_group\": [string]. Default: \"\"" LF
"    Specific which group to search." LF
"\"lineno\": true|false. Default: true." LF
"    Enable `#line 1 [path]` syntax so that if compile error, you known what" LF
"    is wrong." LF
"\"fileinfo\": true|false. Default: true" LF
"    Add file path, size, SHA-256 information before replacement." LF
"\"displace_include\": true|false. Default: true" LF
"    comment `#include \"foo.h\"`." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_c_expand_include(lua_State* L)
{
    return am_addon_call_script(L, expand_include_script, "c:expand_include.lua");
}

am_addon_t am_a_c_expand_include = {
    "c:expand_include",
    _am_c_expand_include,
};
/* AMALGAMATE c:expand_include addon/c_expand_include.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/txt_black_hole.c
 * SIZE:    587
 * SHA-256: b81ee2ebaf920f049b11b24d56361efa3b9016d63bb6d29051477a004f10c6df
 */
/* AMALGAMATE c:expand_include addon/txt_black_hole.c [BEG] */
#line 1 "addon/txt_black_hole.c"
#define LF "\n"
static const char* black_hole_script = "\n" LF
"local function black_hole_proc(data, args)" LF
"    return \"\"" LF
"end" LF
LF
"return {" LF
"    proc = black_hole_proc," LF
"    brief = \"Eliminate anything.\","
"    desc = " LF
"[[Eliminate anything." LF
LF
"[ATTRIBUTES]" LF
"none." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_txt_black_hole(lua_State* L)
{
    return am_addon_call_script(L, black_hole_script, "txt:black_hole.lua");
}

am_addon_t am_a_txt_black_hole = {
    "txt:black_hole",
    _am_txt_black_hole,
};
/* AMALGAMATE c:expand_include addon/txt_black_hole.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    amalgamate.c
 * SIZE:    3442
 * SHA-256: 199af3ab932c921cb4db661711ba1af2ea87ba7374a380af4135e1e2cbaba008
 */
/* AMALGAMATE c:expand_include amalgamate.c [BEG] */
#line 1 "amalgamate.c"
#define LF  "\n"
const char* amalgamate_script = "\n\n\n\n\n" LF // let's align the line number

//////////////////////////////////////////////////////////////////////////
// Script begin
//////////////////////////////////////////////////////////////////////////
"local cjson = require(\"cjson\")" LF
LF
"-- Process data with addon configuration" LF
"local function process_json_addon(data, config)" LF
"    config.args = config.args or {}" LF
"    if config.name == nil then" LF
"        local errmsg = \"missing field `name` in json\"" LF
"        error(errmsg)" LF
"    end" LF
"    local addon = require(config.name)" LF
"    return addon.proc(data, config.args)" LF
"end" LF
LF
"-- Process json block" LF
"local function process_json_block(v)" LF
"    local config = cjson.from_json(v.code)" LF
"    local data = v.data" LF
"    if am.table_is_array(config) then" LF
"        for _, e in ipairs(config) do" LF
"            data = process_json_addon(data, e)" LF
"        end" LF
"    else" LF
"        data = process_json_addon(data, config)" LF
"    end" LF
"    return data" LF
"end" LF
LF
"-- Process lua block" LF
"local function process_lua_block(v)" LF
"    local trunk = load(v.code)" LF
"    local b,addon = pcall(trunk)" LF
"    if b ~= true then" LF
"        error(addon)" LF
"    end" LF
"    return addon.proc(v.data, {})" LF
"end" LF
LF
"-- Preprocess file" LF
"local function preprocess(data)" LF
"    local ret = {}" LF
"    while true do" LF
"        local off_beg_0, off_end_0, group_lang, group_code, group_data" LF
"            = string.find(data, am.config.parser_pattern)" LF
"        if off_beg_0 == nil then" LF
"            ret[#ret + 1] = { data = data }" LF
"            break" LF
"        end" LF
"        if off_beg_0 > 1 then" LF
"            ret[#ret + 1] = { data = string.sub(data, 1, off_beg_0 - 1) }" LF
"        end" LF
"        ret[#ret + 1] = {" LF
"            lang = group_lang," LF
"            code = group_code," LF
"            data = group_data," LF
"        }" LF
"        data = string.sub(data, off_end_0 + 1)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"-- All runtime information" LF
"local rt = {}" LF
LF
"-- Read input file" LF
"rt.input_content = am.load_txt_file(am.config.input)" LF
LF
"-- Split input file into sequence of token" LF
"local payload = preprocess(rt.input_content)" LF
LF
"-- For each token let's do the magic" LF
"for _,v in ipairs(payload) do" LF
"    if v.lang == nil then" LF
"        -- do nothing" LF
"    elseif am.strcasecmp(v.lang, \"lua\") == 0 then" LF
"        v.data = process_lua_block(v)" LF
"    elseif am.strcasecmp(v.lang, \"json\") == 0 then" LF
"        v.data = process_json_block(v)" LF
"    else" LF
"        local err_msg = \"unknown lang `\" .. v.lang .. \"`.\"" LF
"        error(err_msg)" LF
"    end" LF
LF
"    if v.data == nil then" LF
"        v.data = \"\"" LF
"    end" LF
"end" LF
LF
"-- Generate content" LF
"rt.output_content = \"\"" LF
"for _,v in ipairs(payload) do" LF
"    rt.output_content = rt.output_content .. v.data .. \"\\n\"" LF
"end" LF
LF
"-- Write file" LF
"am.write_file(am.config.output, rt.output_content)" LF

//////////////////////////////////////////////////////////////////////////
// Script end
//////////////////////////////////////////////////////////////////////////
;

/* AMALGAMATE_DISPLACE_INCLUDE: amalgamate.h */
/* AMALGAMATE c:expand_include amalgamate.c [END] */


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
"  --iquote=GROUP:PATH\n"
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
    const char* pos = strstr(str, ":");
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
