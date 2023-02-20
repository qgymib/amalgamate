/**
 * This macro must be defined before including pcre2.h. For a program that uses
 * only one code unit width, it makes it possible to use generic function names
 * such as pcre2_compile().
 */
#define PCRE2_CODE_UNIT_WIDTH 8
 /**
  * Statically link PCRE2
  */
#define PCRE2_STATIC

#include "lua_substitute.h"
#include <pcre2.h>

int lua_substitute(lua_State* L)
{
    int ret;
    char* addr = NULL;
    luaL_Buffer buf;
    PCRE2_SIZE erroffset;
    PCRE2_SIZE outlength = 0;
    PCRE2_UCHAR message[256];

    lua_settop(L, 3);

    size_t content_sz = 0;
    const char* content = luaL_checklstring(L, 1, &content_sz);
    size_t pattern_sz = 0;
    const char* pattern = luaL_checklstring(L, 2, &pattern_sz);
    size_t replace_sz = 0;
    const char* replace = luaL_checklstring(L, 3, &replace_sz);

    pcre2_code* re_pattern = pcre2_compile((PCRE2_SPTR)pattern,
        pattern_sz,
        PCRE2_MULTILINE,
        &ret,
        &erroffset,
        NULL); /* SP + 4 */
    if (re_pattern == NULL)
    {
        pcre2_get_error_message(ret, message, sizeof(message) / sizeof(PCRE2_UCHAR));
        return luaL_error(L, "Compile `%s' failed at %u: %s.",
            pattern, (unsigned)erroffset, message);
    }

    ret = pcre2_substitute(re_pattern,
        (PCRE2_SPTR)content,
        content_sz,
        0,
        PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_OVERFLOW_LENGTH | PCRE2_SUBSTITUTE_EXTENDED,
        NULL,
        NULL,
        (PCRE2_SPTR)replace,
        replace_sz,
        NULL,
        &outlength);
    if (ret != PCRE2_ERROR_NOMEMORY)
    {
        goto error;
    }

    addr = luaL_buffinitsize(L, &buf, outlength * sizeof(PCRE2_UCHAR));

    ret = pcre2_substitute(re_pattern,
        (PCRE2_SPTR)content,
        content_sz,
        0,
        PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED,
        NULL,
        NULL,
        (PCRE2_SPTR)replace,
        replace_sz,
        (PCRE2_UCHAR*)addr,
        &outlength);
    if (ret < 0)
    {
        goto error;
    }

    luaL_addsize(&buf, outlength);
    luaL_pushresult(&buf);
    pcre2_code_free(re_pattern);

    return 1;

error:
    if (addr != NULL)
    {
        luaL_pushresult(&buf);
        lua_pop(L, 1);
        addr = NULL;
    }
    if (re_pattern != NULL)
    {
        pcre2_code_free(re_pattern);
        re_pattern = NULL;
    }
    pcre2_get_error_message(ret, message, sizeof(message) / sizeof(PCRE2_UCHAR));
    return luaL_error(L, "%s", message);
}


