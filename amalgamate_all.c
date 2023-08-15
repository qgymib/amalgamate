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
#include "pcre2.lua.h"

////////////////////////////////////////////////////////////////////////////////
// PATH:    config.h
// SIZE:    908
// SHA-256: 219905d60d6468fa83266bf4b24d2c6f981c17d697869ed6de7cd481e6b8203a
////////////////////////////////////////////////////////////////////////////////
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
    "/\\*\\*\\n"                    \
    " \\* @AMALGAMATE:BEG\\n"       \
    "```(\\w+)\\n"                  \
    "([\\w\\W]*?)\\n"               \
    "```\\n"                        \
    " \\*/\\n"                      \
    "([\\w\\W]*?)\\n"               \
    "/\\*\\*\\n"                    \
    " \\* @AMALGAMATE:END\\n"       \
    " \\*/\\n"
#endif

#ifndef AMALGAMATE_DEFAULT_OUTPUT
#define AMALGAMATE_DEFAULT_OUTPUT   ":stdout"
#endif

#ifndef AMALGAMATE_DEFAULT_LOGFILE
#define AMALGAMATE_DEFAULT_LOGFILE  ":stderr"
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/__init__.h
// SIZE:    1641
// SHA-256: 7de168dee0cd6d8fe25761fadbbc84886154606a1c5f58fb6464df5d365c95e1
////////////////////////////////////////////////////////////////////////////////
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
    lua_CFunction   func;
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

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_file.h
// SIZE:    538
// SHA-256: c44d7505271c9bd13be6295db0e2cf458b9e5202067dd458070f2c250dccb44d
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_file.h"
#ifndef __AMALGAMATE_FUNCTION_LUA_FILE_H__
#define __AMALGAMATE_FUNCTION_LUA_FILE_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_function_t am_func_dirname;
extern am_function_t am_func_fmtpath;
extern am_function_t am_func_is_abspath;
extern am_function_t am_func_is_file_exist;
extern am_function_t am_func_load_file;
extern am_function_t am_func_load_txt_file;
extern am_function_t am_func_write_file;
extern am_function_t am_func_append_file;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_log.h
// SIZE:    235
// SHA-256: b89d4872c7f66d2b0eb3e0afdfce58345c334529f7b96c3234a63c6649fbf26f
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_log.h"
#ifndef __AMALGAMATE_FUNCTION_LUA_LOG_H__
#define __AMALGAMATE_FUNCTION_LUA_LOG_H__
/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_function_t am_func_log_i;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_sha256.h
// SIZE:    244
// SHA-256: 716b4139706cd0fa0ca0365463a59babc4fcbeda99c35069d5d24d7a3f651400
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_sha256.h"
#ifndef __AMALGAMATE_FUNCTION_LUA_SHA256_H__
#define __AMALGAMATE_FUNCTION_LUA_SHA256_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_function_t am_func_sha256;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_string.h
// SIZE:    372
// SHA-256: ab8aa7d15a33272e3f59cbae91e6a7070abd4c99c185a833e38032fc20b59361
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_string.h"
#ifndef __AMALGAMATE_FUNCTION_LUA_STRING_H__
#define __AMALGAMATE_FUNCTION_LUA_STRING_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_function_t am_func_strcasecmp;
extern am_function_t am_func_split_line;
extern am_function_t am_func_merge_line;
extern am_function_t am_func_dump_hex;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_table.h
// SIZE:    250
// SHA-256: 15ebe5c2a1c4f73fb4583243cc74073c00b908f48966f5c967a6e487952cdc7a
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_table.h"
#ifndef __AMALGAMATE_FUNCTION_LUA_TABLE_H__
#define __AMALGAMATE_FUNCTION_LUA_TABLE_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_function_t am_func_table_is_array;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/__init__.h
// SIZE:    486
// SHA-256: f13acf80301c7cd7bd790336f24c45808e0e0e5ed22cfb9e016faba9e9bc0c0d
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/__init__.h"
#ifndef __AMALGAMATE_ADDON_INIT_H__
#define __AMALGAMATE_ADDON_INIT_H__

