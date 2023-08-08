#include "lua_table.h"

int am_table_is_array(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);

	int ret = 0;
	if (lua_geti(L, 1, 1) != LUA_TNIL)
	{
		ret = 1;
	}
	lua_pop(L, 1);

	lua_pushboolean(L, ret);
	return 1;
}
