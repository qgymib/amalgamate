#ifndef __AMALGAMATE_LUA_FILE_H__
#define __AMALGAMATE_LUA_FILE_H__

#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

int lua_file_load(lua_State* L, const char* path);

#ifdef __cplusplus
}
#endif
#endif
