#include "__init__.h"

/**
 * @brief Check if path at \p idx is abspath.
 *
 * The stack is always unchanged.
 *
 * @return  boolean
 */
static int _am_search_file_is_abspath(lua_State* L, int idx)
{
    lua_pushcfunction(L, am_f_is_abspath.addr);
    lua_pushvalue(L, idx);
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
static int _am_search_file_is_exist(lua_State* L, int idx)
{
    lua_pushcfunction(L, am_f_is_file_exist.addr);
    lua_pushvalue(L, idx);
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
static int _am_search_file_in_directory(lua_State* L, int idx_dirname, int idx_path)
{
    int sp = lua_gettop(L);

    lua_pushvalue(L, idx_dirname);
    lua_pushstring(L, "/");
    lua_pushvalue(L, idx_path);
    lua_concat(L, 3); // sp+1

    if (_am_search_file_is_exist(L, sp + 1))
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
static int _am_serach_file_from_current_directory(lua_State* L, int idx)
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

    if (_am_search_file_in_directory(L, sp + 1, idx))
    {
        lua_remove(L, sp + 1);
        return 1;
    }

    lua_pop(L, 1);
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
static int _am_search_file_from_quote(lua_State* L, int idx)
{
    int i;
    int sp = lua_gettop(L);

    /* Get iquote table at sp+1 */
    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+1
    lua_getfield(L, -1, "config"); // sp+2
    lua_getfield(L, -1, "iquote"); // sp+3
    lua_remove(L, sp + 2); // sp+2
    lua_remove(L, sp + 1); // sp+1

    for (i = 1; ; i++)
    {
        if (lua_geti(L, sp + 1, i) != LUA_TSTRING)
        {
            lua_pop(L, 1);
            break;
        }

        if (_am_search_file_in_directory(L, sp + 2, idx))
        {
            lua_remove(L, sp + 1);
            return 1;
        }
        lua_pop(L, 1);
    }

    return 0;
}

static int _am_search_file_from_current_and_quote(lua_State* L, int idx)
{
    if (_am_serach_file_from_current_directory(L, idx))
    {
        return 1;
    }

    return _am_search_file_from_quote(L, idx);
}

static int _am_search_file(lua_State* L)
{
    /* Check for abspath */
    if (_am_search_file_is_abspath(L, 1) == 0)
    {
        return _am_search_file_from_current_and_quote(L, 1);
    }

    return !!_am_search_file_is_exist(L, 1);
}

am_function_t am_f_search_file = {
"search_file", _am_search_file, "string search_file(string path)",
"Search file in current directory and quote directory.",
"Search file in current directory and quote directory. Return the real path that\n"
"can be opened or nil if failed."
};
