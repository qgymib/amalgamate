#ifndef __AMALGAMATE_UTILS_LUA_SUBSTITUTE_H__
#define __AMALGAMATE_UTILS_LUA_SUBSTITUTE_H__

#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Substitute pattern with replace.
 *
 * ```lua
 * string substitute(string, pattern, replace)
 * ```
 */
int lua_substitute(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
