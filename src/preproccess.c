#include "preproccess.h"
#include "pcre2.lua.h"
#include <string.h>

static int _split_template(lua_State* L, int ret_idx, int src_idx)
{
    int sp = lua_gettop(L);

    static const char* pattern =
        "/\\*\\*\\n"
        " \\* @AMALGAMATE:BEG\\n"
        "```(\\w+)\\n"
        "([\\w\\W]*?)\\n"
        "```\\n"
        " \\*/\\n"
        "([\\w\\W]*?)\\n"
        "/\\*\\*\\n"
        " \\* @AMALGAMATE:END\\n"
        " \\*/";
        
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
