/**
 * @file
 * A filter is a lua script that have specific hook:
 *
 * ```lua
 * return {
 *     .processer = processer
 * }
 * ```
 *
 * + `processer`
 *   
 *   The function `processer` process data in parameter `flow` and return the
 *   same layout table, it must have following protocol:
 *   
 *   ```lua
 *   flow processer(flow)
 *   ```
 *   
 *   Both parameter and return value must a table contains following field:
 *   ```
 *   {
 *       "file": [
 *           { "path": "path to file_1", "data": "content of file_1" },
 *           { "path": "path to file_2", "data": "content of file_2" }
 *       ]
 *   }
 *   ```
 */
#ifndef __AMALGAMATE_FILTER_INIT_H__
#define __AMALGAMATE_FILTER_INIT_H__

#include "utils/lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct amalgamate_filter
{
    const char*     name;   /**< Filter name. */
    lua_CFunction   entry;  /**< Filter handle. */
    const char*     help;   /**< Help string. */
} amalgamate_filter_t;

/**
 * @brief Get filter by name.
 * @param[in] L     Lua VM.
 * @param[in] name  Filter name.
 * @return          Filter handle.
 */
amalgamate_filter_t* amalgamate_get_filter(lua_State* L, const char* name);

/**
 * @brief Print filter information.
 */
void amalgamate_print_filter(void);

/**
 * @see luaL_error()
 */
int amalgamate_filter_error(lua_State* L, amalgamate_filter_t* filter, const char* fmt, ...);

/**
 * @see luaL_checktype()
 */
void amalgamate_filter_checktype(lua_State* L, amalgamate_filter_t* filter, int idx, int type);

#ifdef __cplusplus
}
#endif
#endif
