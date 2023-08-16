#include "__init__.h"
#include <stdio.h>

static int _am_is_file_exist(lua_State* L)
{
    FILE* file = NULL;
    const char* path = luaL_checkstring(L, 1);

    int ret = 1;
#if defined(_WIN32)
    if (fopen_s(&file, path, "rb") != 0)
#else
    if ((file = fopen(path, "rb")) == NULL)
#endif
    {
        ret = 0;
    }

    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }

    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_is_file_exist = {
"is_file_exist", _am_is_file_exist, "boolean is_file_exist(string path)",
"Check if file is exist.",
"Check if file is exist, return true if it is, false if not exist or cannot\n"
"access it."
};
