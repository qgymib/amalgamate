#include "__init__.h"
#include <string.h>

#if defined(_WIN32)
#   define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif

static int _am_strcasecmp(lua_State* L)
{
    const char* s1 = luaL_checkstring(L, 1);
    const char* s2 = luaL_checkstring(L, 2);

    int ret = strcasecmp(s1, s2);
    lua_pushnumber(L, ret);

    return 1;
}

am_function_t am_f_strcasecmp = {
"strcasecmp", _am_strcasecmp, "number strcasecmp(string s1, string s2)",
"Compare string ignoring the case of the characters.",

"The strcasecmp() function performs a byte-by-byte comparison of the strings `s1`\n"
"and `s2`, ignoring the case of the characters. It returns an integer less than,\n"
"equal to, or greater than zero if `s1` is found, respectively, to be less than,\n"
"to match, or be greater than `s2`."
};
