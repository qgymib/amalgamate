#ifndef __AMALGAMATE_LUA_API_H__
#define __AMALGAMATE_LUA_API_H__

#define ERROR_OOM(L)        \
    luaL_error(L, "Out of memory.")

#define ERROR_NO_GROUP(L)   \
    luaL_error(L, "No group declared. You need to declare a group with `--group-beg'.")

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if defined(_MSC_VER)

#define strtok_r(str, delim, saveptr)   strtok_s(str, delim, saveptr)
#define strerror_r(errno,buf,len)       strerror_s(buf,len,errno)
#define strdup(s)                       _strdup(s)

#else

/**
 * @brief Opens a file.
 * @see fopen()
 * @param[out] pFile    A pointer to the file pointer that will receive the
 *   pointer to the opened file.
 * @param[in] filename  Filename.
 * @param[in] mode      Type of access permitted.
 * @return              Zero if successful; an error code on failure.
 */
int fopen_s(FILE** pFile, const char* filename, const char* mode);

#endif

int lua_foreach(lua_State* L, int idx,
    int (*cb)(lua_State* L, int idx, int key, int val, void* data), void* data);

#ifdef __cplusplus
}
#endif
#endif
