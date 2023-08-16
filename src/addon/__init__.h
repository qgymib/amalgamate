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

/**
 * @brief Initialize addons as required mode.
 */
void am_addon_init(lua_State* L);

/**
 * @brief List addons
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_addon_list(lua_State* L);

/**
 * @param[in] Load manual for specific addon.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_addon_manual(lua_State* L);

/**
 * @brief Call script
 * @param[in] L         Lua VM.
 * @param[in] script    Script.
 * @param[in] name      Script name.
 * @return Always 1.
 */
int am_addon_call_script(lua_State* L, const char* script, const char* name);

/**
 * @brief Registered builtin addons
 * @{
 */
extern am_addon_t am_a_c_dump_hex;
extern am_addon_t am_a_c_expand_include;
extern am_addon_t am_a_txt_black_hole;
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
