#include "str.h"
#include <stdlib.h>
#include <string.h>

amalgamate_str_t amalgamate_str_make(lua_State* L, const char* str)
{
	return amalgamate_str_make_n(L, str, strlen(str));
}

amalgamate_str_t amalgamate_str_make_n(lua_State* L, const char* str, size_t size)
{
	amalgamate_str_t ret;
	ret.size = size;
	ret.data = malloc(ret.size + 1);
	if (ret.data != NULL)
	{
		memcpy(ret.data, str, size);
		ret.data[size] = '\0';
	}
	else
	{
		ERROR_OOM(L);
	}

	return ret;
}

void amalgamate_str_destroy(amalgamate_str_t* str)
{
	if (str->data != NULL)
	{
		free(str->data);
		str->data = NULL;
	}
	str->size = 0;
}

int amalgamate_str_endwith(const amalgamate_str_t* str, const char* pat)
{
	size_t pat_len = strlen(pat);
	if (pat_len > str->size)
	{
		return 0;
	}

	size_t offset = str->size - pat_len;
	return strncmp(str->data + offset, pat, pat_len) == 0;
}
