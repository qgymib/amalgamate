#include "lua_string.h"
#include <string.h>

#if defined(_WIN32)
#	define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif

int am_strcasecmp(lua_State* L)
{
	const char* s1 = luaL_checkstring(L, 1);
	const char* s2 = luaL_checkstring(L, 2);

	int ret = strcasecmp(s1, s2);
	lua_pushnumber(L, ret);

	return 1;
}

int am_split_line(lua_State* L)
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

    return 1;
}

int am_merge_line(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TSTRING);

    lua_pushstring(L, ""); // sp:3

    lua_pushnil(L); // key:4
    while (lua_next(L, 1) != 0) // value:5
    {
        lua_pushvalue(L, 3);
        lua_pushvalue(L, 2);
        lua_pushvalue(L, 5);
        lua_concat(L, 3);
        lua_replace(L, 3);

        lua_pop(L, 1);
    }

    return 1;
}
