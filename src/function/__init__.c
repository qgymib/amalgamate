#include "__init__.h"
#include "lua_file.h"
#include "lua_sha256.h"
#include "lua_string.h"
#include "lua_table.h"
#include <string.h>

static am_function_t* am_apis[] = {
    /* file */
    &am_func_dirname,
    &am_func_fmtpath,
    &am_func_is_abs_path,
    &am_func_is_file_exist,
    &am_func_load_file,
    &am_func_load_txt_file,
    &am_func_write_file,
    /* sha256 */
    &am_func_sha256,
    /* string */
    &am_func_strcasecmp,
    &am_func_split_line,
    &am_func_merge_line,
    &am_func_dump_hex,
    /* table */
    &am_func_table_is_array,
};

#if !defined(_MSC_VER)
int fopen_s(FILE** pFile, const char* filename, const char* mode)
{
    if ((*pFile = fopen(filename, mode)) == NULL)
    {
        return errno;
    }
    return 0;
}
#endif

int luaopen_am(lua_State* L)
{
    lua_newtable(L);

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        lua_pushcfunction(L, am_apis[i]->func);
        lua_setfield(L, -2, am_apis[i]->name);
    }

    return 1;
}

int am_list_function(lua_State* L)
{
    int sp = lua_gettop(L);
    lua_pushstring(L, ""); // sp+1

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        lua_pushvalue(L, sp + 1);
        lua_pushfstring(L, "%s\n    %s\n", am_apis[i]->name, am_apis[i]->brief);
        lua_concat(L, 2);
        lua_replace(L, sp + 1);
    }

    return 1;
}

int am_function_manual(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);

    size_t i;
    for (i = 0; i < ARRAY_SIZE(am_apis); i++)
    {
        if (strcmp(name, am_apis[i]->name) == 0)
        {
            lua_pushfstring(L,
                "[NAME]\n"
                "%s\n"
                "\n"
                "[SYNOPSIS]\n"
                "%s\n"
                "\n"
                "[BRIEF]\n"
                "%s\n"
                "\n"
                "[DOCUMENT]\n"
                "%s\n",
                am_apis[i]->name, am_apis[i]->proto, am_apis[i]->brief, am_apis[i]->document);
            return 1;
        }
    }

    return 0;
}
