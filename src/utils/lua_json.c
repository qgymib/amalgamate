#include "lua_json.h"

typedef struct lua_json
{
    cJSON* object;
} lua_json_t;

static int _json_gc(lua_State* L)
{
    lua_json_t* json = lua_touserdata(L, 1);
    if (json->object != NULL)
    {
        cJSON_Delete(json->object);
        json->object = NULL;
    }

    return 0;
}

static int _json_tostring(lua_State* L)
{
    lua_json_t* json = lua_touserdata(L, 1);
    if (json->object == NULL)
    {
        return 0;
    }

    lua_json_tostring(L, json->object, 0);

    return 1;
}

cJSON* lua_json_pushobject(lua_State* L)
{
    lua_json_t* json = lua_newuserdata(L, sizeof(lua_json_t));
    json->object = NULL;

    static const luaL_Reg s_json_meta[] = {
        { "__gc",       _json_gc },
        { "__tostring", _json_tostring },
        { NULL,         NULL },
    };
    if (luaL_newmetatable(L, "__amalgamate_json") != 0)
    {
        luaL_setfuncs(L, s_json_meta, 0);
    }
    lua_setmetatable(L, -2);

    if ((json->object = cJSON_CreateObject()) == NULL)
    {
        ERROR_OOM(L);
    }

    return json->object;
}

const char* lua_json_tostring(lua_State* L, cJSON* obj, int pretty)
{
    char* str = pretty ? cJSON_Print(obj) : cJSON_PrintUnformatted(obj);
    const char* ret = lua_pushstring(L, str);
    cJSON_free(str);
    return ret;
}

cJSON* lua_json_add_string_to_object(lua_State* L, cJSON* const object,
    const char* const name, const char* const string)
{
    cJSON* ret = (string != NULL) ?
        cJSON_AddStringToObject(object, name, string) : cJSON_AddNullToObject(object, name);
    if (ret == NULL)
    {
        ERROR_OOM(L);
    }
    return ret;
}

cJSON* lua_json_add_null_to_object(lua_State* L, cJSON* const object, const char* const name)
{
    cJSON* ret;
    if ((ret = cJSON_AddNullToObject(object, name)) == NULL)
    {
        ERROR_OOM(L);
    }
    return ret;
}

cJSON* lua_json_add_number_to_object(lua_State* L, cJSON* const object,
    const char* const name, const double number)
{
    cJSON* ret;
    if ((ret = cJSON_AddNumberToObject(object, name, number)) == NULL)
    {
        ERROR_OOM(L);
    }
    return ret;
}

cJSON* lua_json_add_array_to_object(lua_State* L, cJSON* const object,
    const char* const name)
{
    cJSON* ret;
    if ((ret = cJSON_AddArrayToObject(object, name)) == NULL)
    {
        ERROR_OOM(L);
    }
    return ret;
}

cJSON* lua_json_add_object_to_array(lua_State* L, cJSON* array)
{
    cJSON* item = cJSON_CreateObject();
    if (item == NULL)
    {
        ERROR_OOM(L);
    }
    cJSON_AddItemToArray(array, item);
    return item;
}
