#include "lua_file.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct lua_file
{
	FILE* file;
} lua_file_t;

static int _file_gc(lua_State* L)
{
	lua_file_t* file = lua_touserdata(L, 1);
	if (file->file != NULL)
	{
		fclose(file->file);
		file->file = NULL;
	}

	return 0;
}

/**
 * @brief Open a file and push it on top of stack.
 */
static FILE* lua_fopen(lua_State* L, const char* filename, const char* mode)
{
	int errcode;
	char errbuf[256];
	lua_file_t* file = lua_newuserdata(L, sizeof(lua_file_t));
	file->file = NULL;

	static const luaL_Reg s_file_meta[] = {
		{ "__gc",       _file_gc },
		{ NULL,         NULL },
	};
	if (luaL_newmetatable(L, "__amalgamate_file") != 0)
	{
		luaL_setfuncs(L, s_file_meta, 0);
	}
	lua_setmetatable(L, -2);

	if ((errcode = fopen_s(&file->file, filename, mode)) != 0)
	{
		strerror_r(errcode, errbuf, sizeof(errbuf));
		luaL_error(L, "Cannot open file `%s': %s(%d).", filename, errbuf, errcode);
		return NULL;
	}

	return file->file;
}

int lua_file_load(lua_State* L, const char* path)
{
	int errcode;
	char errbuf[256];

	int sp = lua_gettop(L);
	FILE*  pfile = lua_fopen(L, path, "rb"); /* SP + 1 */

	const size_t bufsz = 4 * 1024;
	char* addr = lua_newuserdata(L, bufsz); /* SP + 2 */

	luaL_Buffer buf;
	luaL_buffinit(L, &buf);
	while (!feof(pfile))
	{
		if ((errcode = ferror(pfile)) != 0)
		{
			goto error;
		}

		size_t nread = fread(addr, 1, bufsz, pfile);
		luaL_addlstring(&buf, addr, nread);
	}

	luaL_pushresult(&buf); /* SP + 3 */

	/* Cleanup. */
	lua_remove(L, sp + 1); /* SP + 2 */
	lua_remove(L, sp + 2); /* SP + 1 */

	return 0;

error:
	strerror_r(errcode, errbuf, sizeof(errbuf));
	return luaL_error(L, "Cannot read file `%s': %s(%d).",
		path, errbuf, errcode);
}
