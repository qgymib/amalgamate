#ifndef __AMALGAMATE_LUA_FILE_H__
#define __AMALGAMATE_LUA_FILE_H__

#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

int lua_file_load(lua_State* L, const char* path);

/**
 * @brief Load file
 * @return  Always 1.
 */
int am_load_file(lua_State* L);

int am_load_txt_file(lua_State* L);

int am_is_file_exist(lua_State* L);

int am_dirname(lua_State* L);

int am_fmtpath(lua_State* L);

int am_write_file(lua_State* L);

int am_is_abs_path(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