/* AMALGAMATE_DISPLACE: #include "function/__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct am_addon
{
    const char*     name;
    lua_CFunction   open;
} am_addon_t;

void am_addon_init(lua_State* L);

int am_addon_list(lua_State* L);

int am_addon_manual(lua_State* L);

int am_addon_call_script(lua_State* L, const char* script, const char* name);

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/c_dump_hex.h
// SIZE:    238
// SHA-256: a25206702d1848179a573f30ccc29efcd94cd2c5ac790edb3be0d6ab59f8d926
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/c_dump_hex.h"
#ifndef __AMALGAMATE_ADDON_C_DUMP_HEX_H__
#define __AMALGAMATE_ADDON_C_DUMP_HEX_H__
/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_addon_t am_addon_c_dump_hex;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/c_expand_include.h
// SIZE:    258
// SHA-256: 8c174b847e8671bd874122679d58f002747c1ed09f8c07b9a219f0941104cc0f
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/c_expand_include.h"
#ifndef __AMALGAMATE_ADDON_C_EXPAND_INCLUDE_H__
#define __AMALGAMATE_ADDON_C_EXPAND_INCLUDE_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_addon_t am_addon_c_expand_include;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/txt_black_hole.h
// SIZE:    252
// SHA-256: e61711dbba3028153359a8c337b259a2708e02abd15de16b6cf25221a6d0edbc
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/txt_black_hole.h"
#ifndef __AMALGAMATE_ADDON_TXT_BLACK_HOLE_H__
#define __AMALGAMATE_ADDON_TXT_BLACK_HOLE_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_addon_t am_addon_txt_black_hole;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/txt_pcre2_substitute.h
// SIZE:    270
// SHA-256: 1fc65ab28f20fd3bb8664fa06e5c4aa688a847a03b4efa04cdf15f3f29f624eb
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/txt_pcre2_substitute.h"
#ifndef __AMALGAMATE_ADDON_TXT_PCRE2_SUBSTITUTE_H__
#define __AMALGAMATE_ADDON_TXT_PCRE2_SUBSTITUTE_H__

/* AMALGAMATE_DISPLACE: #include "__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

extern am_addon_t am_addon_txt_pcre2_substitute;

#ifdef __cplusplus
}
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
// PATH:    amalgamate.h
// SIZE:    190
// SHA-256: 935d75a5b2d077d8aadfe111c57bb49fc9ce08b5887ab5321658dc2cb073f6ea
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
// PATH:    preproccess.h
// SIZE:    242
// SHA-256: e7b26401bade0010f3f53dc5a72840cb82bc99763e2cfc375e8fb68af4015f26
////////////////////////////////////////////////////////////////////////////////
#line 1 "preproccess.h"
#ifndef __AMALGAMATE_LUA_PREPROCCESS_H__
#define __AMALGAMATE_LUA_PREPROCCESS_H__

/* AMALGAMATE_DISPLACE: #include "function/__init__.h" */

