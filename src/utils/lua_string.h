#ifndef __AMALGAMATE_LUA_STRING_H__
#define __AMALGAMATE_LUA_STRING_H__

#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

int am_strcasecmp(lua_State* L);
int am_split_line(lua_State* L);
int am_merge_line(lua_State* L);

/**
 * @brief Dump string as hex.
 * @return	Always 1.
 */
int am_dumphex(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
