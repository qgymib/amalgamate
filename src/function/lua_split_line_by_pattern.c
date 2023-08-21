#include "__init__.h"

/**
 * @see string.find
 */
static int _split_line_by_pattern_wrap_string_find(lua_State* L, int idx_s, int idx_p)
{
    int sp = lua_gettop(L);

    /* Prepare function */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, -1, "find"); // sp+2
    lua_remove(L, sp + 1); // sp+1

    /* Prepare arguments */
    lua_pushvalue(L, idx_s); // sp+2
    lua_pushvalue(L, idx_p); // sp+3

    /* Do function call */
    lua_call(L, 2, LUA_MULTRET);

    /* Check result */
    if (lua_type(L, sp + 1) == LUA_TNIL)
    {
        lua_settop(L, sp);
        return 0;
    }

    /* Return the number of values */
    int now_sp = lua_gettop(L);
    return now_sp - sp;
}

static int _split_line_by_pattern_wrap_string_sub(lua_State* L, int idx, size_t offset, size_t len)
{
    int cnt_arg = 2;
    int sp = lua_gettop(L);

    /* Prepare function */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, -1, "sub"); // sp+2
    lua_remove(L, sp + 1); // sp+1

    /* Prepare arguments */
    lua_pushvalue(L, idx);
    lua_pushinteger(L, offset + 1);
    if (len != (size_t)-1)
    {
        lua_pushinteger(L, offset + 1 + len - 1);
        cnt_arg = 3;
    }

    /* Do function call */
    lua_call(L, cnt_arg, 1);

    return 1;
}

static void _split_line_by_pattern_check_args(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TSTRING);
    luaL_checktype(L, 2, LUA_TSTRING);
    lua_settop(L, 2);
}

static size_t _split_line_by_pattern_count_line(lua_State* L, int idx)
{
    size_t cnt = 0;

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, idx, &data_sz);

    size_t i;
    for (i = 0; i < data_sz; i++)
    {
        if (data[i] == '\n')
        {
            cnt++;
        }
    }

    return cnt;
}

/**
 * @brief Push data on sp 1 into result at \p sp+2
 */
static size_t _split_line_by_pattern_push_left_on_stack(lua_State* L, int idx, size_t lineno)
{
    idx = lua_absindex(L, idx);

    lua_newtable(L);

    lua_pushvalue(L, idx);
    lua_setfield(L, -2, "data");

    lua_pushinteger(L, lineno);
    lua_setfield(L, -2, "line_beg");

    size_t cnt_line = _split_line_by_pattern_count_line(L, idx);
    lua_pushinteger(L, lineno + cnt_line);
    lua_setfield(L, -2, "line_end");

    return cnt_line;
}

static int _split_line_by_pattern(lua_State* L)
{
    _split_line_by_pattern_check_args(L);

    int sp = lua_gettop(L);
    size_t lineno = 1;

    lua_newtable(L); // sp+1: this will be the return value.

    while (1)
    {
        if (_split_line_by_pattern_wrap_string_find(L, 1, 2) == 0)
        {/* Not found */
            lineno += _split_line_by_pattern_push_left_on_stack(L, 1, lineno);
            lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);
            break;
        }
        int now_sp = lua_gettop(L); // now_sp-sp: the number of return value.

        /* Get offset */
        size_t off_beg = (size_t)lua_tonumber(L, sp + 3);
        size_t off_end = (size_t)lua_tonumber(L, sp + 4);

        if (off_beg > 1)
        {
            _split_line_by_pattern_wrap_string_sub(L, 1, off_beg - 1,
                off_end - off_beg + 1);

            lineno += _split_line_by_pattern_push_left_on_stack(L, -1, lineno);
            lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);

            lua_pop(L, 1);
        }

        lua_newtable(L);
        {
            int i;
            lua_newtable(L);
            for (i = sp + 2; i <= now_sp; i++)
            {
                lua_pushvalue(L, i);
                lua_seti(L, -2, luaL_len(L, -2) + 1);
            }
            lua_setfield(L, -2, "group");

            lua_pushinteger(L, lineno);
            lua_setfield(L, -2, "line_beg");

            _split_line_by_pattern_wrap_string_sub(L, 1, off_beg - 1, off_end - off_beg + 1);
            size_t line_cnt = _split_line_by_pattern_count_line(L, -1);
            lua_pop(L, 1);
            lua_pushinteger(L, lineno + line_cnt);
            lua_setfield(L, -2, "line_end");
        }
        lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);

        _split_line_by_pattern_wrap_string_sub(L, 1, off_end, (size_t)-1);
        lua_replace(L, 1);

        lua_settop(L, sp + 1);
    }

    return 1;
}

am_function_t am_f_split_line_by_pattern = {
"split_line_by_pattern", _split_line_by_pattern,
"table, split_line_by_pattern(string data, string pattern)",
"Split line by pattern and return the split result.",

"The result is a list contains following fields:\n"
"+ \"data\": The actual string data.\n"
"+ \"line_beg\": The start line number of the data.\n"
"+ \"line_end\": The end line number of the data.\n"
"+ \"group\": Array of captured groups if exists.\n"
"\n"
"E.g.\n"
"[\n"
"    {\n"
"        \"data\": \"The actual string data.\",\n"
"        \"line_beg\": \"The start line number of the data.\",\n"
"        \"line_end\": \"The end line number of the data.\",\n"
"        \"group\": [\n"
"            [1]= \"The first group\","
"            [2]= \"The second group\","
"            ...\n"
"        ]\n"
"    }\n,"
"    ...\n"
"]"
};
