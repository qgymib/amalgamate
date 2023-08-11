#include "lua_string.h"
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
