#ifndef __AMALGAMATE_FUNCTION_INIT_H__
#define __AMALGAMATE_FUNCTION_INIT_H__

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if defined(_MSC_VER)

#define strtok_r(str, delim, saveptr)   strtok_s(str, delim, saveptr)
#define strerror_r(errcode, buf, len)   strerror_s(buf,len, errcode)
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

typedef struct am_function
{
    const char*     name;
    lua_CFunction   func;
    const char*     proto;
    const char*     brief;
    const char*     document;
} am_function_t;

/**
 * @brief Push a table on top of stack that contains all functions.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int luaopen_am(lua_State* L);

/**
 * @brief Push a string on top of stack that contains all function name and brief.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_list_function(lua_State* L);

/**
 * @brief Search for function manual.
 * @param[in] L     Lua VM.
 * @return          1 if found, or 0 if not found.
 */
int am_function_manual(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
