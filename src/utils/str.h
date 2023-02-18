#ifndef __AMALGAMATE_UTILS_STR_H__
#define __AMALGAMATE_UTILS_STR_H__

#include <stddef.h>
#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct amalgamate_str
{
	char*	data;	/**< Content data. NULL terminator is always append to end. */
	size_t	size;	/**< Content length, not including NULL terminator. */
} amalgamate_str_t;

/**
 * @brief Destroy string.
 * @param[in] str	String.
 */
void amalgamate_str_destroy(amalgamate_str_t* str);

amalgamate_str_t amalgamate_str_make(lua_State* L, const char* str);
amalgamate_str_t amalgamate_str_make_n(lua_State* L, const char* str, size_t size);

/**
 * @return	Boolean.
 */
int amalgamate_str_endwith(const amalgamate_str_t* str, const char* pat);

#ifdef __cplusplus
}
#endif
#endif // !__AMALGAMATE_UTILS_STR_H__
