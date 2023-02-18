#include "__init__.h"
#include "c_comment_user_include.h"
#include "c_file_information.h"
#include <string.h>

static amalgamate_filter_t* s_filter_list[] = {
    &filter_c_comment_user_include,
    &filter_c_file_information,
};

amalgamate_filter_t* amalgamate_get_filter(lua_State* L, const char* name)
{
	size_t i;
    for (i = 0; i < sizeof(s_filter_list) / sizeof(s_filter_list[0]); i++)
    {
        amalgamate_filter_t* filter = s_filter_list[i];
        if (strcmp(name, filter->name) == 0)
        {
            return filter;
        }
    }

    luaL_error(L, "No filter named `%s'.", name);
    return NULL;
}

void amalgamate_print_filter(void)
{
    size_t i;
    const size_t list_sz = sizeof(s_filter_list) / sizeof(s_filter_list[0]);
    for (i = 0; i < list_sz; i++)
    {
        amalgamate_filter_t* filter = s_filter_list[i];
        printf("[%s]\n%s", filter->name, filter->help);

        if (i != list_sz - 1)
        {
            printf("\n");
        }
    }
}

int amalgamate_filter_error(lua_State* L, amalgamate_filter_t* filter, const char* fmt, ...)
{
    lua_pushfstring(L, "[%s]", filter->name);

    va_list ap;
    va_start(ap, fmt);
    lua_pushvfstring(L, fmt, ap);
    va_end(ap);

    lua_concat(L, 2);

    return lua_error(L);
}

void amalgamate_filter_checktype(lua_State* L, amalgamate_filter_t* filter, int idx, int type)
{
    int v_type = lua_type(L, idx);
    if (v_type == type)
    {
        return;
    }

    lua_pushfstring(L, "[%s]%s expected, got %s",
        filter->name, lua_typename(L, type), lua_typename(L, v_type));
    lua_error(L);
}
