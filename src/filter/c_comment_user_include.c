#include "c_comment_user_include.h"
#include "utils/lua_substitute.h"

static int _filter_processer_c_comment_user_include(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_getfield(L, 1, "file"); /* SP + 1 */
    amalgamate_filter_checktype(L, &filter_c_comment_user_include, sp + 1, LUA_TTABLE);

    /* Foreach array. */
    lua_pushnil(L); /* SP + 2 */
    while (lua_next(L, sp + 1) != 0)
    {/* key:1-n(sp+2) val:{"path", "data"}(sp+3) */
        /* Call: lua_substitute */
        lua_pushcfunction(L, lua_substitute); /* SP + 4 */
        lua_getfield(L, sp + 3, "data"); /* SP + 5 */
        lua_pushstring(L, "^(\\s*#\\s*include\\s+\"[-.\\w/]+\")"); /* SP + 6 */
        lua_pushstring(L, "/* AMALGAMATE: $1 */"); /* SP + 7 */
        lua_call(L, 3, 1); /* SP + 4 */

        /* Replace group:file[n]:data */
        lua_setfield(L, sp + 3, "data"); /* SP + 3 */
        lua_pop(L, 1); /* SP + 2 */
    }

    lua_settop(L, sp);
    return 1;
}

static int _filter_c_comment_user_include(lua_State* L)
{
    static const luaL_Reg s_func[] = {
        { "processer",  _filter_processer_c_comment_user_include },
        { NULL,         NULL },
    };
    luaL_newlib(L, s_func);
    return 1;
}

amalgamate_filter_t filter_c_comment_user_include = {
"c:comment_user_include", _filter_c_comment_user_include,
"A filter for processing C header/source files.\n"
"It search for all user include statement and comment it out.\n",
};
