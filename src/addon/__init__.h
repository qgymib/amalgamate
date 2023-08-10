#ifndef __AMALGAMATE_ADDON_INIT_H__
#define __AMALGAMATE_ADDON_INIT_H__

#include "function/__init__.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct am_addon
{
    const char*     name;
    lua_CFunction   open;
} am_addon_t;

void am_addon_init(lua_State* L);

int am_addon_list(lua_State* L);

int am_addon_manual(lua_State* L);

int am_addon_call_script(lua_State* L, const char* script, const char* name);

#ifdef __cplusplus
}
#endif

#endif
