#include "c_file_information.h"

static int _filter_processer_c_file_information_summary(lua_State* L, const char* path)
{
    int errcode;
    FILE* pfile = NULL;

    if ((errcode = fopen_s(&pfile, path, "rb")) != 0)
    {
        lua_pushfstring(L,
            "////////////////////////////////////////////////////////////////////////////////\n"
            "/// Cannot access `%s`\n"
            "////////////////////////////////////////////////////////////////////////////////\n", path);
        return 0;
    }

    fseek(pfile, 0L, SEEK_END);
    size_t pfile_sz = ftell(pfile);
    fclose(pfile);

    lua_pushfstring(L,
        "////////////////////////////////////////////////////////////////////////////////\n"
        "/// PATH: %s\n"
        "/// SIZE: %I\n"
        "////////////////////////////////////////////////////////////////////////////////\n",
        path, (lua_Integer)pfile_sz);

    return 0;
}

static int _filter_processer_c_file_information(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_getfield(L, 1, "file"); /* SP + 1 */
    luaL_checktype(L, sp + 1, LUA_TTABLE);

    /* Foreach file record. */
    lua_pushnil(L); /* SP + 2 */
    while (lua_next(L, sp + 1) != 0)
    {/* key at (SP+2) val at (SP+3) */
        /* Get file path. */
        lua_getfield(L, sp + 3, "path"); /* SP + 4 */
        const char* path = luaL_checkstring(L, sp + 4);

        /* Generate file information. */
        _filter_processer_c_file_information_summary(L, path); /* SP + 5 */

        /* Concat. */
        lua_getfield(L, sp + 3, "data"); /* SP + 6 */
        lua_concat(L, 2); /* SP + 5 */

        /* Replace file. */
        lua_setfield(L, sp + 3, "data"); /* SP + 4 */

        /* Remove remaining values. */
        lua_settop(L, sp + 2);
    }

    lua_settop(L, sp);

    return 1;
}

static int _filter_c_file_information(lua_State* L)
{
    static const luaL_Reg s_func[] = {
        { "processer",  _filter_processer_c_file_information },
        { NULL,         NULL },
    };
    luaL_newlib(L, s_func);
    return 1;
}

amalgamate_filter_t filter_c_file_information = {
"c:file_information", _filter_c_file_information,
"A filter for processing C source files.\n"
"It insert file information at the begin of each file.\n"
};
