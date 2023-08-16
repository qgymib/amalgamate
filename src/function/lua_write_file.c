#include "__init__.h"
#include <stdio.h>

static int _am_file_op(lua_State* L, const char* path, const char* mode,
    const char* data, size_t data_sz)
{
    int ret;
    int file_need_close = 0;
    FILE* file = NULL;

    if (strcmp(path, ":stdout") == 0)
    {
        file = stdout;
    }
    else if (strcmp(path, ":stderr") == 0)
    {
        file = stderr;
    }
    else
    {
        if ((ret = fopen_s(&file, path, mode)) != 0)
        {
            char buf[64];
            strerror_r(ret, buf, sizeof(buf));
            return luaL_error(L, "open `%s` failed: %s(%d).", path, buf, ret);
        }
        file_need_close = 1;
    }

    size_t write_cnt = fwrite(data, data_sz, 1, file);
    if (file_need_close)
    {
        fclose(file);
        file = NULL;
    }

    if (write_cnt != 1)
    {
        return luaL_error(L, "write file `%s` failed.", path);
    }

    return 0;
}

static int _am_write_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 2, &data_sz);

    const char* mode = "wb";
    if (lua_type(L, 3) == LUA_TSTRING)
    {
        mode = lua_tostring(L, 3);
    }

    return _am_file_op(L, path, mode, data, data_sz);
}

am_function_t am_f_write_file = {
"write_file", _am_write_file, "nil write_file(string path, string data[, string mode])",
"Write data to file.",

"Open file and write data into it.\n"
"\n"
"By default `mode` is set to \"wb\"."
};