#ifdef __cplusplus
extern "C" {
#endif

int am_preproccess(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif


//////////////////////////////////////////////////////////////////////////
// Embed source file
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PATH:    amalgamate.c
// SIZE:    4022
// SHA-256: 5165743a1e32e6aaaa37bdfe1a4ede5969e89d6115f5b841ecee35ad4a74cd00
////////////////////////////////////////////////////////////////////////////////
#line 1 "amalgamate.c"
#define LF  "\n"
const char* amalgamate_script = "\n\n\n\n\n" LF // let's align the line number

//////////////////////////////////////////////////////////////////////////
// Script begin
//////////////////////////////////////////////////////////////////////////
"-- @brief Dump any value as string" LF
"-- @param o Any Lua object" LF
"-- @return A string contains value of object \\p o" LF
"local function dump(o)" LF
"    if type(o) == 'table' then" LF
"        local s = '{ '" LF
"        for k,v in pairs(o) do" LF
"            if type(k) ~= 'number' then k = '\"'..k..'\"' end" LF
"            s = s .. '['..k..'] = ' .. dump(v) .. ','" LF
"        end" LF
"        return s .. '} '" LF
"    else" LF
"        return tostring(o)" LF
"    end" LF
"end" LF
"am.dump = dump" LF
LF
"-- @brief Search file in iquote table and return real path" LF
"-- @param path The file that want to search" LF
"-- @return The real path that can be opened or nil if failed" LF
"local function search_file(path)" LF
"    if am.is_abspath(path) then" LF
"        if am.is_file_exist(path) then" LF
"            return path" LF
"        else" LF
"            return nil" LF
"        end" LF
"    end" LF
"    local tmp_path = am.dirname(am.config.input) .. \"/\" .. path" LF
"    if am.is_file_exist(tmp_path) then" LF
"        return tmp_path" LF
"    end" LF
"    for _,v in ipairs(am.config.iquote) do" LF
"        tmp_path = v .. \"/\" .. path" LF
"        if am.is_file_exist(tmp_path) then" LF
"            return tmp_path" LF
"        end" LF
"    end" LF
"    return nil" LF
"end" LF
"am.search_file = search_file" LF
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
"-- Process json" LF
"local function process_json(code, data)" LF
"    local cjson = require(\"cjson\")" LF
"    local config = cjson.from_json(code)" LF
"    if am.table_is_array(config) then" LF
"        for _, v in ipairs(config) do" LF
"            data = process_json_addon(data, v)" LF
"        end" LF
"    else" LF
"        data = process_json_addon(data, config)" LF
"    end" LF
"    return data" LF
"end" LF
LF
"-- All runtime information" LF
"local rt = {}" LF
LF
"-- Read input file" LF
"rt.input_content = am.load_txt_file(am.config.input)" LF
LF
"-- Split input file into sequence of token" LF
"local payload = am.preproccess(rt.input_content)" LF
LF
"-- For each token let's do the magic" LF
"for _,v in ipairs(payload) do" LF
"    if v.lang == nil then" LF
"        -- do nothing" LF
"    elseif am.strcasecmp(v.lang, \"lua\") == 0 then" LF
"        local trunk = load(v.code)" LF
"        local b,addon = pcall(trunk)" LF
"        if b ~= true then" LF
"            error(addon)" LF
"        end" LF
"        v.data = addon.proc(v.data, {})" LF
"        if v.data == nil then" LF
"            v.data = \"\"" LF
"        end" LF
"    elseif am.strcasecmp(v.lang, \"json\") == 0 then" LF
"        v.data = process_json(v.code, v.data)" LF
"        if v.data == nil then" LF
"            v.data = \"\"" LF
"        end" LF
"    else" LF
"        local err_msg = \"unknown lang `\" .. v.lang .. \"`.\"" LF
"        error(err_msg)" LF
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

/* AMALGAMATE_DISPLACE: #include "amalgamate.h" */
////////////////////////////////////////////////////////////////////////////////
// PATH:    preproccess.c
// SIZE:    2582
// SHA-256: 49d135b1b5b4ce6bf5ef2a49104c216656fc9e7f6ac8ebd2733777deeebe9c4a
////////////////////////////////////////////////////////////////////////////////
#line 1 "preproccess.c"
/* AMALGAMATE_DISPLACE: #include "preproccess.h" */
/* AMALGAMATE_DISPLACE: #include "pcre2.lua.h" */
/* AMALGAMATE_DISPLACE: #include "config.h" */
#include <string.h>

static int _split_template(lua_State* L, int ret_idx, int src_idx)
{
    int sp = lua_gettop(L);

    static const char* pattern = AMALGAMATE_PARSER_PATTERN;
        
    lpcre2_code_t* code = lpcre2_compile(L, pattern, strlen(pattern),
        LPCRE2_MULTILINE); // sp + 1

    while (1)
    {
        size_t data_sz = 0;
        const char* data = luaL_checklstring(L, src_idx, &data_sz);

        lpcre2_match_data_t* match_data = lpcre2_match(L, code, data, data_sz, 0, 0); // sp + 2
        if (match_data == NULL)
        {/* no match */
            lua_newtable(L);

            lua_pushlstring(L, data, data_sz);
            lua_setfield(L, -2, "data");

            lua_seti(L, ret_idx, luaL_len(L, ret_idx) + 1);

            break;
        }

        size_t capture_len = 0;
        size_t capture_off = lpcre2_match_data_ovector(L, match_data, 0, &capture_len);

        /* Save content before capture */
        if (capture_off != 0)
        {
            lua_newtable(L);
            lua_pushlstring(L, data, capture_off);
            lua_setfield(L, -2, "data");
            lua_seti(L, ret_idx, luaL_len(L, ret_idx) + 1);
        }

        lua_newtable(L);
        {
            /* Save language */
            capture_off = lpcre2_match_data_ovector(L, match_data, 1, &capture_len);
            lua_pushlstring(L, data + capture_off, capture_len);
            lua_setfield(L, -2, "lang");
            /* Save code */
            capture_off = lpcre2_match_data_ovector(L, match_data, 2, &capture_len);
            lua_pushlstring(L, data + capture_off, capture_len);
            lua_setfield(L, -2, "code");
            /* Save data */
            capture_off = lpcre2_match_data_ovector(L, match_data, 3, &capture_len);
            lua_pushlstring(L, data + capture_off, capture_len);
            lua_setfield(L, -2, "data");
        }
        lua_seti(L, ret_idx, luaL_len(L, ret_idx) + 1);

        /* Replace source data */
        capture_off = lpcre2_match_data_ovector(L, match_data, 0, &capture_len);
        lua_pushlstring(L, data + capture_off + capture_len, data_sz - capture_off - capture_len);
        lua_replace(L, src_idx);

        /* Release match_data */
        lua_pop(L, 1);
    }

    lua_settop(L, sp);
    return 0;
}

int am_preproccess(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_newtable(L); // sp + 1
    _split_template(L, sp + 1, 1);

    return 1;
}
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/__init__.c
// SIZE:    2232
// SHA-256: ec1ea08f948fb304c972680985b142eaa769eb94f38f021303310c5723625454
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/__init__.c"
/* AMALGAMATE_DISPLACE: #include "__init__.h" */
/* AMALGAMATE_DISPLACE: #include "lua_file.h" */
/* AMALGAMATE_DISPLACE: #include "lua_log.h" */
/* AMALGAMATE_DISPLACE: #include "lua_sha256.h" */
/* AMALGAMATE_DISPLACE: #include "lua_string.h" */
/* AMALGAMATE_DISPLACE: #include "lua_table.h" */
#include <string.h>
#include <errno.h>

static am_function_t* am_apis[] = {
    /* file */
    &am_func_dirname,
    &am_func_fmtpath,
    &am_func_is_abspath,
    &am_func_is_file_exist,
    &am_func_load_file,
    &am_func_load_txt_file,
    &am_func_write_file,
    &am_func_append_file,
    /* log */
    &am_func_log_i,
    /* sha256 */
    &am_func_sha256,
    /* string */
    &am_func_strcasecmp,
    &am_func_split_line,
    &am_func_merge_line,
    &am_func_dump_hex,
    /* table */
    &am_func_table_is_array,
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
        lua_pushcfunction(L, am_apis[i]->func);
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
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_file.c
// SIZE:    8994
// SHA-256: a05d0c6fe7a0130576bb94ef8157ec8dab4a83066c8b2cfb2bad4c07415f59ef
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_file.c"
/* AMALGAMATE_DISPLACE: #include "lua_file.h" */
/* AMALGAMATE_DISPLACE: #include "lua_string.h" */
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
    lua_call(L, 1, 1); // sp+1

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

    return _am_file_op(L, path, "wb", data, data_sz);
}

am_function_t am_func_write_file = {
"write_file", _am_write_file, "nil write_file(string path, string data)",
"Write data to file with clear previously data.",

"Open file as binary mode and write data into it.\n"
"\n"
"If the file is not exist, the file will be created. If the file is exist, the\n"
"content of the file is cleared before write."
};

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

am_function_t am_func_is_abspath = {
"is_abspath", _am_is_abspath, "boolean is_abspath(string path)",
"Check if parameter is absolute path.",
"Check if parameter is absolute path without actually access it."
};

static int _am_append_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 2, &data_sz);

    return _am_file_op(L, path, "a+b", data, data_sz);
}

