#include "__init__.h"

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
