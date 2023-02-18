#include "lua_api.h"

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

int lua_foreach(lua_State* L, int idx,
    int (*cb)(lua_State* L, int idx, int key, int val, void* data), void* data)
{
    int cnt;
    int sp = lua_gettop(L);

    lua_pushnil(L); /* SP + 1 */
    for (cnt = 0; lua_next(L, idx) != 0; cnt++)
    {/* key(SP + 1), value(SP + 2) */
        if (cb(L, idx, sp + 1, sp + 2, data) != 0)
        {
            break;
        }
        lua_settop(L, sp + 1);
    }

    lua_settop(L, sp);
    return cnt;
}