am_function_t am_func_append_file = {
"append_file", _am_append_file, "nil append_file(string path, string data)",
"Append data to file.",
"Open file as binary mode and append data into it.\n"
"\n"
"If the file is not exist, the file will be created."
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_log.c
// SIZE:    1100
// SHA-256: a8efc8ce26ac5a57b63e837892605cad024115571430d37f531ab55f9c4ea5dc
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_log.c"
/* AMALGAMATE_DISPLACE: #include "lua_log.h" */
/* AMALGAMATE_DISPLACE: #include "lua_file.h" */
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

    lua_pushcfunction(L, am_func_append_file.func); // sp=2

    lua_getglobal(L, "arg"); // sp=3
    lua_getfield(L, -1, "logfile"); //sp=4
    lua_remove(L, 3); // sp=3

    lua_pushfstring(L, "[%s:%d] ", ar.source, ar.currentline); // sp=4
    lua_pushvalue(L, 1); // sp=5
    lua_pushstring(L, "\n"); // sp=6
    lua_concat(L, 3); // sp=4

    lua_call(L, 2, 0); // sp=1

    return 0;
}

am_function_t am_func_log_i = {
"log_i", _log_i, "nil log_i(string data)",
"Append data into log file.",
"Append data into log file."
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_sha256.c
// SIZE:    7767
// SHA-256: de96732437aa84b86deb8f2a01e1909596229387f3c27838a49381294c1fb3e6
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_sha256.c"
/* AMALGAMATE_DISPLACE: #include "lua_sha256.h" */

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

am_function_t am_func_sha256 = {
"sha256", _am_sha256, "string sha256(string s)",
"Calcualte SHA-256.",

"Calcualte SHA256 of `s` and return it's string value."
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_string.c
// SIZE:    5490
// SHA-256: ba69319ad11de75e9db8deb12d6f9df460108ccdd9f873178f30ce56fb1c37ba
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_string.c"
/* AMALGAMATE_DISPLACE: #include "lua_string.h" */
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

am_function_t am_func_strcasecmp = {
"strcasecmp", _am_strcasecmp, "number strcasecmp(string s1, string s2)",
"Compare string ignoring the case of the characters.",

"The strcasecmp() function performs a byte-by-byte comparison of the strings `s1`\n"
"and `s2`, ignoring the case of the characters. It returns an integer less than,\n"
"equal to, or greater than zero if `s1` is found, respectively, to be less than,\n"
"to match, or be greater than `s2`."
};

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

am_function_t am_func_split_line = {
"split_line", _am_split_line, "table split_line(string s)",
"Split string into array.",

"Split string into array, with line wrap as token. This function automatically\n"
"take care of different endings like `\\r`, `\\n` or `\\r\\n`. Empty line is not\n"
"ignored."
};

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

am_function_t am_func_merge_line = {
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

static int _am_dumphex(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    luaL_Buffer buf;
    luaL_buffinit(L, &buf);
    mmc_dump_hex(&buf, data, data_sz, 16);
    luaL_pushresult(&buf);

    return 1;
}

am_function_t am_func_dump_hex = {
"dumphex", _am_dumphex, "string dumphex(string s)",
"Dump string as hex string.",

"Dump string as hex string with ASCII character shown.\n"
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    function/lua_table.c
// SIZE:    471
// SHA-256: 46ce57273620de44c36345d0a85c5590873e1ba0748bf27282f43d8c342d9f4e
////////////////////////////////////////////////////////////////////////////////
#line 1 "function/lua_table.c"
/* AMALGAMATE_DISPLACE: #include "lua_table.h" */

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

am_function_t am_func_table_is_array = {
"table_is_array", am_table_is_array, "boolean table_is_array(table t)",
"Check if a Lua table is array.",

"Check if parameter `t` is an array."
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/__init__.c
// SIZE:    3397
// SHA-256: 0e617800319b14a6ab821a8ae9d07e5acfc6e73a15a642c185e003a56fcfa7a8
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/__init__.c"
/* AMALGAMATE_DISPLACE: #include "__init__.h" */
/* AMALGAMATE_DISPLACE: #include "c_dump_hex.h" */
/* AMALGAMATE_DISPLACE: #include "c_expand_include.h" */
/* AMALGAMATE_DISPLACE: #include "txt_black_hole.h" */
/* AMALGAMATE_DISPLACE: #include "txt_pcre2_substitute.h" */
#include <string.h>

static am_addon_t* s_addon_list[] = {
    &am_addon_c_dump_hex,
    &am_addon_c_expand_include,
    &am_addon_txt_black_hole,
    &am_addon_txt_pcre2_substitute,
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
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/c_dump_hex.c
// SIZE:    3077
// SHA-256: 012b2dd60f83d0600f5543fcf85b51db483dac3010534f137e557be9e88d17c1
////////////////////////////////////////////////////////////////////////////////
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

/* AMALGAMATE_DISPLACE: #include "c_dump_hex.h" */

static int _am_c_dump_hex(lua_State* L)
{
	return am_addon_call_script(L, dump_hex_script, "c:dump_hex.lua");
}

am_addon_t am_addon_c_dump_hex = {
	"c:dump_hex",
	_am_c_dump_hex,
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/c_expand_include.c
// SIZE:    4647
// SHA-256: de42405b9423860c77e91b22e65098f4807c796f2d4776ce4139c295b2f3fe08
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/c_expand_include.c"
#define LF  "\n"
static const char* expand_include_script = "\n" LF
LF
"local pcre2 = require(\"pcre2\")" LF
"local M = {}" LF
"-- This is the pattern to search `#include` statement." LF
"M.pattern = \"#\\\\s*include\\\\s+\\\"([-.\\\\w/]+)\\\"\"" LF
"M.regex = pcre2.compile(M.pattern, pcre2.PCRE2_MULTILINE)" LF
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
"    return args" LF
"end" LF
LF
"-- Get file information for matched regex pattern" LF
"local function generate_file_info(match_data, data)" LF
"    local info = {}" LF
"    info.include_path = match_data:group(data, 1)" LF
"    info.real_path = am.search_file(info.include_path)" LF
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
"local function generate_header_info(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    local ret = \"\"" LF
"    ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
"    ret = ret .. \"// PATH:    \" .. info.include_path .. \"\\n\"" LF
"    ret = ret .. \"// SIZE:    \" .. string.format(\"%q\", info.bin_size) .. \"\\n\"" LF
"    ret = ret .. \"// SHA-256: \" .. info.sha256 .. \"\\n\"" LF
"    ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
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
"        temp = regex:substitute(info.txt_data, \"/* AMALGAMATE_DISPLACE: ${0} */\"," LF
"            pcre2.PCRE2_SUBSTITUTE_GLOBAL | pcre2.PCRE2_SUBSTITUTE_EXTENDED)" LF
"    end" LF
"    ret = ret .. temp .. \"\\n\"" LF
"    return ret" LF
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
"        local match_data = regex:match(data)" LF
"        if match_data == nil then" LF
"            ret = ret .. data" LF
"            break" LF
"        end" LF
LF
"        -- Append data before pattern" LF
"        local off,len = match_data:group_offset(0)" LF
"        if off >= 2 then" LF
"            temp = string.sub(data, 1, off)" LF
"            ret = ret .. temp" LF
"        end" LF
LF
"        -- Get file information" LF
"        local info = generate_file_info(match_data, data)"
LF
"        -- Generate header" LF
"        temp = generate_header_info(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Append file content" LF
"        temp = generate_file_content(info, args, regex)" LF
"        ret = ret .. temp" LF
LF
"        -- Update data" LF
"        off,len = match_data:group_offset(0)" LF
"        data = string.sub(data, off + len + 1)" LF
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
"\"lineno\": true|false. Default: true." LF
"    Enable `#line [path] 1` syntax so that if compile error, you known what" LF
"    is wrong." LF
"\"fileinfo\": true|false. Default: true" LF
"    Add file path, size, SHA-256 information before replacement." LF
"\"displace_include\": true|false. Default: true" LF
"    comment `#include \"foo.h\"`." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE: #include "c_expand_include.h" */

static int _am_c_expand_include(lua_State* L)
{
    return am_addon_call_script(L, expand_include_script, "c:expand_include.lua");
}

am_addon_t am_addon_c_expand_include = {
    "c:expand_include",
    _am_c_expand_include,
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/txt_black_hole.c
// SIZE:    597
// SHA-256: f20a2ea704bb81a7265eacbefd83e2e3dd25662b66ebea58d8e55bf4ea14f5c4
////////////////////////////////////////////////////////////////////////////////
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

/* AMALGAMATE_DISPLACE: #include "txt_black_hole.h" */

static int _am_txt_black_hole(lua_State* L)
{
    return am_addon_call_script(L, black_hole_script, "txt:black_hole.lua");
}

am_addon_t am_addon_txt_black_hole = {
    "txt:black_hole",
    _am_txt_black_hole,
};
////////////////////////////////////////////////////////////////////////////////
// PATH:    addon/txt_pcre2_substitute.c
// SIZE:    1293
// SHA-256: 40348bbccadbc291154da35738d013032fb08a3f759b9b78a7b3cc62a122e4fb
////////////////////////////////////////////////////////////////////////////////
#line 1 "addon/txt_pcre2_substitute.c"
#define LF "\n"
static const char* pcre2_substitute_script = "\n" LF
"local pcre2 = require(\"pcre2\")" LF
LF
"local function pcre2_substitute_proc(data, args)" LF
"    -- Check arguments" LF
"    if args.pattern == nil then" LF
"        error(\"missing argument `pattern`.\")" LF
"    end" LF
"    if args.replace == nil then" LF
"        error(\"missing argument `replace`.\")" LF
"    end" LF
LF
"    local code = pcre2.compile(args.pattern, pcre2.PCRE2_MULTILINE)" LF
"    return code:substitute(data, args.replace," LF
"        pcre2.PCRE2_SUBSTITUTE_GLOBAL | pcre2.PCRE2_SUBSTITUTE_EXTENDED)" LF
"end" LF
LF
"return {" LF
"    proc = pcre2_substitute_proc," LF
"    desc = " LF
"[[DESCRIPTION:" LF
"    Find and substituting a replacement string for what was matched." LF
LF
"ATTRIBUTES:" LF
"    \"pattern\": [string]" LF
"        A regex pattern for find match string." LF
"    \"replace\": [string]" LF
"        Replacement string." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE: #include "txt_pcre2_substitute.h" */

static int _am_txt_pcre2_substitute(lua_State* L)
{
    return am_addon_call_script(L, pcre2_substitute_script, "txt:pcre2_substitute.lua");
}

am_addon_t am_addon_txt_pcre2_substitute = {
    "txt:pcre2_substitute",
    _am_txt_pcre2_substitute,
};


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
"    Add the directory dir to the list of directories to be searched.\n"
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
