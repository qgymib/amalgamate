#ifndef __AMALGAMATE_LUA_DUMPHEX_H__
#define __AMALGAMATE_LUA_DUMPHEX_H__

#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dump string as hex.
 * @return	Always 1.
 */
int am_dumphex(lua_State* L);

#ifdef __cplusplus
}
#endif
#endif
