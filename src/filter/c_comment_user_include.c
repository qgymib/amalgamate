#include "c_comment_user_include.h"
#include "lua_pcre2.h"
#include <string.h>

static int _filter_processer_c_comment_user_include(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* pattern = "^(\\s*#\\s*include\\s+\"[-.\\w/]+\")";
    size_t pattern_sz = strlen(pattern);
    const char* replacement = "/* AMALGAMATE: $1 */";
    size_t replacement_sz = strlen(replacement);

    /* SP + 1 */
    lua_getfield(L, 1, "file");
    luaL_checktype(L, sp + 1, LUA_TTABLE);

    /* SP + 2 */
    lpcre2_code_t* code = lpcre2_compile(L, pattern, pattern_sz, LPCRE2_MULTILINE);

    /* Foreach array. */
    lua_pushnil(L); /* SP + 3 */
    while (lua_next(L, sp + 1) != 0)
    {/* key:1-n(sp+3) val:{"path", "data"}(sp+4) */

        lua_getfield(L, sp + 4, "data"); /* SP + 5 */

        size_t subject_sz = 0;
        const char* subject = lua_tolstring(L, sp + 5, &subject_sz);

        /* SP + 6 */
        lpcre2_substitute(L, code,
            subject, subject_sz,
            replacement, replacement_sz,
            LPCRE2_SUBSTITUTE_GLOBAL | LPCRE2_SUBSTITUTE_EXTENDED, NULL);

        /* Replace group:file[n]:data */
        lua_setfield(L, sp + 4, "data"); /* SP + 5 */
        lua_pop(L, 2); /* SP + 3 */
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
