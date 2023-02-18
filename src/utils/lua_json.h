#ifndef __AMALGAMATE_LUA_JSON_H__
#define __AMALGAMATE_LUA_JSON_H__

#include <cJSON.h>
#include "lua_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Push an empty json object on top of Lua stack \p L.
 * @warning Do not use cJSON_Delete() to delete this object. It is managed by
 *   Lua VM.
 * @param[in] L     Lua VM.
 * @return          Json object.
 */
cJSON* lua_json_pushobject(lua_State* L);

/**
 * @brief Push an string on top of Lua stack \p L.
 * @param[in] L         Lua VM.
 * @param[in] obj       Json object.
 * @param[in] pretty    Print pretty.
 * @return              Reference to string.
 */
const char* lua_json_tostring(lua_State* L, cJSON* obj, int pretty);

/**
 * @see cJSON_AddStringToObject()
 * @see cJSON_AddNullToObject()
 */
cJSON* lua_json_add_string_to_object(lua_State* L, cJSON* const object,
    const char* const name, const char* string);

/**
 * @see cJSON_AddNullToObject()
 */
cJSON* lua_json_add_null_to_object(lua_State* L, cJSON* const object,
    const char* const name);

/**
 * @see cJSON_AddNumberToObject()
 */
cJSON* lua_json_add_number_to_object(lua_State* L, cJSON* const object,
    const char* const name, const double number);

/**
 * @brief Create an empty array, add this array to \p object, and return
 *   this array.
 * @see cJSON_AddArrayToObject()
 */
cJSON* lua_json_add_array_to_object(lua_State* L, cJSON* const object,
    const char* const name);

/**
 * @brief Create an empty object, append this object to end of \p array, and
 *   return this object.
 * @see cJSON_CreateObject()
 * @see cJSON_AddItemToArray()
 */
cJSON* lua_json_add_object_to_array(lua_State* L, cJSON* array);

#ifdef __cplusplus
}
#endif
#endif
