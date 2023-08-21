//////////////////////////////////////////////////////////////////////////
// Version
//////////////////////////////////////////////////////////////////////////
#define AMALGAMATE_VERSION_MAJRO    1
#define AMALGAMATE_VERSION_MINOR    0
#define AMALGAMATE_VERSION_PATCH    0

//////////////////////////////////////////////////////////////////////////
// System header
//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////
// 3rd: Lua
//////////////////////////////////////////////////////////////////////////
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

//////////////////////////////////////////////////////////////////////////
// 3rd: cJSON
//////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
/*
 * ADDON:   c:expand_include
 * PATH:    cJSON.h
 * SIZE:    16122
 * SHA-256: 3f627ce5b8032c0b67624fd2f207007275108daedcde3508f1a8ef411d47f778
 */
/* AMALGAMATE c:expand_include cJSON.h [BEG] */
#line 1 "cJSON.h"
/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__

/* When compiling for windows, we specify a specific calling convention to avoid issues where we are being called from a project with a different default calling convention.  For windows you have 3 define options:

CJSON_HIDE_SYMBOLS - Define this in the case where you don't want to ever dllexport symbols
CJSON_EXPORT_SYMBOLS - Define this on library build when you want to dllexport symbols (default)
CJSON_IMPORT_SYMBOLS - Define this if you want to dllimport symbol

For *nix builds that support visibility attribute, you can define similar behavior by

setting default visibility to hidden by adding
-fvisibility=hidden (for gcc)
or
-xldscope=hidden (for sun cc)
to CFLAGS

then using the CJSON_API_VISIBILITY flag to "export" the same symbols the way CJSON_EXPORT_SYMBOLS does

*/

#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall

/* export symbols by default, this is necessary for copy pasting the C and header file */
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif

#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type)   type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllimport) type CJSON_STDCALL
#endif
#else /* !__WINDOWS__ */
#define CJSON_CDECL
#define CJSON_STDCALL

#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 15

#include <stddef.h>

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7) /* raw json */

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

/* The cJSON structure: */
typedef struct cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct cJSON *next;
    struct cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==cJSON_String  and type == cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} cJSON;

typedef struct cJSON_Hooks
{
      /* malloc/free are CDECL on Windows regardless of the default calling convention of the compiler, so ensure the hooks allow passing those functions directly. */
      void *(CJSON_CDECL *malloc_fn)(size_t sz);
      void (CJSON_CDECL *free_fn)(void *ptr);
} cJSON_Hooks;

typedef int cJSON_bool;

/* Limits how deeply nested arrays/objects can be before cJSON rejects to parse them.
 * This is to prevent stack overflows. */
#ifndef CJSON_NESTING_LIMIT
#define CJSON_NESTING_LIMIT 1000
#endif

/* returns the version of cJSON as a string */
CJSON_PUBLIC(const char*) cJSON_Version(void);

/* Supply malloc, realloc and free functions to cJSON */
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);

/* Memory Management: the caller is always responsible to free the results from all variants of cJSON_Parse (with cJSON_Delete) and cJSON_Print (with stdlib free, cJSON_Hooks.free_fn, or cJSON_free as appropriate). The exception is cJSON_PrintPreallocated, where the caller has full responsibility of the buffer. */
/* Supply a block of JSON, and this returns a cJSON object you can interrogate. */
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length);
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
/* If you supply a ptr in return_parse_end and parsing fails, then return_parse_end will contain a pointer to the error so will match cJSON_GetErrorPtr(). */
CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);

/* Render a cJSON entity to text for transfer/storage. */
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item);
/* Render a cJSON entity to text for transfer/storage without any formatting. */
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item);
/* Render a cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
/* Render a cJSON entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure. */
/* NOTE: cJSON is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need */
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
/* Delete a cJSON entity and all subentities. */
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);

/* Returns the number of items in an array (or object). */
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
/* Retrieve item number "index" from array "array". Returns NULL if unsuccessful. */
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
/* Get item "string" from object. Case insensitive. */
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds. */
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);

/* Check item type and return its value */
CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item);
CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item);

/* These functions check the type of an item */
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);

/* These calls create a cJSON item of the appropriate type. */
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
/* raw json */
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);

/* Create a string where valuestring references a string so
 * it will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
/* Create an object/array that only references it's elements so
 * they will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child);

/* These utilities create an Array of count items.
 * The parameter count cannot be greater than the number of elements in the number array, otherwise array access will be out of bounds.*/
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count);

/* Append item to the specified array/object. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the cJSON object.
 * WARNING: When this function was used, make sure to always check that (item->type & cJSON_StringIsConst) is zero before
 * writing to `item->string` */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing cJSON to a new cJSON, but don't want to corrupt your existing cJSON. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* Remove/Detach items from Arrays/Objects. */
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);

/* Update array items. */
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem); /* Shifts pre-existing items to the right. */
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);

/* Duplicate a cJSON item */
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
/* Duplicate will create a new, identical cJSON item to the one you pass, in new memory that will
 * need to be released. With recurse!=0, it will duplicate any children connected to the item.
 * The item->next and ->prev pointers are always zero on return from Duplicate. */
/* Recursively compare two cJSON items for equality. If either a or b is NULL or invalid, they will be considered unequal.
 * case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0) */
CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);

/* Minify a strings, remove blank characters(such as ' ', '\t', '\r', '\n') from strings.
 * The input pointer json cannot point to a read-only address area, such as a string constant, 
 * but should point to a readable and writable address area. */
CJSON_PUBLIC(void) cJSON_Minify(char *json);

/* Helper functions for creating and adding items to an object at the same time.
 * They return the added item or NULL on failure. */
CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name);

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
/* helper for the cJSON_SetNumberValue macro */
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number);
#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))
/* Change the valuestring of a cJSON_String object, only takes effect when type of object is cJSON_String */
CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring);

/* Macro for iterating over an array or object */
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

/* malloc/free objects using the malloc/free functions that have been set with cJSON_InitHooks */
CJSON_PUBLIC(void *) cJSON_malloc(size_t size);
CJSON_PUBLIC(void) cJSON_free(void *object);

#ifdef __cplusplus
}
#endif

#endif
/* AMALGAMATE c:expand_include cJSON.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    cJSON.c
 * SIZE:    80879
 * SHA-256: 870a3717cd02fbe747371fec920022d78bb7f625b6ace88c444c87fb61ecbdf5
 */
/* AMALGAMATE c:expand_include cJSON.c [BEG] */
#line 1 "cJSON.c"
/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* cJSON */
/* JSON parser in C. */

/* disable warnings about old C89 functions in MSVC */
#if !defined(_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
#if defined(_MSC_VER)
#pragma warning (push)
/* disable warning about single line comments in system headers */
#pragma warning (disable : 4001)
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>

#ifdef ENABLE_LOCALES
#include <locale.h>
#endif

#if defined(_MSC_VER)
#pragma warning (pop)
#endif
#ifdef __GNUC__
#pragma GCC visibility pop
#endif

/* AMALGAMATE_DISPLACE_INCLUDE: cJSON.h */

/* define our own boolean type */
#ifdef true
#undef true
#endif
#define true ((cJSON_bool)1)

#ifdef false
#undef false
#endif
#define false ((cJSON_bool)0)

/* define isnan and isinf for ANSI C, if in C99 or above, isnan and isinf has been defined in math.h */
#ifndef isinf
#define isinf(d) (isnan((d - d)) && !isnan(d))
#endif
#ifndef isnan
#define isnan(d) (d != d)
#endif

#ifndef NAN
#ifdef _WIN32
#define NAN sqrt(-1.0)
#else
#define NAN 0.0/0.0
#endif
#endif

typedef struct {
    const unsigned char *json;
    size_t position;
} error;
static error global_error = { NULL, 0 };

CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void)
{
    return (const char*) (global_error.json + global_error.position);
}

CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item) 
{
    if (!cJSON_IsString(item)) 
    {
        return NULL;
    }

    return item->valuestring;
}

CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item) 
{
    if (!cJSON_IsNumber(item)) 
    {
        return (double) NAN;
    }

    return item->valuedouble;
}

/* This is a safeguard to prevent copy-pasters from using incompatible C and header files */
#if (CJSON_VERSION_MAJOR != 1) || (CJSON_VERSION_MINOR != 7) || (CJSON_VERSION_PATCH != 15)
    #error cJSON.h and cJSON.c have different versions. Make sure that both have the same.
#endif

CJSON_PUBLIC(const char*) cJSON_Version(void)
{
    static char version[15];
    sprintf(version, "%i.%i.%i", CJSON_VERSION_MAJOR, CJSON_VERSION_MINOR, CJSON_VERSION_PATCH);

    return version;
}

/* Case insensitive string comparison, doesn't consider two NULL pointers equal though */
static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == NULL) || (string2 == NULL))
    {
        return 1;
    }

    if (string1 == string2)
    {
        return 0;
    }

    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }

    return tolower(*string1) - tolower(*string2);
}

typedef struct internal_hooks
{
    void *(CJSON_CDECL *allocate)(size_t size);
    void (CJSON_CDECL *deallocate)(void *pointer);
    void *(CJSON_CDECL *reallocate)(void *pointer, size_t size);
} internal_hooks;

#if defined(_MSC_VER)
/* work around MSVC error C2322: '...' address of dllimport '...' is not static */
static void * CJSON_CDECL internal_malloc(size_t size)
{
    return malloc(size);
}
static void CJSON_CDECL internal_free(void *pointer)
{
    free(pointer);
}
static void * CJSON_CDECL internal_realloc(void *pointer, size_t size)
{
    return realloc(pointer, size);
}
#else
#define internal_malloc malloc
#define internal_free free
#define internal_realloc realloc
#endif

/* strlen of character literals resolved at compile time */
#define static_strlen(string_literal) (sizeof(string_literal) - sizeof(""))

static internal_hooks global_hooks = { internal_malloc, internal_free, internal_realloc };

static unsigned char* cJSON_strdup(const unsigned char* string, const internal_hooks * const hooks)
{
    size_t length = 0;
    unsigned char *copy = NULL;

    if (string == NULL)
    {
        return NULL;
    }

    length = strlen((const char*)string) + sizeof("");
    copy = (unsigned char*)hooks->allocate(length);
    if (copy == NULL)
    {
        return NULL;
    }
    memcpy(copy, string, length);

    return copy;
}

CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks)
{
    if (hooks == NULL)
    {
        /* Reset hooks */
        global_hooks.allocate = malloc;
        global_hooks.deallocate = free;
        global_hooks.reallocate = realloc;
        return;
    }

    global_hooks.allocate = malloc;
    if (hooks->malloc_fn != NULL)
    {
        global_hooks.allocate = hooks->malloc_fn;
    }

    global_hooks.deallocate = free;
    if (hooks->free_fn != NULL)
    {
        global_hooks.deallocate = hooks->free_fn;
    }

    /* use realloc only if both free and malloc are used */
    global_hooks.reallocate = NULL;
    if ((global_hooks.allocate == malloc) && (global_hooks.deallocate == free))
    {
        global_hooks.reallocate = realloc;
    }
}

/* Internal constructor. */
static cJSON *cJSON_New_Item(const internal_hooks * const hooks)
{
    cJSON* node = (cJSON*)hooks->allocate(sizeof(cJSON));
    if (node)
    {
        memset(node, '\0', sizeof(cJSON));
    }

    return node;
}

/* Delete a cJSON structure. */
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item)
{
    cJSON *next = NULL;
    while (item != NULL)
    {
        next = item->next;
        if (!(item->type & cJSON_IsReference) && (item->child != NULL))
        {
            cJSON_Delete(item->child);
        }
        if (!(item->type & cJSON_IsReference) && (item->valuestring != NULL))
        {
            global_hooks.deallocate(item->valuestring);
        }
        if (!(item->type & cJSON_StringIsConst) && (item->string != NULL))
        {
            global_hooks.deallocate(item->string);
        }
        global_hooks.deallocate(item);
        item = next;
    }
}

/* get the decimal point character of the current locale */
static unsigned char get_decimal_point(void)
{
#ifdef ENABLE_LOCALES
    struct lconv *lconv = localeconv();
    return (unsigned char) lconv->decimal_point[0];
#else
    return '.';
#endif
}

typedef struct
{
    const unsigned char *content;
    size_t length;
    size_t offset;
    size_t depth; /* How deeply nested (in arrays/objects) is the input at the current offset. */
    internal_hooks hooks;
} parse_buffer;

/* check if the given size is left to read in a given parse buffer (starting with 1) */
#define can_read(buffer, size) ((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))
/* check if the buffer can be accessed at the given index (starting with 0) */
#define can_access_at_index(buffer, index) ((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))
#define cannot_access_at_index(buffer, index) (!can_access_at_index(buffer, index))
/* get a pointer to the buffer at the position */
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)

/* Parse the input text to generate a number, and populate the result into item. */
static cJSON_bool parse_number(cJSON * const item, parse_buffer * const input_buffer)
{
    double number = 0;
    unsigned char *after_end = NULL;
    unsigned char number_c_string[64];
    unsigned char decimal_point = get_decimal_point();
    size_t i = 0;

    if ((input_buffer == NULL) || (input_buffer->content == NULL))
    {
        return false;
    }

    /* copy the number into a temporary buffer and replace '.' with the decimal point
     * of the current locale (for strtod)
     * This also takes care of '\0' not necessarily being available for marking the end of the input */
    for (i = 0; (i < (sizeof(number_c_string) - 1)) && can_access_at_index(input_buffer, i); i++)
    {
        switch (buffer_at_offset(input_buffer)[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '+':
            case '-':
            case 'e':
            case 'E':
                number_c_string[i] = buffer_at_offset(input_buffer)[i];
                break;

            case '.':
                number_c_string[i] = decimal_point;
                break;

            default:
                goto loop_end;
        }
    }
loop_end:
    number_c_string[i] = '\0';

    number = strtod((const char*)number_c_string, (char**)&after_end);
    if (number_c_string == after_end)
    {
        return false; /* parse_error */
    }

    item->valuedouble = number;

    /* use saturation in case of overflow */
    if (number >= INT_MAX)
    {
        item->valueint = INT_MAX;
    }
    else if (number <= (double)INT_MIN)
    {
        item->valueint = INT_MIN;
    }
    else
    {
        item->valueint = (int)number;
    }

    item->type = cJSON_Number;

    input_buffer->offset += (size_t)(after_end - number_c_string);
    return true;
}

/* don't ask me, but the original cJSON_SetNumberValue returns an integer or double */
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number)
{
    if (number >= INT_MAX)
    {
        object->valueint = INT_MAX;
    }
    else if (number <= (double)INT_MIN)
    {
        object->valueint = INT_MIN;
    }
    else
    {
        object->valueint = (int)number;
    }

    return object->valuedouble = number;
}

CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
    char *copy = NULL;
    /* if object's type is not cJSON_String or is cJSON_IsReference, it should not set valuestring */
    if (!(object->type & cJSON_String) || (object->type & cJSON_IsReference))
    {
        return NULL;
    }
    if (strlen(valuestring) <= strlen(object->valuestring))
    {
        strcpy(object->valuestring, valuestring);
        return object->valuestring;
    }
    copy = (char*) cJSON_strdup((const unsigned char*)valuestring, &global_hooks);
    if (copy == NULL)
    {
        return NULL;
    }
    if (object->valuestring != NULL)
    {
        cJSON_free(object->valuestring);
    }
    object->valuestring = copy;

    return copy;
}

typedef struct
{
    unsigned char *buffer;
    size_t length;
    size_t offset;
    size_t depth; /* current nesting depth (for formatted printing) */
    cJSON_bool noalloc;
    cJSON_bool format; /* is this print a formatted print */
    internal_hooks hooks;
} printbuffer;

/* realloc printbuffer if necessary to have at least "needed" bytes more */
static unsigned char* ensure(printbuffer * const p, size_t needed)
{
    unsigned char *newbuffer = NULL;
    size_t newsize = 0;

    if ((p == NULL) || (p->buffer == NULL))
    {
        return NULL;
    }

    if ((p->length > 0) && (p->offset >= p->length))
    {
        /* make sure that offset is valid */
        return NULL;
    }

    if (needed > INT_MAX)
    {
        /* sizes bigger than INT_MAX are currently not supported */
        return NULL;
    }

    needed += p->offset + 1;
    if (needed <= p->length)
    {
        return p->buffer + p->offset;
    }

    if (p->noalloc) {
        return NULL;
    }

    /* calculate new buffer size */
    if (needed > (INT_MAX / 2))
    {
        /* overflow of int, use INT_MAX if possible */
        if (needed <= INT_MAX)
        {
            newsize = INT_MAX;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        newsize = needed * 2;
    }

    if (p->hooks.reallocate != NULL)
    {
        /* reallocate with realloc if available */
        newbuffer = (unsigned char*)p->hooks.reallocate(p->buffer, newsize);
        if (newbuffer == NULL)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }
    }
    else
    {
        /* otherwise reallocate manually */
        newbuffer = (unsigned char*)p->hooks.allocate(newsize);
        if (!newbuffer)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }
        
        memcpy(newbuffer, p->buffer, p->offset + 1);
        p->hooks.deallocate(p->buffer);
    }
    p->length = newsize;
    p->buffer = newbuffer;

    return newbuffer + p->offset;
}

/* calculate the new length of the string in a printbuffer and update the offset */
static void update_offset(printbuffer * const buffer)
{
    const unsigned char *buffer_pointer = NULL;
    if ((buffer == NULL) || (buffer->buffer == NULL))
    {
        return;
    }
    buffer_pointer = buffer->buffer + buffer->offset;

    buffer->offset += strlen((const char*)buffer_pointer);
}

/* securely comparison of floating-point variables */
static cJSON_bool compare_double(double a, double b)
{
    double maxVal = fabs(a) > fabs(b) ? fabs(a) : fabs(b);
    return (fabs(a - b) <= maxVal * DBL_EPSILON);
}

/* Render the number nicely from the given item into a string. */
static cJSON_bool print_number(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    double d = item->valuedouble;
    int length = 0;
    size_t i = 0;
    unsigned char number_buffer[26] = {0}; /* temporary buffer to print the number into */
    unsigned char decimal_point = get_decimal_point();
    double test = 0.0;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* This checks for NaN and Infinity */
    if (isnan(d) || isinf(d))
    {
        length = sprintf((char*)number_buffer, "null");
    }
    else
    {
        /* Try 15 decimal places of precision to avoid nonsignificant nonzero digits */
        length = sprintf((char*)number_buffer, "%1.15g", d);

        /* Check whether the original double can be recovered */
        if ((sscanf((char*)number_buffer, "%lg", &test) != 1) || !compare_double((double)test, d))
        {
            /* If not, print with 17 decimal places of precision */
            length = sprintf((char*)number_buffer, "%1.17g", d);
        }
    }

    /* sprintf failed or buffer overrun occurred */
    if ((length < 0) || (length > (int)(sizeof(number_buffer) - 1)))
    {
        return false;
    }

    /* reserve appropriate space in the output */
    output_pointer = ensure(output_buffer, (size_t)length + sizeof(""));
    if (output_pointer == NULL)
    {
        return false;
    }

    /* copy the printed number to the output and replace locale
     * dependent decimal point with '.' */
    for (i = 0; i < ((size_t)length); i++)
    {
        if (number_buffer[i] == decimal_point)
        {
            output_pointer[i] = '.';
            continue;
        }

        output_pointer[i] = number_buffer[i];
    }
    output_pointer[i] = '\0';

    output_buffer->offset += (size_t)length;

    return true;
}

/* parse 4 digit hexadecimal number */
static unsigned parse_hex4(const unsigned char * const input)
{
    unsigned int h = 0;
    size_t i = 0;

    for (i = 0; i < 4; i++)
    {
        /* parse digit */
        if ((input[i] >= '0') && (input[i] <= '9'))
        {
            h += (unsigned int) input[i] - '0';
        }
        else if ((input[i] >= 'A') && (input[i] <= 'F'))
        {
            h += (unsigned int) 10 + input[i] - 'A';
        }
        else if ((input[i] >= 'a') && (input[i] <= 'f'))
        {
            h += (unsigned int) 10 + input[i] - 'a';
        }
        else /* invalid */
        {
            return 0;
        }

        if (i < 3)
        {
            /* shift left to make place for the next nibble */
            h = h << 4;
        }
    }

    return h;
}

/* converts a UTF-16 literal to UTF-8
 * A literal can be one or two sequences of the form \uXXXX */
static unsigned char utf16_literal_to_utf8(const unsigned char * const input_pointer, const unsigned char * const input_end, unsigned char **output_pointer)
{
    long unsigned int codepoint = 0;
    unsigned int first_code = 0;
    const unsigned char *first_sequence = input_pointer;
    unsigned char utf8_length = 0;
    unsigned char utf8_position = 0;
    unsigned char sequence_length = 0;
    unsigned char first_byte_mark = 0;

    if ((input_end - first_sequence) < 6)
    {
        /* input ends unexpectedly */
        goto fail;
    }

    /* get the first utf16 sequence */
    first_code = parse_hex4(first_sequence + 2);

    /* check that the code is valid */
    if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
    {
        goto fail;
    }

    /* UTF16 surrogate pair */
    if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
    {
        const unsigned char *second_sequence = first_sequence + 6;
        unsigned int second_code = 0;
        sequence_length = 12; /* \uXXXX\uXXXX */

        if ((input_end - second_sequence) < 6)
        {
            /* input ends unexpectedly */
            goto fail;
        }

        if ((second_sequence[0] != '\\') || (second_sequence[1] != 'u'))
        {
            /* missing second half of the surrogate pair */
            goto fail;
        }

        /* get the second utf16 sequence */
        second_code = parse_hex4(second_sequence + 2);
        /* check that the code is valid */
        if ((second_code < 0xDC00) || (second_code > 0xDFFF))
        {
            /* invalid second half of the surrogate pair */
            goto fail;
        }


        /* calculate the unicode codepoint from the surrogate pair */
        codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
    }
    else
    {
        sequence_length = 6; /* \uXXXX */
        codepoint = first_code;
    }

    /* encode as UTF-8
     * takes at maximum 4 bytes to encode:
     * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (codepoint < 0x80)
    {
        /* normal ascii, encoding 0xxxxxxx */
        utf8_length = 1;
    }
    else if (codepoint < 0x800)
    {
        /* two bytes, encoding 110xxxxx 10xxxxxx */
        utf8_length = 2;
        first_byte_mark = 0xC0; /* 11000000 */
    }
    else if (codepoint < 0x10000)
    {
        /* three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx */
        utf8_length = 3;
        first_byte_mark = 0xE0; /* 11100000 */
    }
    else if (codepoint <= 0x10FFFF)
    {
        /* four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx */
        utf8_length = 4;
        first_byte_mark = 0xF0; /* 11110000 */
    }
    else
    {
        /* invalid unicode codepoint */
        goto fail;
    }

    /* encode as utf8 */
    for (utf8_position = (unsigned char)(utf8_length - 1); utf8_position > 0; utf8_position--)
    {
        /* 10xxxxxx */
        (*output_pointer)[utf8_position] = (unsigned char)((codepoint | 0x80) & 0xBF);
        codepoint >>= 6;
    }
    /* encode first byte */
    if (utf8_length > 1)
    {
        (*output_pointer)[0] = (unsigned char)((codepoint | first_byte_mark) & 0xFF);
    }
    else
    {
        (*output_pointer)[0] = (unsigned char)(codepoint & 0x7F);
    }

    *output_pointer += utf8_length;

    return sequence_length;

fail:
    return 0;
}

/* Parse the input text into an unescaped cinput, and populate item. */
static cJSON_bool parse_string(cJSON * const item, parse_buffer * const input_buffer)
{
    const unsigned char *input_pointer = buffer_at_offset(input_buffer) + 1;
    const unsigned char *input_end = buffer_at_offset(input_buffer) + 1;
    unsigned char *output_pointer = NULL;
    unsigned char *output = NULL;

    /* not a string */
    if (buffer_at_offset(input_buffer)[0] != '\"')
    {
        goto fail;
    }

    {
        /* calculate approximate size of the output (overestimate) */
        size_t allocation_length = 0;
        size_t skipped_bytes = 0;
        while (((size_t)(input_end - input_buffer->content) < input_buffer->length) && (*input_end != '\"'))
        {
            /* is escape sequence */
            if (input_end[0] == '\\')
            {
                if ((size_t)(input_end + 1 - input_buffer->content) >= input_buffer->length)
                {
                    /* prevent buffer overflow when last input character is a backslash */
                    goto fail;
                }
                skipped_bytes++;
                input_end++;
            }
            input_end++;
        }
        if (((size_t)(input_end - input_buffer->content) >= input_buffer->length) || (*input_end != '\"'))
        {
            goto fail; /* string ended unexpectedly */
        }

        /* This is at most how much we need for the output */
        allocation_length = (size_t) (input_end - buffer_at_offset(input_buffer)) - skipped_bytes;
        output = (unsigned char*)input_buffer->hooks.allocate(allocation_length + sizeof(""));
        if (output == NULL)
        {
            goto fail; /* allocation failure */
        }
    }

    output_pointer = output;
    /* loop through the string literal */
    while (input_pointer < input_end)
    {
        if (*input_pointer != '\\')
        {
            *output_pointer++ = *input_pointer++;
        }
        /* escape sequence */
        else
        {
            unsigned char sequence_length = 2;
            if ((input_end - input_pointer) < 1)
            {
                goto fail;
            }

            switch (input_pointer[1])
            {
                case 'b':
                    *output_pointer++ = '\b';
                    break;
                case 'f':
                    *output_pointer++ = '\f';
                    break;
                case 'n':
                    *output_pointer++ = '\n';
                    break;
                case 'r':
                    *output_pointer++ = '\r';
                    break;
                case 't':
                    *output_pointer++ = '\t';
                    break;
                case '\"':
                case '\\':
                case '/':
                    *output_pointer++ = input_pointer[1];
                    break;

                /* UTF-16 literal */
                case 'u':
                    sequence_length = utf16_literal_to_utf8(input_pointer, input_end, &output_pointer);
                    if (sequence_length == 0)
                    {
                        /* failed to convert UTF16-literal to UTF-8 */
                        goto fail;
                    }
                    break;

                default:
                    goto fail;
            }
            input_pointer += sequence_length;
        }
    }

    /* zero terminate the output */
    *output_pointer = '\0';

    item->type = cJSON_String;
    item->valuestring = (char*)output;

    input_buffer->offset = (size_t) (input_end - input_buffer->content);
    input_buffer->offset++;

    return true;

fail:
    if (output != NULL)
    {
        input_buffer->hooks.deallocate(output);
    }

    if (input_pointer != NULL)
    {
        input_buffer->offset = (size_t)(input_pointer - input_buffer->content);
    }

    return false;
}

/* Render the cstring provided to an escaped version that can be printed. */
static cJSON_bool print_string_ptr(const unsigned char * const input, printbuffer * const output_buffer)
{
    const unsigned char *input_pointer = NULL;
    unsigned char *output = NULL;
    unsigned char *output_pointer = NULL;
    size_t output_length = 0;
    /* numbers of additional characters needed for escaping */
    size_t escape_characters = 0;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* empty string */
    if (input == NULL)
    {
        output = ensure(output_buffer, sizeof("\"\""));
        if (output == NULL)
        {
            return false;
        }
        strcpy((char*)output, "\"\"");

        return true;
    }

    /* set "flag" to 1 if something needs to be escaped */
    for (input_pointer = input; *input_pointer; input_pointer++)
    {
        switch (*input_pointer)
        {
            case '\"':
            case '\\':
            case '\b':
            case '\f':
            case '\n':
            case '\r':
            case '\t':
                /* one character escape sequence */
                escape_characters++;
                break;
            default:
                if (*input_pointer < 32)
                {
                    /* UTF-16 escape sequence uXXXX */
                    escape_characters += 5;
                }
                break;
        }
    }
    output_length = (size_t)(input_pointer - input) + escape_characters;

    output = ensure(output_buffer, output_length + sizeof("\"\""));
    if (output == NULL)
    {
        return false;
    }

    /* no characters have to be escaped */
    if (escape_characters == 0)
    {
        output[0] = '\"';
        memcpy(output + 1, input, output_length);
        output[output_length + 1] = '\"';
        output[output_length + 2] = '\0';

        return true;
    }

    output[0] = '\"';
    output_pointer = output + 1;
    /* copy the string */
    for (input_pointer = input; *input_pointer != '\0'; (void)input_pointer++, output_pointer++)
    {
        if ((*input_pointer > 31) && (*input_pointer != '\"') && (*input_pointer != '\\'))
        {
            /* normal character, copy */
            *output_pointer = *input_pointer;
        }
        else
        {
            /* character needs to be escaped */
            *output_pointer++ = '\\';
            switch (*input_pointer)
            {
                case '\\':
                    *output_pointer = '\\';
                    break;
                case '\"':
                    *output_pointer = '\"';
                    break;
                case '\b':
                    *output_pointer = 'b';
                    break;
                case '\f':
                    *output_pointer = 'f';
                    break;
                case '\n':
                    *output_pointer = 'n';
                    break;
                case '\r':
                    *output_pointer = 'r';
                    break;
                case '\t':
                    *output_pointer = 't';
                    break;
                default:
                    /* escape and print as unicode codepoint */
                    sprintf((char*)output_pointer, "u%04x", *input_pointer);
                    output_pointer += 4;
                    break;
            }
        }
    }
    output[output_length + 1] = '\"';
    output[output_length + 2] = '\0';

    return true;
}

/* Invoke print_string_ptr (which is useful) on an item. */
static cJSON_bool print_string(const cJSON * const item, printbuffer * const p)
{
    return print_string_ptr((unsigned char*)item->valuestring, p);
}

/* Predeclare these prototypes. */
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer);

/* Utility to jump whitespace and cr/lf */
static parse_buffer *buffer_skip_whitespace(parse_buffer * const buffer)
{
    if ((buffer == NULL) || (buffer->content == NULL))
    {
        return NULL;
    }

    if (cannot_access_at_index(buffer, 0))
    {
        return buffer;
    }

    while (can_access_at_index(buffer, 0) && (buffer_at_offset(buffer)[0] <= 32))
    {
       buffer->offset++;
    }

    if (buffer->offset == buffer->length)
    {
        buffer->offset--;
    }

    return buffer;
}

/* skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer */
static parse_buffer *skip_utf8_bom(parse_buffer * const buffer)
{
    if ((buffer == NULL) || (buffer->content == NULL) || (buffer->offset != 0))
    {
        return NULL;
    }

    if (can_access_at_index(buffer, 4) && (strncmp((const char*)buffer_at_offset(buffer), "\xEF\xBB\xBF", 3) == 0))
    {
        buffer->offset += 3;
    }

    return buffer;
}

CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    size_t buffer_length;

    if (NULL == value)
    {
        return NULL;
    }

    /* Adding null character size due to require_null_terminated. */
    buffer_length = strlen(value) + sizeof("");

    return cJSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated);
}

/* Parse an object - create a new root, and populate. */
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    cJSON *item = NULL;

    /* reset error position */
    global_error.json = NULL;
    global_error.position = 0;

    if (value == NULL || 0 == buffer_length)
    {
        goto fail;
    }

    buffer.content = (const unsigned char*)value;
    buffer.length = buffer_length; 
    buffer.offset = 0;
    buffer.hooks = global_hooks;

    item = cJSON_New_Item(&global_hooks);
    if (item == NULL) /* memory fail */
    {
        goto fail;
    }

    if (!parse_value(item, buffer_skip_whitespace(skip_utf8_bom(&buffer))))
    {
        /* parse failure. ep is set. */
        goto fail;
    }

    /* if we require null-terminated JSON without appended garbage, skip and then check for a null terminator */
    if (require_null_terminated)
    {
        buffer_skip_whitespace(&buffer);
        if ((buffer.offset >= buffer.length) || buffer_at_offset(&buffer)[0] != '\0')
        {
            goto fail;
        }
    }
    if (return_parse_end)
    {
        *return_parse_end = (const char*)buffer_at_offset(&buffer);
    }

    return item;

fail:
    if (item != NULL)
    {
        cJSON_Delete(item);
    }

    if (value != NULL)
    {
        error local_error;
        local_error.json = (const unsigned char*)value;
        local_error.position = 0;

        if (buffer.offset < buffer.length)
        {
            local_error.position = buffer.offset;
        }
        else if (buffer.length > 0)
        {
            local_error.position = buffer.length - 1;
        }

        if (return_parse_end != NULL)
        {
            *return_parse_end = (const char*)local_error.json + local_error.position;
        }

        global_error = local_error;
    }

    return NULL;
}

/* Default options for cJSON_Parse */
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value)
{
    return cJSON_ParseWithOpts(value, 0, 0);
}

CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length)
{
    return cJSON_ParseWithLengthOpts(value, buffer_length, 0, 0);
}

#define cjson_min(a, b) (((a) < (b)) ? (a) : (b))

static unsigned char *print(const cJSON * const item, cJSON_bool format, const internal_hooks * const hooks)
{
    static const size_t default_buffer_size = 256;
    printbuffer buffer[1];
    unsigned char *printed = NULL;

    memset(buffer, 0, sizeof(buffer));

    /* create buffer */
    buffer->buffer = (unsigned char*) hooks->allocate(default_buffer_size);
    buffer->length = default_buffer_size;
    buffer->format = format;
    buffer->hooks = *hooks;
    if (buffer->buffer == NULL)
    {
        goto fail;
    }

    /* print the value */
    if (!print_value(item, buffer))
    {
        goto fail;
    }
    update_offset(buffer);

    /* check if reallocate is available */
    if (hooks->reallocate != NULL)
    {
        printed = (unsigned char*) hooks->reallocate(buffer->buffer, buffer->offset + 1);
        if (printed == NULL) {
            goto fail;
        }
        buffer->buffer = NULL;
    }
    else /* otherwise copy the JSON over to a new buffer */
    {
        printed = (unsigned char*) hooks->allocate(buffer->offset + 1);
        if (printed == NULL)
        {
            goto fail;
        }
        memcpy(printed, buffer->buffer, cjson_min(buffer->length, buffer->offset + 1));
        printed[buffer->offset] = '\0'; /* just to be sure */

        /* free the buffer */
        hooks->deallocate(buffer->buffer);
    }

    return printed;

fail:
    if (buffer->buffer != NULL)
    {
        hooks->deallocate(buffer->buffer);
    }

    if (printed != NULL)
    {
        hooks->deallocate(printed);
    }

    return NULL;
}

/* Render a cJSON item/entity/structure to text. */
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item)
{
    return (char*)print(item, true, &global_hooks);
}

CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item)
{
    return (char*)print(item, false, &global_hooks);
}

CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

    if (prebuffer < 0)
    {
        return NULL;
    }

    p.buffer = (unsigned char*)global_hooks.allocate((size_t)prebuffer);
    if (!p.buffer)
    {
        return NULL;
    }

    p.length = (size_t)prebuffer;
    p.offset = 0;
    p.noalloc = false;
    p.format = fmt;
    p.hooks = global_hooks;

    if (!print_value(item, &p))
    {
        global_hooks.deallocate(p.buffer);
        return NULL;
    }

    return (char*)p.buffer;
}

CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

    if ((length < 0) || (buffer == NULL))
    {
        return false;
    }

    p.buffer = (unsigned char*)buffer;
    p.length = (size_t)length;
    p.offset = 0;
    p.noalloc = true;
    p.format = format;
    p.hooks = global_hooks;

    return print_value(item, &p);
}

/* Parser core - when encountering text, process appropriately. */
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer)
{
    if ((input_buffer == NULL) || (input_buffer->content == NULL))
    {
        return false; /* no input */
    }

    /* parse the different types of values */
    /* null */
    if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "null", 4) == 0))
    {
        item->type = cJSON_NULL;
        input_buffer->offset += 4;
        return true;
    }
    /* false */
    if (can_read(input_buffer, 5) && (strncmp((const char*)buffer_at_offset(input_buffer), "false", 5) == 0))
    {
        item->type = cJSON_False;
        input_buffer->offset += 5;
        return true;
    }
    /* true */
    if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "true", 4) == 0))
    {
        item->type = cJSON_True;
        item->valueint = 1;
        input_buffer->offset += 4;
        return true;
    }
    /* string */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
    {
        return parse_string(item, input_buffer);
    }
    /* number */
    if (can_access_at_index(input_buffer, 0) && ((buffer_at_offset(input_buffer)[0] == '-') || ((buffer_at_offset(input_buffer)[0] >= '0') && (buffer_at_offset(input_buffer)[0] <= '9'))))
    {
        return parse_number(item, input_buffer);
    }
    /* array */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
    {
        return parse_array(item, input_buffer);
    }
    /* object */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
    {
        return parse_object(item, input_buffer);
    }

    return false;
}

/* Render a value to text. */
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output = NULL;

    if ((item == NULL) || (output_buffer == NULL))
    {
        return false;
    }

    switch ((item->type) & 0xFF)
    {
        case cJSON_NULL:
            output = ensure(output_buffer, 5);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "null");
            return true;

        case cJSON_False:
            output = ensure(output_buffer, 6);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "false");
            return true;

        case cJSON_True:
            output = ensure(output_buffer, 5);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "true");
            return true;

        case cJSON_Number:
            return print_number(item, output_buffer);

        case cJSON_Raw:
        {
            size_t raw_length = 0;
            if (item->valuestring == NULL)
            {
                return false;
            }

            raw_length = strlen(item->valuestring) + sizeof("");
            output = ensure(output_buffer, raw_length);
            if (output == NULL)
            {
                return false;
            }
            memcpy(output, item->valuestring, raw_length);
            return true;
        }

        case cJSON_String:
            return print_string(item, output_buffer);

        case cJSON_Array:
            return print_array(item, output_buffer);

        case cJSON_Object:
            return print_object(item, output_buffer);

        default:
            return false;
    }
}

/* Build an array from input text. */
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = NULL; /* head of the linked list */
    cJSON *current_item = NULL;

    if (input_buffer->depth >= CJSON_NESTING_LIMIT)
    {
        return false; /* to deeply nested */
    }
    input_buffer->depth++;

    if (buffer_at_offset(input_buffer)[0] != '[')
    {
        /* not an array */
        goto fail;
    }

    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ']'))
    {
        /* empty array */
        goto success;
    }

    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index(input_buffer, 0))
    {
        input_buffer->offset--;
        goto fail;
    }

    /* step back to character in front of the first element */
    input_buffer->offset--;
    /* loop through the comma separated array elements */
    do
    {
        /* allocate next item */
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == NULL)
        {
            goto fail; /* allocation failure */
        }

        /* attach next item to list */
        if (head == NULL)
        {
            /* start the linked list */
            current_item = head = new_item;
        }
        else
        {
            /* add to the end and advance */
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }

        /* parse next value */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail; /* failed to parse value */
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

    if (cannot_access_at_index(input_buffer, 0) || buffer_at_offset(input_buffer)[0] != ']')
    {
        goto fail; /* expected end of array */
    }

success:
    input_buffer->depth--;

    if (head != NULL) {
        head->prev = current_item;
    }

    item->type = cJSON_Array;
    item->child = head;

    input_buffer->offset++;

    return true;

fail:
    if (head != NULL)
    {
        cJSON_Delete(head);
    }

    return false;
}

/* Render an array to text */
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    size_t length = 0;
    cJSON *current_element = item->child;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* Compose the output array. */
    /* opening square bracket */
    output_pointer = ensure(output_buffer, 1);
    if (output_pointer == NULL)
    {
        return false;
    }

    *output_pointer = '[';
    output_buffer->offset++;
    output_buffer->depth++;

    while (current_element != NULL)
    {
        if (!print_value(current_element, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);
        if (current_element->next)
        {
            length = (size_t) (output_buffer->format ? 2 : 1);
            output_pointer = ensure(output_buffer, length + 1);
            if (output_pointer == NULL)
            {
                return false;
            }
            *output_pointer++ = ',';
            if(output_buffer->format)
            {
                *output_pointer++ = ' ';
            }
            *output_pointer = '\0';
            output_buffer->offset += length;
        }
        current_element = current_element->next;
    }

    output_pointer = ensure(output_buffer, 2);
    if (output_pointer == NULL)
    {
        return false;
    }
    *output_pointer++ = ']';
    *output_pointer = '\0';
    output_buffer->depth--;

    return true;
}

/* Build an object from the text. */
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = NULL; /* linked list head */
    cJSON *current_item = NULL;

    if (input_buffer->depth >= CJSON_NESTING_LIMIT)
    {
        return false; /* to deeply nested */
    }
    input_buffer->depth++;

    if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '{'))
    {
        goto fail; /* not an object */
    }

    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '}'))
    {
        goto success; /* empty object */
    }

    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index(input_buffer, 0))
    {
        input_buffer->offset--;
        goto fail;
    }

    /* step back to character in front of the first element */
    input_buffer->offset--;
    /* loop through the comma separated array elements */
    do
    {
        /* allocate next item */
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == NULL)
        {
            goto fail; /* allocation failure */
        }

        /* attach next item to list */
        if (head == NULL)
        {
            /* start the linked list */
            current_item = head = new_item;
        }
        else
        {
            /* add to the end and advance */
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }

        /* parse the name of the child */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_string(current_item, input_buffer))
        {
            goto fail; /* failed to parse name */
        }
        buffer_skip_whitespace(input_buffer);

        /* swap valuestring and string, because we parsed the name */
        current_item->string = current_item->valuestring;
        current_item->valuestring = NULL;

        if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != ':'))
        {
            goto fail; /* invalid object */
        }

        /* parse the value */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail; /* failed to parse value */
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

    if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '}'))
    {
        goto fail; /* expected end of object */
    }

success:
    input_buffer->depth--;

    if (head != NULL) {
        head->prev = current_item;
    }

    item->type = cJSON_Object;
    item->child = head;

    input_buffer->offset++;
    return true;

fail:
    if (head != NULL)
    {
        cJSON_Delete(head);
    }

    return false;
}

/* Render an object to text. */
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    size_t length = 0;
    cJSON *current_item = item->child;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* Compose the output: */
    length = (size_t) (output_buffer->format ? 2 : 1); /* fmt: {\n */
    output_pointer = ensure(output_buffer, length + 1);
    if (output_pointer == NULL)
    {
        return false;
    }

    *output_pointer++ = '{';
    output_buffer->depth++;
    if (output_buffer->format)
    {
        *output_pointer++ = '\n';
    }
    output_buffer->offset += length;

    while (current_item)
    {
        if (output_buffer->format)
        {
            size_t i;
            output_pointer = ensure(output_buffer, output_buffer->depth);
            if (output_pointer == NULL)
            {
                return false;
            }
            for (i = 0; i < output_buffer->depth; i++)
            {
                *output_pointer++ = '\t';
            }
            output_buffer->offset += output_buffer->depth;
        }

        /* print key */
        if (!print_string_ptr((unsigned char*)current_item->string, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);

        length = (size_t) (output_buffer->format ? 2 : 1);
        output_pointer = ensure(output_buffer, length);
        if (output_pointer == NULL)
        {
            return false;
        }
        *output_pointer++ = ':';
        if (output_buffer->format)
        {
            *output_pointer++ = '\t';
        }
        output_buffer->offset += length;

        /* print value */
        if (!print_value(current_item, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);

        /* print comma if not last */
        length = ((size_t)(output_buffer->format ? 1 : 0) + (size_t)(current_item->next ? 1 : 0));
        output_pointer = ensure(output_buffer, length + 1);
        if (output_pointer == NULL)
        {
            return false;
        }
        if (current_item->next)
        {
            *output_pointer++ = ',';
        }

        if (output_buffer->format)
        {
            *output_pointer++ = '\n';
        }
        *output_pointer = '\0';
        output_buffer->offset += length;

        current_item = current_item->next;
    }

    output_pointer = ensure(output_buffer, output_buffer->format ? (output_buffer->depth + 1) : 2);
    if (output_pointer == NULL)
    {
        return false;
    }
    if (output_buffer->format)
    {
        size_t i;
        for (i = 0; i < (output_buffer->depth - 1); i++)
        {
            *output_pointer++ = '\t';
        }
    }
    *output_pointer++ = '}';
    *output_pointer = '\0';
    output_buffer->depth--;

    return true;
}

/* Get Array size/item / object item. */
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array)
{
    cJSON *child = NULL;
    size_t size = 0;

    if (array == NULL)
    {
        return 0;
    }

    child = array->child;

    while(child != NULL)
    {
        size++;
        child = child->next;
    }

    /* FIXME: Can overflow here. Cannot be fixed without breaking the API */

    return (int)size;
}

static cJSON* get_array_item(const cJSON *array, size_t index)
{
    cJSON *current_child = NULL;

    if (array == NULL)
    {
        return NULL;
    }

    current_child = array->child;
    while ((current_child != NULL) && (index > 0))
    {
        index--;
        current_child = current_child->next;
    }

    return current_child;
}

CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index)
{
    if (index < 0)
    {
        return NULL;
    }

    return get_array_item(array, (size_t)index);
}

static cJSON *get_object_item(const cJSON * const object, const char * const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element = NULL;

    if ((object == NULL) || (name == NULL))
    {
        return NULL;
    }

    current_element = object->child;
    if (case_sensitive)
    {
        while ((current_element != NULL) && (current_element->string != NULL) && (strcmp(name, current_element->string) != 0))
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while ((current_element != NULL) && (case_insensitive_strcmp((const unsigned char*)name, (const unsigned char*)(current_element->string)) != 0))
        {
            current_element = current_element->next;
        }
    }

    if ((current_element == NULL) || (current_element->string == NULL)) {
        return NULL;
    }

    return current_element;
}

CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, false);
}

CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, true);
}

CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string)
{
    return cJSON_GetObjectItem(object, string) ? 1 : 0;
}

/* Utility for array list handling. */
static void suffix_object(cJSON *prev, cJSON *item)
{
    prev->next = item;
    item->prev = prev;
}

/* Utility for handling references. */
static cJSON *create_reference(const cJSON *item, const internal_hooks * const hooks)
{
    cJSON *reference = NULL;
    if (item == NULL)
    {
        return NULL;
    }

    reference = cJSON_New_Item(hooks);
    if (reference == NULL)
    {
        return NULL;
    }

    memcpy(reference, item, sizeof(cJSON));
    reference->string = NULL;
    reference->type |= cJSON_IsReference;
    reference->next = reference->prev = NULL;
    return reference;
}

static cJSON_bool add_item_to_array(cJSON *array, cJSON *item)
{
    cJSON *child = NULL;

    if ((item == NULL) || (array == NULL) || (array == item))
    {
        return false;
    }

    child = array->child;
    /*
     * To find the last item in array quickly, we use prev in array
     */
    if (child == NULL)
    {
        /* list is empty, start new one */
        array->child = item;
        item->prev = item;
        item->next = NULL;
    }
    else
    {
        /* append to the end */
        if (child->prev)
        {
            suffix_object(child->prev, item);
            array->child->prev = item;
        }
    }

    return true;
}

/* Add item to array/object. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return add_item_to_array(array, item);
}

#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
    #pragma GCC diagnostic push
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
/* helper function to cast away const */
static void* cast_away_const(const void* string)
{
    return (void*)string;
}
#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
    #pragma GCC diagnostic pop
#endif


static cJSON_bool add_item_to_object(cJSON * const object, const char * const string, cJSON * const item, const internal_hooks * const hooks, const cJSON_bool constant_key)
{
    char *new_key = NULL;
    int new_type = cJSON_Invalid;

    if ((object == NULL) || (string == NULL) || (item == NULL) || (object == item))
    {
        return false;
    }

    if (constant_key)
    {
        new_key = (char*)cast_away_const(string);
        new_type = item->type | cJSON_StringIsConst;
    }
    else
    {
        new_key = (char*)cJSON_strdup((const unsigned char*)string, hooks);
        if (new_key == NULL)
        {
            return false;
        }

        new_type = item->type & ~cJSON_StringIsConst;
    }

    if (!(item->type & cJSON_StringIsConst) && (item->string != NULL))
    {
        hooks->deallocate(item->string);
    }

    item->string = new_key;
    item->type = new_type;

    return add_item_to_array(object, item);
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, false);
}

/* Add an item to an object with constant string as key */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, true);
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)
{
    if (array == NULL)
    {
        return false;
    }

    return add_item_to_array(array, create_reference(item, &global_hooks));
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item)
{
    if ((object == NULL) || (string == NULL))
    {
        return false;
    }

    return add_item_to_object(object, string, create_reference(item, &global_hooks), &global_hooks, false);
}

CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name)
{
    cJSON *null = cJSON_CreateNull();
    if (add_item_to_object(object, name, null, &global_hooks, false))
    {
        return null;
    }

    cJSON_Delete(null);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name)
{
    cJSON *true_item = cJSON_CreateTrue();
    if (add_item_to_object(object, name, true_item, &global_hooks, false))
    {
        return true_item;
    }

    cJSON_Delete(true_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name)
{
    cJSON *false_item = cJSON_CreateFalse();
    if (add_item_to_object(object, name, false_item, &global_hooks, false))
    {
        return false_item;
    }

    cJSON_Delete(false_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean)
{
    cJSON *bool_item = cJSON_CreateBool(boolean);
    if (add_item_to_object(object, name, bool_item, &global_hooks, false))
    {
        return bool_item;
    }

    cJSON_Delete(bool_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number)
{
    cJSON *number_item = cJSON_CreateNumber(number);
    if (add_item_to_object(object, name, number_item, &global_hooks, false))
    {
        return number_item;
    }

    cJSON_Delete(number_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string)
{
    cJSON *string_item = cJSON_CreateString(string);
    if (add_item_to_object(object, name, string_item, &global_hooks, false))
    {
        return string_item;
    }

    cJSON_Delete(string_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw)
{
    cJSON *raw_item = cJSON_CreateRaw(raw);
    if (add_item_to_object(object, name, raw_item, &global_hooks, false))
    {
        return raw_item;
    }

    cJSON_Delete(raw_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name)
{
    cJSON *object_item = cJSON_CreateObject();
    if (add_item_to_object(object, name, object_item, &global_hooks, false))
    {
        return object_item;
    }

    cJSON_Delete(object_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name)
{
    cJSON *array = cJSON_CreateArray();
    if (add_item_to_object(object, name, array, &global_hooks, false))
    {
        return array;
    }

    cJSON_Delete(array);
    return NULL;
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item)
{
    if ((parent == NULL) || (item == NULL))
    {
        return NULL;
    }

    if (item != parent->child)
    {
        /* not the first element */
        item->prev->next = item->next;
    }
    if (item->next != NULL)
    {
        /* not the last element */
        item->next->prev = item->prev;
    }

    if (item == parent->child)
    {
        /* first element */
        parent->child = item->next;
    }
    else if (item->next == NULL)
    {
        /* last element */
        parent->child->prev = item->prev;
    }

    /* make sure the detached item doesn't point anywhere anymore */
    item->prev = NULL;
    item->next = NULL;

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which)
{
    if (which < 0)
    {
        return NULL;
    }

    return cJSON_DetachItemViaPointer(array, get_array_item(array, (size_t)which));
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which)
{
    cJSON_Delete(cJSON_DetachItemFromArray(array, which));
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItem(object, string);

    return cJSON_DetachItemViaPointer(object, to_detach);
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItemCaseSensitive(object, string);

    return cJSON_DetachItemViaPointer(object, to_detach);
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObject(object, string));
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObjectCaseSensitive(object, string));
}

/* Replace array/object items with new ones. */
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *after_inserted = NULL;

    if (which < 0)
    {
        return false;
    }

    after_inserted = get_array_item(array, (size_t)which);
    if (after_inserted == NULL)
    {
        return add_item_to_array(array, newitem);
    }

    newitem->next = after_inserted;
    newitem->prev = after_inserted->prev;
    after_inserted->prev = newitem;
    if (after_inserted == array->child)
    {
        array->child = newitem;
    }
    else
    {
        newitem->prev->next = newitem;
    }
    return true;
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement)
{
    if ((parent == NULL) || (replacement == NULL) || (item == NULL))
    {
        return false;
    }

    if (replacement == item)
    {
        return true;
    }

    replacement->next = item->next;
    replacement->prev = item->prev;

    if (replacement->next != NULL)
    {
        replacement->next->prev = replacement;
    }
    if (parent->child == item)
    {
        if (parent->child->prev == parent->child)
        {
            replacement->prev = replacement;
        }
        parent->child = replacement;
    }
    else
    {   /*
         * To find the last item in array quickly, we use prev in array.
         * We can't modify the last item's next pointer where this item was the parent's child
         */
        if (replacement->prev != NULL)
        {
            replacement->prev->next = replacement;
        }
        if (replacement->next == NULL)
        {
            parent->child->prev = replacement;
        }
    }

    item->next = NULL;
    item->prev = NULL;
    cJSON_Delete(item);

    return true;
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem)
{
    if (which < 0)
    {
        return false;
    }

    return cJSON_ReplaceItemViaPointer(array, get_array_item(array, (size_t)which), newitem);
}

static cJSON_bool replace_item_in_object(cJSON *object, const char *string, cJSON *replacement, cJSON_bool case_sensitive)
{
    if ((replacement == NULL) || (string == NULL))
    {
        return false;
    }

    /* replace the name in the replacement */
    if (!(replacement->type & cJSON_StringIsConst) && (replacement->string != NULL))
    {
        cJSON_free(replacement->string);
    }
    replacement->string = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
    replacement->type &= ~cJSON_StringIsConst;

    return cJSON_ReplaceItemViaPointer(object, get_object_item(object, string, case_sensitive), replacement);
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, false);
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, true);
}

/* Create basic types: */
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_NULL;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_True;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_False;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = boolean ? cJSON_True : cJSON_False;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_Number;
        item->valuedouble = num;

        /* use saturation in case of overflow */
        if (num >= INT_MAX)
        {
            item->valueint = INT_MAX;
        }
        else if (num <= (double)INT_MIN)
        {
            item->valueint = INT_MIN;
        }
        else
        {
            item->valueint = (int)num;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_String;
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return NULL;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL)
    {
        item->type = cJSON_String | cJSON_IsReference;
        item->valuestring = (char*)cast_away_const(string);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL) {
        item->type = cJSON_Object | cJSON_IsReference;
        item->child = (cJSON*)cast_away_const(child);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child) {
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL) {
        item->type = cJSON_Array | cJSON_IsReference;
        item->child = (cJSON*)cast_away_const(child);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_Raw;
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)raw, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return NULL;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type=cJSON_Array;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item)
    {
        item->type = cJSON_Object;
    }

    return item;
}

/* Create Arrays: */
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if (!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber((double)numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (strings == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for (i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateString(strings[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p,n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }
    
    return a;
}

/* Duplication */
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse)
{
    cJSON *newitem = NULL;
    cJSON *child = NULL;
    cJSON *next = NULL;
    cJSON *newchild = NULL;

    /* Bail on bad ptr */
    if (!item)
    {
        goto fail;
    }
    /* Create new item */
    newitem = cJSON_New_Item(&global_hooks);
    if (!newitem)
    {
        goto fail;
    }
    /* Copy over all vars */
    newitem->type = item->type & (~cJSON_IsReference);
    newitem->valueint = item->valueint;
    newitem->valuedouble = item->valuedouble;
    if (item->valuestring)
    {
        newitem->valuestring = (char*)cJSON_strdup((unsigned char*)item->valuestring, &global_hooks);
        if (!newitem->valuestring)
        {
            goto fail;
        }
    }
    if (item->string)
    {
        newitem->string = (item->type&cJSON_StringIsConst) ? item->string : (char*)cJSON_strdup((unsigned char*)item->string, &global_hooks);
        if (!newitem->string)
        {
            goto fail;
        }
    }
    /* If non-recursive, then we're done! */
    if (!recurse)
    {
        return newitem;
    }
    /* Walk the ->next chain for the child. */
    child = item->child;
    while (child != NULL)
    {
        newchild = cJSON_Duplicate(child, true); /* Duplicate (with recurse) each item in the ->next chain */
        if (!newchild)
        {
            goto fail;
        }
        if (next != NULL)
        {
            /* If newitem->child already set, then crosswire ->prev and ->next and move on */
            next->next = newchild;
            newchild->prev = next;
            next = newchild;
        }
        else
        {
            /* Set newitem->child and move to it */
            newitem->child = newchild;
            next = newchild;
        }
        child = child->next;
    }
    if (newitem && newitem->child)
    {
        newitem->child->prev = newchild;
    }

    return newitem;

fail:
    if (newitem != NULL)
    {
        cJSON_Delete(newitem);
    }

    return NULL;
}

static void skip_oneline_comment(char **input)
{
    *input += static_strlen("//");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if ((*input)[0] == '\n') {
            *input += static_strlen("\n");
            return;
        }
    }
}

static void skip_multiline_comment(char **input)
{
    *input += static_strlen("/*");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if (((*input)[0] == '*') && ((*input)[1] == '/'))
        {
            *input += static_strlen("*/");
            return;
        }
    }
}

static void minify_string(char **input, char **output) {
    (*output)[0] = (*input)[0];
    *input += static_strlen("\"");
    *output += static_strlen("\"");


    for (; (*input)[0] != '\0'; (void)++(*input), ++(*output)) {
        (*output)[0] = (*input)[0];

        if ((*input)[0] == '\"') {
            (*output)[0] = '\"';
            *input += static_strlen("\"");
            *output += static_strlen("\"");
            return;
        } else if (((*input)[0] == '\\') && ((*input)[1] == '\"')) {
            (*output)[1] = (*input)[1];
            *input += static_strlen("\"");
            *output += static_strlen("\"");
        }
    }
}

CJSON_PUBLIC(void) cJSON_Minify(char *json)
{
    char *into = json;

    if (json == NULL)
    {
        return;
    }

    while (json[0] != '\0')
    {
        switch (json[0])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                json++;
                break;

            case '/':
                if (json[1] == '/')
                {
                    skip_oneline_comment(&json);
                }
                else if (json[1] == '*')
                {
                    skip_multiline_comment(&json);
                } else {
                    json++;
                }
                break;

            case '\"':
                minify_string(&json, (char**)&into);
                break;

            default:
                into[0] = json[0];
                json++;
                into++;
        }
    }

    /* and null-terminate. */
    *into = '\0';
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Invalid;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_False;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xff) == cJSON_True;
}


CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & (cJSON_True | cJSON_False)) != 0;
}
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_NULL;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Number;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_String;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Array;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Object;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Raw;
}

CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive)
{
    if ((a == NULL) || (b == NULL) || ((a->type & 0xFF) != (b->type & 0xFF)))
    {
        return false;
    }

    /* check if type is valid */
    switch (a->type & 0xFF)
    {
        case cJSON_False:
        case cJSON_True:
        case cJSON_NULL:
        case cJSON_Number:
        case cJSON_String:
        case cJSON_Raw:
        case cJSON_Array:
        case cJSON_Object:
            break;

        default:
            return false;
    }

    /* identical objects are equal */
    if (a == b)
    {
        return true;
    }

    switch (a->type & 0xFF)
    {
        /* in these cases and equal type is enough */
        case cJSON_False:
        case cJSON_True:
        case cJSON_NULL:
            return true;

        case cJSON_Number:
            if (compare_double(a->valuedouble, b->valuedouble))
            {
                return true;
            }
            return false;

        case cJSON_String:
        case cJSON_Raw:
            if ((a->valuestring == NULL) || (b->valuestring == NULL))
            {
                return false;
            }
            if (strcmp(a->valuestring, b->valuestring) == 0)
            {
                return true;
            }

            return false;

        case cJSON_Array:
        {
            cJSON *a_element = a->child;
            cJSON *b_element = b->child;

            for (; (a_element != NULL) && (b_element != NULL);)
            {
                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return false;
                }

                a_element = a_element->next;
                b_element = b_element->next;
            }

            /* one of the arrays is longer than the other */
            if (a_element != b_element) {
                return false;
            }

            return true;
        }

        case cJSON_Object:
        {
            cJSON *a_element = NULL;
            cJSON *b_element = NULL;
            cJSON_ArrayForEach(a_element, a)
            {
                /* TODO This has O(n^2) runtime, which is horrible! */
                b_element = get_object_item(b, a_element->string, case_sensitive);
                if (b_element == NULL)
                {
                    return false;
                }

                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return false;
                }
            }

            /* doing this twice, once on a and b to prevent true comparison if a subset of b
             * TODO: Do this the proper way, this is just a fix for now */
            cJSON_ArrayForEach(b_element, b)
            {
                a_element = get_object_item(a, b_element->string, case_sensitive);
                if (a_element == NULL)
                {
                    return false;
                }

                if (!cJSON_Compare(b_element, a_element, case_sensitive))
                {
                    return false;
                }
            }

            return true;
        }

        default:
            return false;
    }
}

CJSON_PUBLIC(void *) cJSON_malloc(size_t size)
{
    return global_hooks.allocate(size);
}

CJSON_PUBLIC(void) cJSON_free(void *object)
{
    global_hooks.deallocate(object);
}
/* AMALGAMATE c:expand_include cJSON.c [END] */

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


//////////////////////////////////////////////////////////////////////////
// 3rd: cjson.lua
//////////////////////////////////////////////////////////////////////////

/*
 * ADDON:   c:expand_include
 * PATH:    cjson.lua.h
 * SIZE:    720
 * SHA-256: 291b6bb0a4b558d23f313f6ebb69bcdb75e937b01630bebd6e6958a2539c6780
 */
/* AMALGAMATE c:expand_include cjson.lua.h [BEG] */
#line 1 "cjson.lua.h"
#ifndef __CJSON_LUA_H__
#define __CJSON_LUA_H__
#ifdef __cplusplus
extern "C" {
#endif

struct lua_State;

/**
 * @brief Load cJSON package.
 * @param[in] L     Lua Stack.
 * @return          Always 1.
 */
int luaopen_cjson(struct lua_State* L);

/**
 * @brief Convert Lua value into json string.
 * @param[in] L     Lua stack.
 * @param[in] idx   Value index.
 * @return          Always 1.
 */
int lua_cjson_serialize(struct lua_State* L, int idx);

/**
 * @brief Convert json into Lua value.
 * @param[in] L     Lua stack.
 * @param[in] idx   Value index.
 * @return          Always 1.
 */
int lua_cjson_deserialize(struct lua_State* L, int idx);

#ifdef __cplusplus
}
#endif
#endif
/* AMALGAMATE c:expand_include cjson.lua.h [END] */


/*
 * ADDON:   c:expand_include
 * PATH:    cjson.lua.c
 * SIZE:    11302
 * SHA-256: d4be402e1d32d8a2ffd51e81edfd0fa931fd401f4aa83bd655e63899098f9286
 */
/* AMALGAMATE c:expand_include cjson.lua.c [BEG] */
#line 1 "cjson.lua.c"
/* AMALGAMATE_DISPLACE_INCLUDE: cjson.lua.h */
/* AMALGAMATE_DISPLACE_INCLUDE: lua.h */
/* AMALGAMATE_DISPLACE_INCLUDE: lauxlib.h */
/* AMALGAMATE_DISPLACE_INCLUDE: lualib.h */
/* AMALGAMATE_DISPLACE_INCLUDE: cjson/cJSON.h */

static int _lua_cjson_serialize(lua_State* L, int idx, cJSON* obj, const char* k);
static int _lua_cjson_deserialize(lua_State* L, cJSON* v);
static int _cjson_from_json_array(lua_State* L, int idx, cJSON* obj);

typedef struct lua_cjson
{
    cJSON* obj;
} lua_cjson_t;

static int _cjson_gc(lua_State* L)
{
    lua_cjson_t* self = lua_touserdata(L, 1);

    if (self->obj != NULL)
    {
        cJSON_Delete(self->obj);
        self->obj = NULL;
    }

    return 0;
}

static lua_cjson_t* _cjson_make_json(lua_State* L)
{
    lua_cjson_t* obj = lua_newuserdata(L, sizeof(lua_cjson_t));
    obj->obj = NULL;

    static const luaL_Reg s_meta[] = {
        { "__gc",   _cjson_gc },
        { NULL,     NULL },
    };
    if (luaL_newmetatable(L, "__cjson") != 0)
    {
        luaL_setfuncs(L, s_meta, 0);
    }
    lua_setmetatable(L, -2);

    obj->obj = cJSON_CreateObject();

    return obj;
}

static int _cjson_serialize(lua_State* L)
{
    return lua_cjson_serialize(L, 1);
}

static int _cjson_deserialize(lua_State* L)
{
    return lua_cjson_deserialize(L, 1);
}

static int _cjson_tostring_table(lua_State* L, int idx, cJSON* obj, const char* k)
{
    int sp = lua_gettop(L);

    cJSON* arr = cJSON_CreateArray();
    cJSON_AddItemToObject(obj, k, arr);

    lua_pushnil(L); // sp + 1
    while (lua_next(L, idx) != 0)
    {// key at sp+1, value at sp+2
        cJSON* ele = cJSON_CreateObject();
        cJSON_AddItemToArray(arr, ele);

        _lua_cjson_serialize(L, sp + 1, ele, "k");
        _lua_cjson_serialize(L, sp + 2, ele, "v");

        lua_pop(L, 1);
    }

    return 0;
}

static int _cjson_tostring_native(lua_State* L, int idx, cJSON* obj, const char* k)
{
    int type;

    switch (type = lua_type(L, idx))
    {
    case LUA_TNIL:
        cJSON_AddNullToObject(obj, k);
        return 0;

    case LUA_TBOOLEAN:
        cJSON_AddBoolToObject(obj, k, lua_toboolean(L, idx));
        return 0;

    case LUA_TNUMBER:
        cJSON_AddNumberToObject(obj, k, lua_tonumber(L, idx));
        return 0;

    case LUA_TSTRING:
        cJSON_AddStringToObject(obj, k, lua_tostring(L, idx));
        return 0;

    case LUA_TTABLE:
        return _cjson_tostring_table(L, idx, obj, k);

    case LUA_TUSERDATA:
    case LUA_TLIGHTUSERDATA:
        if (lua_touserdata(L, idx) == NULL)
        {
            cJSON_AddNullToObject(obj, k);
            return 0;
        }
        lua_pushfstring(L, "userdata does not contains `__tostring` metamethod.");
        return -1;

    case LUA_TFUNCTION:
    case LUA_TTHREAD:
    default:
        lua_pushfstring(L, "type %s does not support serializable.", lua_typename(L, idx));
        return -1;
    }
}

static int _lua_cjson_serialize(lua_State* L, int idx, cJSON* obj, const char* k)
{
    int ret;
    int sp = lua_gettop(L);

    if ((ret = luaL_getmetafield(L, idx, "__name")) == LUA_TSTRING) // sp + 1
    {
        if ((ret = luaL_getmetafield(L, idx, "__tostring")) != LUA_TFUNCTION) // sp + 2
        {
            lua_pushfstring(L, "type `%s` does not have `__tostring` meta method.", lua_tostring(L, sp + 1));
            return -1;
        }

        lua_pushvalue(L, idx); // sp + 3
        lua_call(L, 1, 1); // sp + 2

        cJSON* v = cJSON_CreateObject();
        cJSON_AddStringToObject(v, "t", lua_tostring(L, sp + 1));
        cJSON_AddStringToObject(v, "p", lua_tostring(L, sp + 2));
        cJSON_AddItemToObject(obj, k, v);

        lua_settop(L, sp);
        return 0;
    }
    lua_settop(L, sp);

    return _cjson_tostring_native(L, idx, obj, k);
}

static int _lua_cjson_fromjson_table(lua_State* L, cJSON* obj)
{
    cJSON* ele;
    lua_newtable(L);

    cJSON_ArrayForEach(ele, obj)
    {
        cJSON* k = cJSON_GetObjectItem(ele, "k");
        if (_lua_cjson_deserialize(L, k) != 0)
        {
            return -1;
        }

        cJSON* v = cJSON_GetObjectItem(ele, "v");
        if (_lua_cjson_deserialize(L, v) != 0)
        {
            return -1;
        }

        lua_settable(L, -3);
    }

    return 0;
}

static int _lua_cjson_fromjson_userdata(lua_State* L, cJSON* obj)
{
    int sp = lua_gettop(L);
    cJSON* t = cJSON_GetObjectItem(obj, "t");
    cJSON* p = cJSON_GetObjectItem(obj, "p");

    if (luaL_getmetatable(L, cJSON_GetStringValue(t)) != LUA_TTABLE) // sp + 1
    {
        lua_pushfstring(L, "no metatable named `%s`", cJSON_GetStringValue(t));
        return -1;
    }
    if (lua_getfield(L, sp + 1, "__fromstring") != LUA_TFUNCTION) // sp + 2
    {
        lua_pushfstring(L, "no metamethod `__fromstring` in metatable `%s`", cJSON_GetStringValue(t));
        return -1;
    }

    lua_pushstring(L, cJSON_GetStringValue(p)); // sp + 3
    lua_call(L, 1, 1); // sp + 2

    lua_remove(L, sp + 1); // sp + 1
    return 0;
}

static int _lua_cjson_deserialize(lua_State* L, cJSON* v)
{
    switch (v->type)
    {
    case cJSON_False:
        lua_pushboolean(L, 0);
        break;

    case cJSON_True:
        lua_pushboolean(L, 1);
        break;

    case cJSON_NULL:
        lua_pushnil(L);
        break;

    case cJSON_Number:
        lua_pushnumber(L, cJSON_GetNumberValue(v));
        break;

    case cJSON_String:
        lua_pushstring(L, cJSON_GetStringValue(v));
        break;

    case cJSON_Array:
        return _lua_cjson_fromjson_table(L, v);

    case cJSON_Object:
        return _lua_cjson_fromjson_userdata(L, v);

    default:
        lua_pushfstring(L, "unknown JSON type %d", v->type);
        return -1;
    }

    return 0;
}

static int _cjson_compare(lua_State* L)
{
    cJSON* v1_json = NULL;
    cJSON* v2_json = NULL;
    const char* err_pos = NULL;

    size_t v1_sz = 0;
    const char* v1 = luaL_checklstring(L, 1, &v1_sz);

    size_t v2_sz = 0;
    const char* v2 = luaL_checklstring(L, 2, &v2_sz);

    if ((v1_json = cJSON_ParseWithLengthOpts(v1, v1_sz, &err_pos, 0)) == NULL)
    {
        lua_pushfstring(L, "parser argument #1 as json failed at `%s`", err_pos);
        goto handle_error;
    }

    if ((v2_json = cJSON_ParseWithLengthOpts(v2, v2_sz, &err_pos, 0)) == NULL)
    {
		lua_pushfstring(L, "parser argument #2 as json failed at `%s`", err_pos);
		goto handle_error;
    }

    int ret = cJSON_Compare(v1_json, v2_json, 1);
    cJSON_Delete(v1_json);
    cJSON_Delete(v2_json);

    lua_pushboolean(L, ret);
    return 1;

handle_error:
    if (v1_json != NULL)
    {
        cJSON_Delete(v1_json);
        v1_json = NULL;
    }
    if (v2_json != NULL)
    {
        cJSON_Delete(v2_json);
        v2_json = NULL;
    }
    return lua_error(L);
}

static int _cjson_from_json_object(lua_State* L, int idx, cJSON* obj)
{
    cJSON* ele;
    cJSON_ArrayForEach(ele, obj)
    {
        lua_pushstring(L, ele->string);

		if (cJSON_IsBool(ele))
		{
			lua_pushboolean(L, ele->valueint);
		}
		else if (cJSON_IsNull(ele))
		{
			lua_pushlightuserdata(L, NULL);
		}
		else if (cJSON_IsNumber(ele))
		{
			lua_pushnumber(L, ele->valuedouble);
		}
		else if (cJSON_IsString(ele))
		{
			lua_pushstring(L, ele->valuestring);
		}
		else if (cJSON_IsArray(ele))
		{
			int sp = lua_gettop(L);
			lua_newtable(L);
			_cjson_from_json_array(L, sp + 1, ele);
		}
		else if (cJSON_IsObject(ele) || cJSON_IsRaw(ele))
		{
			int sp = lua_gettop(L);
			lua_newtable(L);
			_cjson_from_json_object(L, sp + 1, ele);
		}
		else
		{
			return luaL_error(L, "invalid json object type %d.", ele->type);
		}

		lua_settable(L, idx);
    }

    return 0;
}

static int _cjson_from_json_array(lua_State* L, int idx, cJSON* obj)
{
	cJSON* ele;
    size_t pos = 1;
	cJSON_ArrayForEach(ele, obj)
	{
        lua_pushinteger(L, pos);

        if (cJSON_IsBool(ele))
        {
            lua_pushboolean(L, ele->valueint);
        }
        else if (cJSON_IsNull(ele))
        {
            lua_pushlightuserdata(L, NULL);
        }
        else if (cJSON_IsNumber(ele))
        {
            lua_pushnumber(L, ele->valuedouble);
        }
        else if (cJSON_IsString(ele))
        {
            lua_pushstring(L, ele->valuestring);
        }
        else if (cJSON_IsArray(ele))
        {
            int sp = lua_gettop(L);
            lua_newtable(L);
            _cjson_from_json_array(L, sp + 1, ele);
        }
        else if (cJSON_IsObject(ele) || cJSON_IsRaw(ele))
        {
			int sp = lua_gettop(L);
			lua_newtable(L);
            _cjson_from_json_object(L, sp + 1, ele);
        }
        else
        {
            return luaL_error(L, "invalid json object type %d.", ele->type);
        }

        lua_settable(L, idx);
        pos++;
	}

    return 0;
}

static int _cjson_from_json(lua_State* L)
{
    int sp = lua_gettop(L);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    cJSON* object = cJSON_ParseWithLength(data, data_sz);
    if (object == NULL)
    {
        return 0;
    }

    lua_newtable(L); //sp+1
    if (cJSON_IsObject(object))
    {
        _cjson_from_json_object(L, sp + 1, object);
    }
    else if (cJSON_IsArray(object))
    {
        _cjson_from_json_array(L, sp + 1, object);
    }
    else
    {
        return luaL_error(L, "invalid json object type %d.", object->type);
    }

    cJSON_Delete(object);

    return 1;
}

int luaopen_cjson(lua_State* L)
{
    static const luaL_Reg s_apis[] = {
        { "from_json",      _cjson_from_json },
        { "serialize",      _cjson_serialize },
        { "deserialize",    _cjson_deserialize },
        { "compare",        _cjson_compare },
        { NULL,             NULL },
    };
    luaL_newlib(L, s_apis);

    lua_pushlightuserdata(L, NULL);
    lua_setfield(L, -2, "NULL");

    return 1;
}

int lua_cjson_serialize(lua_State* L, int idx)
{
    lua_cjson_t* obj = _cjson_make_json(L); // sp + 1

    if (_lua_cjson_serialize(L, idx, obj->obj, "v") != 0)
    {
        return lua_error(L);
    }

    char* str = cJSON_PrintUnformatted(obj->obj);
    lua_pop(L, 1); // sp

    lua_pushstring(L, str);
    cJSON_free(str);

    return 1;
}

int lua_cjson_deserialize(lua_State* L, int idx)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, idx, &data_sz);

    int sp = lua_gettop(L);

    lua_cjson_t* obj = _cjson_make_json(L); // sp + 1
    cJSON_Delete(obj->obj); obj->obj = NULL;

    const char* return_parse_end = NULL;
    obj->obj = cJSON_ParseWithLengthOpts(data, data_sz, &return_parse_end, 0);

    if (obj->obj == NULL)
    {
        lua_pop(L, 1); // sp
        lua_pushfstring(L, "JSON parser failed at `%s`", return_parse_end); // sp + 1
        return lua_error(L);
    }

    cJSON* v = cJSON_GetObjectItem(obj->obj, "v");
    int ret = _lua_cjson_deserialize(L, v); // sp + 2
    lua_remove(L, sp + 1);

    if (ret != 0)
    {
        return lua_error(L);
    }

    return 1;
}
/* AMALGAMATE c:expand_include cjson.lua.c [END] */



//////////////////////////////////////////////////////////////////////////
// User header
//////////////////////////////////////////////////////////////////////////

/*
 * ADDON:   c:expand_include
 * PATH:    config.h
 * SIZE:    906
 * SHA-256: 97f90e5655423ca5dd814cb4ebdd36527bfb0d945ee813c2b9515add96f4ba74
 */
/* AMALGAMATE c:expand_include config.h [BEG] */
#line 1 "config.h"
#ifndef __AMALGAMATE_CONFIG_H__
#define __AMALGAMATE_CONFIG_H__

/**
 * @brief Global amalgamate namespace for Lua
 */
#ifndef AMALGAMATE_NAMESPACE
#define AMALGAMATE_NAMESPACE "am"
#endif

/**
 * @brief Pattern for searching specific code block.
 */
#ifndef AMALGAMATE_PARSER_PATTERN
#define AMALGAMATE_PARSER_PATTERN   \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:BEG\n"         \
    "```(%w+)\n"                    \
    "(.-)\n"                        \
    "```\n"                         \
    " %*/\n"                        \
    "(.-)"                          \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:END\n"         \
    " %*/\n"
#endif

#ifndef AMALGAMATE_DEFAULT_OUTPUT
#define AMALGAMATE_DEFAULT_OUTPUT   ":stdout"
#endif

#ifndef AMALGAMATE_DEFAULT_LOGFILE
#define AMALGAMATE_DEFAULT_LOGFILE  ":stderr"
#endif

#endif
/* AMALGAMATE c:expand_include config.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/__init__.h
 * SIZE:    2432
 * SHA-256: 4ecab206876636f7b8d33f89c8401e4cb2955a24f6997aa04d222a53c90f0fec
 */
/* AMALGAMATE c:expand_include function/__init__.h [BEG] */
#line 1 "function/__init__.h"
#ifndef __AMALGAMATE_FUNCTION_INIT_H__
#define __AMALGAMATE_FUNCTION_INIT_H__

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if defined(_MSC_VER)

#define strtok_r(str, delim, saveptr)   strtok_s(str, delim, saveptr)
#define strerror_r(errcode, buf, len)   strerror_s(buf,len, errcode)
#define strdup(s)                       _strdup(s)

#else

/**
 * @brief Opens a file.
 * @see fopen()
 * @param[out] pFile    A pointer to the file pointer that will receive the
 *   pointer to the opened file.
 * @param[in] filename  Filename.
 * @param[in] mode      Type of access permitted.
 * @return              Zero if successful; an error code on failure.
 */
int fopen_s(FILE** pFile, const char* filename, const char* mode);

#endif

typedef struct am_function
{
    const char*     name;
    lua_CFunction   addr;
    const char*     proto;
    const char*     brief;
    const char*     document;
} am_function_t;

/**
 * @brief Push a table on top of stack that contains all functions.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int luaopen_am(lua_State* L);

/**
 * @brief Push a string on top of stack that contains all function name and brief.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
int am_list_function(lua_State* L);

/**
 * @brief Search for function manual.
 * @param[in] L     Lua VM.
 * @return          1 if found, or 0 if not found.
 */
int am_function_manual(lua_State* L);

/**
 * @brief Registered builtin functions
 * @{
 */
extern am_function_t am_f_dirname;
extern am_function_t am_f_dump_hex;
extern am_function_t am_f_dump_obj;
extern am_function_t am_f_fmtpath;
extern am_function_t am_f_is_abspath;
extern am_function_t am_f_is_file_exist;
extern am_function_t am_f_load_file;
extern am_function_t am_f_load_txt_file;
extern am_function_t am_f_log_i;
extern am_function_t am_f_merge_line;
extern am_function_t am_f_msvc_suppress_warning;
extern am_function_t am_f_search_file;
extern am_function_t am_f_sha256;
extern am_function_t am_f_split_line;
extern am_function_t am_f_split_line_by_pattern;
extern am_function_t am_f_strcasecmp;
extern am_function_t am_f_table_is_array;
extern am_function_t am_f_write_file;
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
/* AMALGAMATE c:expand_include function/__init__.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/__init__.h
 * SIZE:    1103
 * SHA-256: e1aa73fcd13e955077ba7bffa54283a171b17c9b2719d4e430b9434384393a00
 */
/* AMALGAMATE c:expand_include addon/__init__.h [BEG] */
#line 1 "addon/__init__.h"
#ifndef __AMALGAMATE_ADDON_INIT_H__
#define __AMALGAMATE_ADDON_INIT_H__

/* AMALGAMATE_DISPLACE_INCLUDE: function/__init__.h */

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
/* AMALGAMATE c:expand_include addon/__init__.h [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    amalgamate.h
 * SIZE:    190
 * SHA-256: 935d75a5b2d077d8aadfe111c57bb49fc9ce08b5887ab5321658dc2cb073f6ea
 */
/* AMALGAMATE c:expand_include amalgamate.h [BEG] */
#line 1 "amalgamate.h"
#ifndef __AMALGAMATE_SCRIPT_H__
#define __AMALGAMATE_SCRIPT_H__
#ifdef __cplusplus
extern "C" {
#endif

extern const char* amalgamate_script;

#ifdef __cplusplus
}
#endif
#endif
/* AMALGAMATE c:expand_include amalgamate.h [END] */



//////////////////////////////////////////////////////////////////////////
// Embed source file
//////////////////////////////////////////////////////////////////////////

/*
 * ADDON:   c:expand_include
 * PATH:    function/__init__.c
 * SIZE:    2073
 * SHA-256: 9978775f247d967deb1ff6999e905d8e8217fda1a5770323e75edb1b593b71b5
 */
/* AMALGAMATE c:expand_include function/__init__.c [BEG] */
#line 1 "function/__init__.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>
#include <errno.h>

static am_function_t* am_apis[] = {
    &am_f_dirname,
    &am_f_dump_hex,
    &am_f_dump_obj,
    &am_f_fmtpath,
    &am_f_is_abspath,
    &am_f_is_file_exist,
    &am_f_load_file,
    &am_f_load_txt_file,
    &am_f_log_i,
    &am_f_merge_line,
    &am_f_msvc_suppress_warning,
    &am_f_search_file,
    &am_f_sha256,
    &am_f_split_line,
    &am_f_split_line_by_pattern,
    &am_f_strcasecmp,
    &am_f_table_is_array,
    &am_f_write_file,
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
        lua_pushcfunction(L, am_apis[i]->addr);
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
/* AMALGAMATE c:expand_include function/__init__.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dirname.c
 * SIZE:    864
 * SHA-256: 949469fead3b2455531177f93e7e5bc2f6501fb5979018ec05e33928c68eca04
 */
/* AMALGAMATE c:expand_include function/lua_dirname.c [BEG] */
#line 1 "function/lua_dirname.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static char* _am_dirname(char* s)
{
    size_t i;
    if (!s || !*s) return ".";
    i = strlen(s) - 1;
    for (; s[i] == '/'; i--) if (!i) return "/";
    for (; s[i] != '/'; i--) if (!i) return ".";
    for (; s[i] == '/'; i--) if (!i) return "/";
    s[i + 1] = 0;
    return s;
}

static int _lua_dirname(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    char* cpy_path = strdup(path);

    char* name = _am_dirname(cpy_path);
    lua_pushstring(L, name);
    free(cpy_path);

    return 1;
}

am_function_t am_f_dirname = {
"dirname", _lua_dirname, "string dirname(string s)",
"Break string `s` into directory component and return it.",
"dirname() returns the string up to, but not including, the final '/'. If path\n"
"does not contain a slash, dirname() returns the string \".\"."
};
/* AMALGAMATE c:expand_include function/lua_dirname.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dump_hex.c
 * SIZE:    1831
 * SHA-256: 7c93a08b450368a5b333d6151615de09991084bbc95b38b469cd977824bc79ad
 */
/* AMALGAMATE c:expand_include function/lua_dump_hex.c [BEG] */
#line 1 "function/lua_dump_hex.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static char _mmc_ascii_to_char(unsigned char c)
{
    if (c >= 32 && c <= 126)
    {
        return c;
    }
    return '.';
}

static void mmc_dump_hex(luaL_Buffer* buf, const void* data, size_t size, size_t width)
{
    char tmp[64];
    const unsigned char* pdat = (unsigned char*)data;

    size_t idx_line;
    for (idx_line = 0; idx_line < size; idx_line += width)
    {
        snprintf(tmp, sizeof(tmp), "%p: ", (void*)(uintptr_t)idx_line);
        luaL_addstring(buf, tmp);

        /* printf hex */
        size_t idx_colume;
        for (idx_colume = 0; idx_colume < width; idx_colume++)
        {
            const char* postfix = (idx_colume < width - 1) ? "" : "|";

            if (idx_colume + idx_line < size)
            {
                snprintf(tmp, sizeof(tmp), "%02x %s", pdat[idx_colume + idx_line], postfix);
            }
            else
            {
                snprintf(tmp, sizeof(tmp), "   %s", postfix);
            }
            luaL_addstring(buf, tmp);
        }
        luaL_addchar(buf, ' ');
        /* printf char */
        for (idx_colume = 0; (idx_colume < width) && (idx_colume + idx_line < size); idx_colume++)
        {
            luaL_addchar(buf, _mmc_ascii_to_char(pdat[idx_colume + idx_line]));
        }
        luaL_addchar(buf, '\n');
    }
}

static int _am_dump_hex(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    luaL_Buffer buf;
    luaL_buffinit(L, &buf);
    mmc_dump_hex(&buf, data, data_sz, 16);
    luaL_pushresult(&buf);

    return 1;
}

am_function_t am_f_dump_hex = {
"dump_hex", _am_dump_hex, "string dump_hex(string s)",
"Dump string as hex string.",

"Dump string as hex string with ASCII character shown.\n"
};
/* AMALGAMATE c:expand_include function/lua_dump_hex.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_dump_obj.c
 * SIZE:    1258
 * SHA-256: 65315e330bf767f1763c48cb89ab23379655227b4d9655634ecd6d0ccad92511
 */
/* AMALGAMATE c:expand_include function/lua_dump_obj.c [BEG] */
#line 1 "function/lua_dump_obj.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_dump_obj(lua_State* L)
{
    if (lua_type(L, 1) != LUA_TTABLE)
    {
        lua_getglobal(L, "tostring");
        lua_pushvalue(L, 1);
        lua_call(L, 1, 1);
        return 1;
    }

    int sp = lua_gettop(L);
    lua_pushstring(L, "{ "); // sp+1: return value

    lua_pushnil(L); // sp+2
    while (lua_next(L, 1) != 0) // sp+3
    {
        lua_pushvalue(L, sp + 1);
        lua_pushstring(L, "[");

        if (lua_type(L, sp + 2) != LUA_TNUMBER)
        {
            lua_pushstring(L, "\"");
            lua_pushvalue(L, sp + 2);
            lua_pushstring(L, "\"");
            lua_concat(L, 3);
        }
        else
        {
            lua_pushvalue(L, sp + 2);
        }
        lua_pushstring(L, "] = ");

        lua_pushcfunction(L, _am_dump_obj);
        lua_pushvalue(L, sp + 3);
        lua_call(L, 1, 1);

        lua_pushstring(L, ",");

        lua_concat(L, 6);
        lua_replace(L, sp + 1);

        lua_pop(L, 1);
    }

    lua_pushstring(L, "} ");
    lua_concat(L, 2);

    return 1;
}

am_function_t am_f_dump_obj = {
"dump_obj",_am_dump_obj, "string dump_obj(object o)",
"Dump object as string.",
"Dump object as string."
};
/* AMALGAMATE c:expand_include function/lua_dump_obj.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_fmtpath.c
 * SIZE:    1478
 * SHA-256: 0b0026a1e86e667e0f3d0cb131d74ae80d67b4b28687f63833ba66843998b1f8
 */
/* AMALGAMATE c:expand_include function/lua_fmtpath.c [BEG] */
#line 1 "function/lua_fmtpath.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_fmtpath(lua_State* L)
{
    int sp = lua_gettop(L);
    luaL_checktype(L, 1, LUA_TSTRING);

    const char* delim = "/";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        delim = lua_tostring(L, 2);
    }

    /*
     * ```lua
     * param_1 = string.gsub(param_1, "\\\\", "/")
     * ```
     */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, sp + 1, "gsub"); // sp+2
    lua_pushvalue(L, 1); // sp+3
    lua_pushstring(L, "\\\\"); // sp+4
    lua_pushstring(L, "/"); // sp+5
    lua_call(L, 3, 1); // sp+2
    lua_replace(L, 1); // sp+1

    /*
     * ```lua
     * param_1 = string.gsub(param_1, "/", param_2)
     * ```
     */
    lua_getfield(L, sp + 1, "gsub"); // sp+2
    lua_pushvalue(L, 1); // sp+3
    lua_pushstring(L, "/"); // sp+4
    lua_pushstring(L, delim); // sp+5
    lua_call(L, 3, 1); // sp+2
    lua_replace(L, 1); // sp+1

    lua_pop(L, 1);
    lua_pushvalue(L, 1);

    return 1;
}

am_function_t am_f_fmtpath = {
"fmtpath", _am_fmtpath, "string fmtpath(string path[, string delim])",
"Format path into unified path string.",
"The first parameter is a string contains the path to format. The second optional\n"
"parameter is a string decide what the delimiter is, which by default is \"\\n\".\n"
"\n"
"EXAMPLE\n"
"If we have path string \"path/to\\\\foo\\\\bar\", the result of call\n"
"`fmtpath(path, \"/\")` is:\n"
"\"path/to/foo/bar\"."
};
/* AMALGAMATE c:expand_include function/lua_fmtpath.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_is_abspath.c
 * SIZE:    713
 * SHA-256: 21d337477d687c9586a968fe778ef49c73190379cb46f3158a15cb9925b970e2
 */
/* AMALGAMATE c:expand_include function/lua_is_abspath.c [BEG] */
#line 1 "function/lua_is_abspath.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

#define IS_LETTER(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

static int _am_is_abspath(lua_State* L)
{
    int ret = 0;
    const char* path = luaL_checkstring(L, 1);

    if (path[0] == '/')
    {
        ret = 1;
        goto finish;
    }
    if (IS_LETTER(path[0]) && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
        ret = 1;
        goto finish;
    }

finish:
    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_is_abspath = {
"is_abspath", _am_is_abspath, "boolean is_abspath(string path)",
"Check if parameter is absolute path.",
"Check if parameter is absolute path without actually access it."
};
/* AMALGAMATE c:expand_include function/lua_is_abspath.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_is_file_exist.c
 * SIZE:    714
 * SHA-256: b5e027d35098115d29b4941dd71d730b4ef2291186e07079022ab8037db40fc9
 */
/* AMALGAMATE c:expand_include function/lua_is_file_exist.c [BEG] */
#line 1 "function/lua_is_file_exist.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

static int _am_is_file_exist(lua_State* L)
{
    FILE* file = NULL;
    const char* path = luaL_checkstring(L, 1);

    int ret = 1;
#if defined(_WIN32)
    if (fopen_s(&file, path, "rb") != 0)
#else
    if ((file = fopen(path, "rb")) == NULL)
#endif
    {
        ret = 0;
    }

    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }

    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_is_file_exist = {
"is_file_exist", _am_is_file_exist, "boolean is_file_exist(string path)",
"Check if file is exist.",
"Check if file is exist, return true if it is, false if not exist or cannot\n"
"access it."
};
/* AMALGAMATE c:expand_include function/lua_is_file_exist.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_load_file.c
 * SIZE:    2351
 * SHA-256: cc1044e3623d627678358e9b022e341a239ff71952e56d64d53c7b21f16a52a0
 */
/* AMALGAMATE c:expand_include function/lua_load_file.c [BEG] */
#line 1 "function/lua_load_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

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

static int _lua_file_load(lua_State* L, const char* path)
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
            goto err;
        }

        size_t nread = fread(addr, 1, bufsz, pfile);
        luaL_addlstring(&buf, addr, nread);
    }

    luaL_pushresult(&buf); /* SP + 3 */

    /* Cleanup. */
    lua_remove(L, sp + 2); /* SP + 2 */
    lua_remove(L, sp + 1); /* SP + 1 */

    return 1;

err:
    strerror_r(errcode, errbuf, sizeof(errbuf));
    return luaL_error(L, "Cannot read file `%s': %s(%d).",
        path, errbuf, errcode);
}

static int _am_load_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    return _lua_file_load(L, path);
}

am_function_t am_f_load_file = {
"load_file", _am_load_file, "string load_file(string path)",
"Load whole file as binary mode and return it.",
"Load whole file as binary mode and return it."
};
/* AMALGAMATE c:expand_include function/lua_load_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_load_txt_file.c
 * SIZE:    913
 * SHA-256: abc28513bbd0ddbada84dd4104644d82a9c19f5d0c04b7c3e06686f0834e3021
 */
/* AMALGAMATE c:expand_include function/lua_load_txt_file.c [BEG] */
#line 1 "function/lua_load_txt_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_load_txt_file(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* file_type = "\n";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        file_type = lua_tostring(L, 2);
    }

    /* Load file */
    lua_pushcfunction(L, am_f_load_file.addr);
    lua_pushvalue(L, 1);
    lua_call(L, 1, 1); // sp+1

    /* Split line */
    lua_pushcfunction(L, am_f_split_line.addr);
    lua_insert(L, sp + 1);
    lua_call(L, 1, 1); // sp+1

    lua_pushcfunction(L, am_f_merge_line.addr);
    lua_insert(L, sp + 1);
    lua_pushstring(L, file_type);
    lua_call(L, 2, 1); // sp+1

    return 1;
}

am_function_t am_f_load_txt_file = {
"load_txt_file", _am_load_txt_file, "string load_txt_file(string path)",
"Load while file as txt mode and return it.",
"Load while file as txt mode and return it. Line endings is always convert to \"\\n\"."
};
/* AMALGAMATE c:expand_include function/lua_load_txt_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_log_i.c
 * SIZE:    1112
 * SHA-256: 0037ccacefa18bd952b44e52f411abc566a8941764338db439250977a760b7aa
 */
/* AMALGAMATE c:expand_include function/lua_log_i.c [BEG] */
#line 1 "function/lua_log_i.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

static int _log_i(lua_State* L)
{
    int sp = lua_gettop(L);
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Format string */
    lua_getglobal(L, "string"); //sp+1
    lua_getfield(L, -1, "format"); //sp+2
    lua_remove(L, sp + 1);
    lua_insert(L, 1);
    lua_call(L, sp, 1); // sp=1
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Write to logfile */
    lua_Debug ar; memset(&ar, 0, sizeof(ar));
    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "nSl", &ar);

    lua_pushcfunction(L, am_f_write_file.addr); // sp=2

    lua_getglobal(L, "arg"); // sp=3
    lua_getfield(L, -1, "logfile"); //sp=4
    lua_remove(L, 3); // sp=3

    lua_pushfstring(L, "[%s:%d] ", ar.source, ar.currentline); // sp=4
    lua_pushvalue(L, 1); // sp=5
    lua_pushstring(L, "\n"); // sp=6
    lua_concat(L, 3); // sp=4

    lua_pushstring(L, "a+b"); // sp+5

    lua_call(L, 3, 0); // sp=1

    return 0;
}

am_function_t am_f_log_i = {
"log_i", _log_i, "nil log_i(string data)",
"Append data into log file.",
"Append data into log file."
};
/* AMALGAMATE c:expand_include function/lua_log_i.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_merge_line.c
 * SIZE:    1121
 * SHA-256: 6e52e32ccb5952d4f6d84d577bbd0c6b7a61aaca0c8f2a90d103240d3f8f9c45
 */
/* AMALGAMATE c:expand_include function/lua_merge_line.c [BEG] */
#line 1 "function/lua_merge_line.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_merge_line(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TSTRING);
    lua_settop(L, 2);

    lua_pushstring(L, ""); // sp:3

    lua_pushnil(L); // key:4

    size_t cnt;
    for (cnt = 0; lua_next(L, 1) != 0; cnt++) // value:5
    {
        lua_pushvalue(L, 3); //sp:6

        if (cnt != 0)
        {
            lua_pushvalue(L, 2); //sp:7
        }

        lua_pushvalue(L, 5); //sp:8
        lua_concat(L, cnt != 0 ? 3 : 2); // sp:6
        lua_replace(L, 3); // sp:5

        lua_pop(L, 1);
    }

    return 1;
}

am_function_t am_f_merge_line = {
"merge_line", _am_merge_line, "string merge_line(table t[, string token])",
"Merge array of strings into a large string.",

"Merge array of strings into a large string, with `token` specific combinator.\n"
"If `token` is not assign, it is treat as `\\n`.\n"
"\n"
"EXAMPLE\n"
"If we have following table:\n"
"```lua\n"
"{ [1]=\"hello\", [2]=\" \", [3]=\"world\" }\n"
"```\n"
"The result of merge_line() will be:\n"
"\"hello\\n \\nworld\"."
};
/* AMALGAMATE c:expand_include function/lua_merge_line.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_msvc_suppress_warning.c
 * SIZE:    976
 * SHA-256: ee13ba8bdb4bbe6b1fe6018e8559e009b7f12eed3eb4b97e1ffeeceb5646b892
 */
/* AMALGAMATE c:expand_include function/lua_msvc_suppress_warning.c [BEG] */
#line 1 "function/lua_msvc_suppress_warning.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _msvc_suppress_warning(lua_State* L)
{
    int i;
    int sp = lua_gettop(L);

    if (sp <= 1)
    {
        return sp;
    }
    luaL_checktype(L, 1, LUA_TSTRING);

    lua_pushstring(L, "#if defined(_MSC_VER)\n#pragma warning(push)\n");

    for (i = 2; i <= sp; i++)
    {
        lua_pushstring(L, "#pragma warning(disable : ");
        lua_pushvalue(L, sp);
        lua_pushstring(L, ")\n");
        lua_concat(L, 4);
    }

    lua_pushstring(L, "#endif\n");
    lua_concat(L, 2);

    lua_pushvalue(L, 1);
    lua_concat(L, 2);

    lua_pushstring(L, "#if defined(_MSC_VER)\n#pragma warning(pop)\n#endif\n");
    lua_concat(L, 2);

    return 1;
}

am_function_t am_f_msvc_suppress_warning = {
"msvc_suppress_warning", _msvc_suppress_warning, "string msvc_suppress_warning(string source[, int code1, ...])",
"Suppress warning for MSVC cl compiler.",
"Suppress warning for MSVC cl compiler."
};
/* AMALGAMATE c:expand_include function/lua_msvc_suppress_warning.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_search_file.c
 * SIZE:    4931
 * SHA-256: c1a3f3410896786c9eb5d7659a6cda1a66ce283cfe8e45d168bf723a5f601738
 */
/* AMALGAMATE c:expand_include function/lua_search_file.c [BEG] */
#line 1 "function/lua_search_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

/**
 * @brief Check if path at \p idx is abspath.
 *
 * The stack is always unchanged.
 *
 * @return  boolean
 */
static int _am_search_file_is_abspath(lua_State* L, const char* file)
{
    lua_pushcfunction(L, am_f_is_abspath.addr);
    lua_pushstring(L, file);
    lua_call(L, 1, 1);

    int ret = lua_toboolean(L, -1);
    lua_pop(L, 1);

    return ret;
}

/**
 * @brief Check if file at \p idx is exist.
 *
 * The stack is always unchanged.
 *
 * @return  boolean
 */
static int _am_search_file_is_exist(lua_State* L, const char* file)
{
    lua_pushcfunction(L, am_f_is_file_exist.addr);
    lua_pushstring(L, file);
    lua_call(L, 1, 1);

    int ret = lua_toboolean(L, -1);
    lua_pop(L, 1);

    return ret;
}

/**
 * @brief Search file at \p idx_path in directory at \p idx_dirname
 * 
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 * 
 * @return 1 if found, 0 if not.
 */
static int _am_search_file_in_directory(lua_State* L, const char* dir, const char* file)
{
    int sp = lua_gettop(L);

    lua_pushstring(L, dir);
    lua_pushstring(L, "/");
    lua_pushstring(L, file);
    lua_concat(L, 3); // sp+1

    if (_am_search_file_is_exist(L, lua_tostring(L, sp + 1)))
    {
        return 1;
    }

    lua_pop(L, 1);
    return 0;
}

/**
 * @brief Search file at \p idx from current directory.
 *
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 *
 * @return 1 if found, 0 if not.
 */
static int _am_serach_file_from_current_directory(lua_State* L, const char* file)
{
    int sp = lua_gettop(L);

    /* Get dirname from input */
    lua_pushcfunction(L, am_f_dirname.addr); // sp+1
    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+2
    lua_getfield(L, -1, "config"); // sp+3
    lua_getfield(L, -1, "input"); // sp+4
    lua_remove(L, sp + 3); // sp+3
    lua_remove(L, sp + 2); // sp+2
    lua_call(L, 1, 1); // sp+1

    const char* dir = lua_tostring(L, sp + 1);
    int ret = _am_search_file_in_directory(L, dir, file);
    lua_remove(L, sp + 1);

    return ret;
}

static int _am_search_file_in_quote(lua_State* L, int quote_idx, const char* group, const char* file)
{
    int i;
    int sp = lua_gettop(L);

    if (lua_getfield(L, quote_idx, group) != LUA_TTABLE) // sp+1
    {
        lua_pop(L, 1);
        return 0;
    }

    for (i = 1;; i++)
    {
        if (lua_geti(L, -1, i) != LUA_TSTRING) // sp+2: directory
        {
            lua_pop(L, 1);
            break;
        }

        const char* dir = lua_tostring(L, sp + 2);
        if (_am_search_file_in_directory(L, dir, file))
        {
            lua_remove(L, sp + 1);
            return 1;
        }
        lua_pop(L, 1);
    }

    return 0;
}

/**
 * @brief Search file at \p idx from iquote table.
 *
 * If found, the top of stack contains the actual file path. If not found, the
 * stack is remain untouched.
 *
 * @return 1 if found, 0 if not.
 */
static int _am_search_file_from_quote(lua_State* L, const char* group, const char* path)
{
    int ret = 0;
    int sp = lua_gettop(L);

    /* Get iquote table at sp+1 */
    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+1
    lua_getfield(L, -1, "config"); // sp+2
    lua_getfield(L, -1, "iquote"); // sp+3
    lua_remove(L, sp + 2); // sp+2
    lua_remove(L, sp + 1); // sp+1

    if ((ret = _am_search_file_in_quote(L, sp + 1, group, path)) != 0)
    {
        goto finish;
    }

    if ((ret = _am_search_file_in_quote(L, sp + 1, "", path)) != 0)
    {
        goto finish;
    }

finish:
    lua_remove(L, sp + 1);
    return ret;
}

static int _am_search_file_from_current_and_quote(lua_State* L,
    const char* group, const char* file)
{
    if (_am_serach_file_from_current_directory(L, file))
    {
        return 1;
    }

    return _am_search_file_from_quote(L, group, file);
}

static int _am_search_file(lua_State* L)
{
    const char* file = luaL_checkstring(L, 1);
    const char* group = luaL_optstring(L, 2, "");

    /* Check for abspath */
    if (_am_search_file_is_abspath(L, file) == 0)
    {
        return _am_search_file_from_current_and_quote(L, group, file);
    }

    return !!_am_search_file_is_exist(L, file);
}

am_function_t am_f_search_file = {
"search_file", _am_search_file, "string search_file(string path[, string group])",
"Search file in current directory and quote directory.",

"Search file in current directory and quote directory. Return the real path that\n"
"can be opened or nil if failed.\n"
"\n"
"The search policy is:\n"
"1) Search in current directory where input file is.\n"
"2) Search in quote group if `group` option exists.\n"
"3) Search in default quote group \"\".\n"
};
/* AMALGAMATE c:expand_include function/lua_search_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_sha256.c
 * SIZE:    7762
 * SHA-256: 1b9ffed3e8024a3d6a5346f5d39d5cda87eba33d88611893743b3421b95ae577
 */
/* AMALGAMATE c:expand_include function/lua_sha256.c [BEG] */
#line 1 "function/lua_sha256.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/



/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/

typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
static void sha256_init(SHA256_CTX* ctx);
static void sha256_update(SHA256_CTX* ctx, const uint8_t data[], size_t len);
static void sha256_final(SHA256_CTX* ctx, uint8_t hash[]);


/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA-256 hashing algorithm.
              SHA-256 is one of the three algorithms in the SHA2
              specification. The others, SHA-384 and SHA-512, are not
              offered in this implementation.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/

/*************************** HEADER FILES ***************************/


/****************************** MACROS ******************************/
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

/**************************** VARIABLES *****************************/
static const uint32_t k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

/*********************** FUNCTION DEFINITIONS ***********************/
static void sha256_transform(SHA256_CTX* ctx, const uint8_t data[])
{
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

static void sha256_init(SHA256_CTX* ctx)
{
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

static void sha256_update(SHA256_CTX* ctx, const uint8_t data[], size_t len)
{
    uint32_t i;

    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha256_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

static void sha256_final(SHA256_CTX* ctx, uint8_t hash[])
{
    uint32_t i;

    i = ctx->datalen;

    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56)
            ctx->data[i++] = 0x00;
    }
    else {
        ctx->data[i++] = 0x80;
        while (i < 64)
            ctx->data[i++] = 0x00;
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56);
    }

    // Append to the padding the total message's length in bits and transform.
    ctx->bitlen += (uint64_t)(ctx->datalen * 8);
    ctx->data[63] = (uint8_t)ctx->bitlen;
    ctx->data[62] = (uint8_t)(ctx->bitlen >> 8);
    ctx->data[61] = (uint8_t)(ctx->bitlen >> 16);
    ctx->data[60] = (uint8_t)(ctx->bitlen >> 24);
    ctx->data[59] = (uint8_t)(ctx->bitlen >> 32);
    ctx->data[58] = (uint8_t)(ctx->bitlen >> 40);
    ctx->data[57] = (uint8_t)(ctx->bitlen >> 48);
    ctx->data[56] = (uint8_t)(ctx->bitlen >> 56);
    sha256_transform(ctx, ctx->data);

    // Since this implementation uses little endian byte ordering and SHA uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

static int _am_sha256(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (uint8_t*)data, data_sz);

    uint8_t ret[SHA256_BLOCK_SIZE];
    sha256_final(&ctx, ret);

    char buf[65]; size_t i;
    for (i = 0; i < sizeof(ret); i++)
    {
        snprintf(buf + 2 * i, sizeof(buf) - 2 * i, "%02x", ret[i]);
    }

    lua_pushstring(L, buf);
    return 1;
}

am_function_t am_f_sha256 = {
"sha256", _am_sha256, "string sha256(string s)",
"Calcualte SHA-256.",

"Calcualte SHA256 of `s` and return it's string value."
};
/* AMALGAMATE c:expand_include function/lua_sha256.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_split_line.c
 * SIZE:    1783
 * SHA-256: a28d60008fc3a823a748a38c308c8e331afd96a5ea09872264a62eb896ad7660
 */
/* AMALGAMATE c:expand_include function/lua_split_line.c [BEG] */
#line 1 "function/lua_split_line.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_split_line(lua_State* L)
{
    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 1, &data_sz);

    // This will be the return value.
    lua_newtable(L);

    size_t pos;
    const char* start = data;

    for (pos = 0; pos < data_sz; pos++)
    {
        /*
         * There are 3 EOLs:
         * \r\n: CRLF (Windows)
         * \r: CR (Macintosh)
         * \n: LF (Unix)
         * Here we allow mixed line endings, just to parse aggressively.
         */
        if (data[pos] == '\r')
        {
            size_t len = &data[pos] - start;
            lua_pushlstring(L, start, len);
            lua_seti(L, -2, luaL_len(L, -2) + 1);

            if (pos < data_sz - 1 && data[pos + 1] == '\n')
            {
                start = &data[pos + 2];
                pos++;
            }
            else
            {
                start = &data[pos + 1];
            }
            continue;
        }
        else if (data[pos] == '\n')
        {
            size_t len = &data[pos] - start;
            lua_pushlstring(L, start, len);
            lua_seti(L, -2, luaL_len(L, -2) + 1);

            start = &data[pos + 1];
            continue;
        }
    }

    if (start < data + pos)
    {
        size_t len = data + data_sz - start;
        lua_pushlstring(L, start, len);
        lua_seti(L, -2, luaL_len(L, -2) + 1);
    }

    return 1;
}

am_function_t am_f_split_line = {
"split_line", _am_split_line, "table split_line(string s)",
"Split string into array.",

"Split string into array, with line wrap as token. This function automatically\n"
"take care of different endings like `\\r`, `\\n` or `\\r\\n`. Empty line is not\n"
"ignored."
};
/* AMALGAMATE c:expand_include function/lua_split_line.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_split_line_by_pattern.c
 * SIZE:    5230
 * SHA-256: abe2d7d9ac398c0b400b06a3faaee381c3418ecc58aba37bb91fca58631b8ea5
 */
/* AMALGAMATE c:expand_include function/lua_split_line_by_pattern.c [BEG] */
#line 1 "function/lua_split_line_by_pattern.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

/**
 * @see string.find
 */
static int _split_line_by_pattern_wrap_string_find(lua_State* L, int idx_s, int idx_p)
{
    int sp = lua_gettop(L);

    /* Prepare function */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, -1, "find"); // sp+2
    lua_remove(L, sp + 1); // sp+1

    /* Prepare arguments */
    lua_pushvalue(L, idx_s); // sp+2
    lua_pushvalue(L, idx_p); // sp+3

    /* Do function call */
    lua_call(L, 2, LUA_MULTRET);

    /* Check result */
    if (lua_type(L, sp + 1) == LUA_TNIL)
    {
        lua_settop(L, sp);
        return 0;
    }

    /* Return the number of values */
    int now_sp = lua_gettop(L);
    return now_sp - sp;
}

static int _split_line_by_pattern_wrap_string_sub(lua_State* L, int idx, size_t offset, size_t len)
{
    int cnt_arg = 2;
    int sp = lua_gettop(L);

    /* Prepare function */
    lua_getglobal(L, "string"); // sp+1
    lua_getfield(L, -1, "sub"); // sp+2
    lua_remove(L, sp + 1); // sp+1

    /* Prepare arguments */
    lua_pushvalue(L, idx);
    lua_pushinteger(L, offset + 1);
    if (len != (size_t)-1)
    {
        lua_pushinteger(L, offset + 1 + len - 1);
        cnt_arg = 3;
    }

    /* Do function call */
    lua_call(L, cnt_arg, 1);

    return 1;
}

static void _split_line_by_pattern_check_args(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TSTRING);
    luaL_checktype(L, 2, LUA_TSTRING);
    lua_settop(L, 2);
}

static size_t _split_line_by_pattern_count_line(lua_State* L, int idx)
{
    size_t cnt = 0;

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, idx, &data_sz);

    size_t i;
    for (i = 0; i < data_sz; i++)
    {
        if (data[i] == '\n')
        {
            cnt++;
        }
    }

    return cnt;
}

/**
 * @brief Push data on sp 1 into result at \p sp+2
 */
static size_t _split_line_by_pattern_push_left_on_stack(lua_State* L, int idx, size_t lineno)
{
    idx = lua_absindex(L, idx);

    lua_newtable(L);

    lua_pushvalue(L, idx);
    lua_setfield(L, -2, "data");

    lua_pushinteger(L, lineno);
    lua_setfield(L, -2, "line_beg");

    size_t cnt_line = _split_line_by_pattern_count_line(L, idx);
    lua_pushinteger(L, lineno + cnt_line);
    lua_setfield(L, -2, "line_end");

    return cnt_line;
}

static int _split_line_by_pattern(lua_State* L)
{
    _split_line_by_pattern_check_args(L);

    int sp = lua_gettop(L);
    size_t lineno = 1;

    lua_newtable(L); // sp+1: this will be the return value.

    while (1)
    {
        if (_split_line_by_pattern_wrap_string_find(L, 1, 2) == 0)
        {/* Not found */
            lineno += _split_line_by_pattern_push_left_on_stack(L, 1, lineno);
            lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);
            break;
        }
        int now_sp = lua_gettop(L); // now_sp-sp: the number of return value.

        /* Get offset */
        size_t off_beg = (size_t)lua_tonumber(L, sp + 3);
        size_t off_end = (size_t)lua_tonumber(L, sp + 4);

        if (off_beg > 1)
        {
            _split_line_by_pattern_wrap_string_sub(L, 1, off_beg - 1,
                off_end - off_beg + 1);

            lineno += _split_line_by_pattern_push_left_on_stack(L, -1, lineno);
            lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);

            lua_pop(L, 1);
        }

        lua_newtable(L);
        {
            int i;
            lua_newtable(L);
            for (i = sp + 2; i <= now_sp; i++)
            {
                lua_pushvalue(L, i);
                lua_seti(L, -2, luaL_len(L, -2) + 1);
            }
            lua_setfield(L, -2, "group");

            lua_pushinteger(L, lineno);
            lua_setfield(L, -2, "line_beg");

            _split_line_by_pattern_wrap_string_sub(L, 1, off_beg - 1, off_end - off_beg + 1);
            size_t line_cnt = _split_line_by_pattern_count_line(L, -1);
            lua_pop(L, 1);
            lua_pushinteger(L, lineno + line_cnt);
            lua_setfield(L, -2, "line_end");
        }
        lua_seti(L, sp + 1, luaL_len(L, sp + 1) + 1);

        _split_line_by_pattern_wrap_string_sub(L, 1, off_end, (size_t)-1);
        lua_replace(L, 1);

        lua_settop(L, sp + 1);
    }

    return 1;
}

am_function_t am_f_split_line_by_pattern = {
"split_line_by_pattern", _split_line_by_pattern,
"table, split_line_by_pattern(string data, string pattern)",
"Split line by pattern and return the split result.",

"The result is a list contains following fields:\n"
"+ \"data\": The actual string data.\n"
"+ \"line_beg\": The start line number of the data.\n"
"+ \"line_end\": The end line number of the data.\n"
"+ \"group\": Array of captured groups if exists.\n"
"\n"
"E.g.\n"
"[\n"
"    {\n"
"        \"data\": \"The actual string data.\",\n"
"        \"line_beg\": \"The start line number of the data.\",\n"
"        \"line_end\": \"The end line number of the data.\",\n"
"        \"group\": [\n"
"            [1]= \"The first group\","
"            [2]= \"The second group\","
"            ...\n"
"        ]\n"
"    }\n,"
"    ...\n"
"]"
};
/* AMALGAMATE c:expand_include function/lua_split_line_by_pattern.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_strcasecmp.c
 * SIZE:    814
 * SHA-256: eda786d14f01a79d3cb8c1af61fc2a14b230da7d1388b61be9aa5461f817fc2d
 */
/* AMALGAMATE c:expand_include function/lua_strcasecmp.c [BEG] */
#line 1 "function/lua_strcasecmp.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

#if defined(_WIN32)
#   define strcasecmp(s1, s2) _stricmp(s1, s2)
#endif

static int _am_strcasecmp(lua_State* L)
{
    const char* s1 = luaL_checkstring(L, 1);
    const char* s2 = luaL_checkstring(L, 2);

    int ret = strcasecmp(s1, s2);
    lua_pushnumber(L, ret);

    return 1;
}

am_function_t am_f_strcasecmp = {
"strcasecmp", _am_strcasecmp, "number strcasecmp(string s1, string s2)",
"Compare string ignoring the case of the characters.",

"The strcasecmp() function performs a byte-by-byte comparison of the strings `s1`\n"
"and `s2`, ignoring the case of the characters. It returns an integer less than,\n"
"equal to, or greater than zero if `s1` is found, respectively, to be less than,\n"
"to match, or be greater than `s2`."
};
/* AMALGAMATE c:expand_include function/lua_strcasecmp.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_table_is_array.c
 * SIZE:    467
 * SHA-256: 3cc019095e3cf941e406a22c318cd5e3426a17092a197042daa512d9f4c3f587
 */
/* AMALGAMATE c:expand_include function/lua_table_is_array.c [BEG] */
#line 1 "function/lua_table_is_array.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int am_table_is_array(lua_State* L)
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

am_function_t am_f_table_is_array = {
"table_is_array", am_table_is_array, "boolean table_is_array(table t)",
"Check if a Lua table is array.",

"Check if parameter `t` is an array."
};
/* AMALGAMATE c:expand_include function/lua_table_is_array.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    function/lua_write_file.c
 * SIZE:    1546
 * SHA-256: 53ed29e955f19651017d3f66a9cd0bc8d5dd1ff0c4e060796420762d98aa11d3
 */
/* AMALGAMATE c:expand_include function/lua_write_file.c [BEG] */
#line 1 "function/lua_write_file.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <stdio.h>

static int _am_file_op(lua_State* L, const char* path, const char* mode,
    const char* data, size_t data_sz)
{
    int ret;
    int file_need_close = 0;
    FILE* file = NULL;

    if (strcmp(path, ":stdout") == 0)
    {
        file = stdout;
    }
    else if (strcmp(path, ":stderr") == 0)
    {
        file = stderr;
    }
    else
    {
        if ((ret = fopen_s(&file, path, mode)) != 0)
        {
            char buf[64];
            strerror_r(ret, buf, sizeof(buf));
            return luaL_error(L, "open `%s` failed: %s(%d).", path, buf, ret);
        }
        file_need_close = 1;
    }

    size_t write_cnt = fwrite(data, data_sz, 1, file);
    if (file_need_close)
    {
        fclose(file);
        file = NULL;
    }

    if (write_cnt != 1)
    {
        return luaL_error(L, "write file `%s` failed.", path);
    }

    return 0;
}

static int _am_write_file(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    size_t data_sz = 0;
    const char* data = luaL_checklstring(L, 2, &data_sz);

    const char* mode = "wb";
    if (lua_type(L, 3) == LUA_TSTRING)
    {
        mode = lua_tostring(L, 3);
    }

    return _am_file_op(L, path, mode, data, data_sz);
}

am_function_t am_f_write_file = {
"write_file", _am_write_file, "nil write_file(string path, string data[, string mode])",
"Write data to file.",

"Open file and write data into it.\n"
"\n"
"By default `mode` is set to \"wb\"."
};
/* AMALGAMATE c:expand_include function/lua_write_file.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/__init__.c
 * SIZE:    3228
 * SHA-256: e5e336dd371c14f1174c4df336f1fca1399a16af1b1c5809510033973f67f3de
 */
/* AMALGAMATE c:expand_include addon/__init__.c [BEG] */
#line 1 "addon/__init__.c"
/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */
#include <string.h>

static am_addon_t* s_addon_list[] = {
    &am_a_c_dump_hex,
    &am_a_c_expand_include,
    &am_a_txt_black_hole,
};

typedef void (*am_addon_load_cb)(lua_State* L, const char* name, int idx, void* arg);

/**
 * @brief Load all addons.
 * @param[in] L     Lua VM.
 * @param[in] cb    Load callback. Can be NULL.
 * @param[in] arg   User data passed to \p cb.
 */
static void _am_addon_load(lua_State* L, am_addon_load_cb cb, void* arg)
{
    size_t i;
    int sp = lua_gettop(L);

    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1);
        if (cb != NULL)
        {
            cb(L, s_addon_list[i]->name, sp + 1, arg);
        }
        lua_settop(L, sp);
    }
}

static void _addon_foreach(lua_State* L, const char* name, int idx, void* arg)
{
    int* p_ret_idx = (int*)arg;
    int ret_idx = *p_ret_idx;

    lua_pushvalue(L, ret_idx);
    lua_pushfstring(L, "%s\n    ", name);
    if (lua_getfield(L, idx, "brief") != LUA_TSTRING)
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NO BRIEF");
    }
    lua_pushstring(L, "\n");
    lua_concat(L, 4);
    lua_replace(L, ret_idx);
}

void am_addon_init(lua_State* L)
{
    _am_addon_load(L, NULL, NULL);
}

int am_addon_list(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_pushstring(L, ""); // sp+1: this will be the return value
    int idx = sp + 1;

    _am_addon_load(L, _addon_foreach, &idx);

    return 1;
}

static void _addon_manual(lua_State* L, const char* name, int ret_idx, int req_idx)
{
    /* NAME */
    lua_pushfstring(L, "[NAME]\n%s\n\n", name);

    /* BRIEF */
    lua_pushstring(L, "[BRIEF]\n");
    if (lua_getfield(L, req_idx, "brief") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n\n");
    }
    lua_concat(L, 2);

    /* DOCUMENT */
    lua_pushstring(L, "[DOCUMENT]\n");
    if (lua_getfield(L, req_idx, "desc") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n");
    }
    lua_concat(L, 2);

    /* Merge string */
    lua_concat(L, 3);

    /* Set return value */
    lua_replace(L, ret_idx);
}

int am_addon_manual(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* name = luaL_checkstring(L, 1);

    lua_pushstring(L, ""); // sp+1: return value.

    size_t i;
    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        if (strcmp(name, s_addon_list[i]->name) == 0)
        {
            luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1); // sp+2
            _addon_manual(L, name, sp + 1, sp + 2);
            lua_pop(L, 1);
            return 1;
        }
    }

    return 0;
}

int am_addon_call_script(lua_State* L, const char* script, const char* name)
{
    if (luaL_loadbuffer(L, script, strlen(script), name) != LUA_OK)
    {
        return lua_error(L);
    }

    lua_call(L, 0, 1);
    return 1;
}
/* AMALGAMATE c:expand_include addon/__init__.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/c_dump_hex.c
 * SIZE:    3080
 * SHA-256: 955503d906486cb5af7a1f49e80aafc783d3d22c6614758b2ec871063acf0c9a
 */
/* AMALGAMATE c:expand_include addon/c_dump_hex.c [BEG] */
#line 1 "addon/c_dump_hex.c"
#define LF "\n"
static const char* dump_hex_script = "\n" LF
LF
"local function dump_hex_proc(data, args)" LF
"    local src_data = data" LF
"    local ret = \"\"" LF
LF
"    -- Format arguments" LF
"    if args.include_stdint == nil then" LF
"        args.include_stdint = false" LF
"    end" LF
"    if args.append_eol == nil then" LF
"        args.append_eol = true" LF
"    end" LF
LF
"    -- Handle args.source_file" LF
"    if args.source_file ~= nil then" LF
"        src_data = am.load_file(args.source_file)" LF
"        ret = ret .. data" LF
"    end" LF
LF
"    -- Handle args.include_stdint" LF
"    if args.include_stdint then" LF
"        ret = ret .. \"#include <stdint.h>\\n#include <stddef.h>\\n\"" LF
"    end" LF
LF
"    -- Handle args.name_of_array" LF
"    if args.name_of_array == nil then" LF
"        error(\"missing argument `name_of_array`.\")" LF
"    end" LF
"    ret = ret .. \"const uint8_t \" .. args.name_of_array .. \" = {\\n\"" LF
"    local print_idx = 1" LF
"    for b in string.gmatch(src_data, '.') do" LF
"        if print_idx == 1 then" LF
"            ret = ret .. \"    \"" LF
"        end" LF
"        ret = ret .. string.format(\"0x%02x,\", string.byte(b))" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"            print_idx = 1" LF
"        else" LF
"            print_idx = print_idx + 1" LF
"        end" LF
"    end" LF
"    if args.append_eol then" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"        end" LF
"        ret = ret .. \"0x00\"" LF
"    end" LF
"    ret = ret .. \"\\n};\\n\"" LF
LF
"    -- Handle args.name_of_array_size" LF
"    if args.name_of_array_size ~= nil then" LF
"        ret = ret .. \"const size_t \" .. args.name_of_array_size .. \" = sizeof(\" .. args.name_of_array .. \")\"" LF
"        if args.append_eol then" LF
"            ret = ret .. \" - 1;\\n\"" LF
"        else" LF
"            ret = ret .. \";\\n\"" LF
"        end" LF
"    end" LF
LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = dump_hex_proc," LF
"    desc = " LF
"[[Dump anything into C array." LF
LF
"[ATTRIBUTES]" LF
"\"name_of_array\": [string]" LF
"    The name of dumped array variable." LF
"\"name_of_array_size\": [string]" LF
"    The name of dumped array size variable. If not specificed, the array" LF
"    size is not generated." LF
"\"source_file\": [string]" LF
"    The source file to dump. If not specificed, dump amalgamate content as" LF
"    hex array." LF
"\"include_stdint\": true|false. Default: false." LF
"    Set to true if need to include header file `stdint.h` and `stddef.h`." LF
"\"append_eol\": true|false. Default: true." LF
"    Whether append NULL terminal character to end of dumped array." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_c_dump_hex(lua_State* L)
{
    return am_addon_call_script(L, dump_hex_script, "c:dump_hex.lua");
}

am_addon_t am_a_c_dump_hex = {
    "c:dump_hex",
    _am_c_dump_hex,
};
/* AMALGAMATE c:expand_include addon/c_dump_hex.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/c_expand_include.c
 * SIZE:    4979
 * SHA-256: 2b7d5ff907248fa4ee421ffc6e3507cbe464c5dcd51605bb60c1c86569cdfd1d
 */
/* AMALGAMATE c:expand_include addon/c_expand_include.c [BEG] */
#line 1 "addon/c_expand_include.c"
#define LF  "\n"
static const char* expand_include_script = "\n" LF
LF
"local M = {}" LF
"-- This is the pattern to search `#include` statement." LF
"M.pattern = \"#%s*include%s+\\\"([-_/%.%w]+)\\\"\"" LF
LF
"-- Set default value if not exist" LF
"local function format_default_arguments(args)" LF
"    if args.lineno == nil then" LF
"        args.lineno = true" LF
"    end" LF
"    if args.fileinfo == nil then" LF
"        args.fileinfo = true" LF
"    end" LF
"    if args.displace_include == nil then" LF
"        args.displace_include = true" LF
"    end" LF
"    if args.quote_group == nil then" LF
"        args.quote_group = \"\"" LF
"    end" LF
"    return args" LF
"end" LF
LF
"-- Get file information for matched regex pattern" LF
"local function generate_file_info(include_path, data, args)" LF
"    local info = { include_path = include_path }" LF
"    info.real_path = am.search_file(info.include_path, args.quote_group)" LF
"    if info.real_path == nil then" LF
"        local err_msg = \"file `\" .. info.include_path .. \"` not found.\"" LF
"        error(err_msg)" LF
"    end" LF
"    info.txt_data = am.load_txt_file(info.real_path)" LF
"    info.bin_data = am.load_file(info.real_path)" LF
"    info.sha256 = am.sha256(info.bin_data)" LF
"    info.bin_size = string.len(info.bin_data)" LF
"    return info" LF
"end" LF
LF
"-- Generate file header" LF
"local function generate_file_header(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    local ret = \"/*\\n\"" LF
"    ret = ret .. \" * ADDON:   c:expand_include\\n\"" LF
"    ret = ret .. \" * PATH:    \" .. info.include_path .. \"\\n\"" LF
"    ret = ret .. \" * SIZE:    \" .. string.format(\"%q\", info.bin_size) .. \"\\n\"" LF
"    ret = ret .. \" * SHA-256: \" .. info.sha256 .. \"\\n\"" LF
"    ret = ret .. \" */\\n\"" LF
"    ret = ret .. \"/* AMALGAMATE c:expand_include \" .. info.include_path .. \" [BEG] */\\n\"" LF
"    return ret" LF
"end" LF
LF
"-- Generate file content" LF
"local function generate_file_content(info, args, regex)" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    if args.lineno then" LF
"        ret = ret .. \"#line 1 \\\"\" .. info.include_path .. \"\\\"\\n\"" LF
"    end" LF
"    if args.displace_include then" LF
"        temp = string.gsub(info.txt_data, M.pattern, \"/* AMALGAMATE_DISPLACE_INCLUDE: %1 */\")" LF
"    end" LF
"    ret = ret .. temp .. \"\\n\"" LF
"    return ret" LF
"end" LF
LF
"local function generate_file_tail(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    return \"/* AMALGAMATE c:expand_include \" .. info.include_path .. \" [END] */\\n\"" LF
"end" LF
LF
"-- c:expand_include" LF
"local function expand_include_proc(data, args)" LF
"    -- Local variable" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    local regex = M.regex" LF
LF
"    args = format_default_arguments(args)" LF
LF
"    while true do" LF
"        local off_beg, off_end, group_include = string.find(data, M.pattern)" LF
"        if off_beg == nil then" LF
"            ret = ret .. data" LF
"            break" LF
"        end" LF
LF
"        -- Append data before pattern" LF
"        if off_beg >= 2 then" LF
"            temp = string.sub(data, 1, off_beg - 1)" LF
"            ret = ret .. temp" LF
"        end" LF
LF
"        -- Get file information" LF
"        local info = generate_file_info(group_include, data, args)"
LF
"        -- Generate header" LF
"        temp = generate_file_header(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Append file content" LF
"        temp = generate_file_content(info, args)" LF
"        ret = ret .. temp" LF
LF
"        temp = generate_file_tail(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Update data" LF
"        data = string.sub(data, off_end + 1)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = expand_include_proc," LF
"    brief = \"Replace file content with #include path.\"," LF
"    desc = " LF
"[[Read #include file content and replace the #include statement."LF
LF
"[ATTRIBUTES]" LF
"\"quote_group\": [string]. Default: \"\"" LF
"    Specific which group to search." LF
"\"lineno\": true|false. Default: true." LF
"    Enable `#line 1 [path]` syntax so that if compile error, you known what" LF
"    is wrong." LF
"\"fileinfo\": true|false. Default: true" LF
"    Add file path, size, SHA-256 information before replacement." LF
"\"displace_include\": true|false. Default: true" LF
"    comment `#include \"foo.h\"`." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_c_expand_include(lua_State* L)
{
    return am_addon_call_script(L, expand_include_script, "c:expand_include.lua");
}

am_addon_t am_a_c_expand_include = {
    "c:expand_include",
    _am_c_expand_include,
};
/* AMALGAMATE c:expand_include addon/c_expand_include.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    addon/txt_black_hole.c
 * SIZE:    587
 * SHA-256: b81ee2ebaf920f049b11b24d56361efa3b9016d63bb6d29051477a004f10c6df
 */
/* AMALGAMATE c:expand_include addon/txt_black_hole.c [BEG] */
#line 1 "addon/txt_black_hole.c"
#define LF "\n"
static const char* black_hole_script = "\n" LF
"local function black_hole_proc(data, args)" LF
"    return \"\"" LF
"end" LF
LF
"return {" LF
"    proc = black_hole_proc," LF
"    brief = \"Eliminate anything.\","
"    desc = " LF
"[[Eliminate anything." LF
LF
"[ATTRIBUTES]" LF
"none." LF
"]]," LF
"}" LF
;

/* AMALGAMATE_DISPLACE_INCLUDE: __init__.h */

static int _am_txt_black_hole(lua_State* L)
{
    return am_addon_call_script(L, black_hole_script, "txt:black_hole.lua");
}

am_addon_t am_a_txt_black_hole = {
    "txt:black_hole",
    _am_txt_black_hole,
};
/* AMALGAMATE c:expand_include addon/txt_black_hole.c [END] */

/*
 * ADDON:   c:expand_include
 * PATH:    amalgamate.c
 * SIZE:    3520
 * SHA-256: 3e9fb364561ca2c4057a411a1cdafab7230796778ce2dc8df8bd56ff0338689e
 */
/* AMALGAMATE c:expand_include amalgamate.c [BEG] */
#line 1 "amalgamate.c"
#define LF  "\n"
const char* amalgamate_script = "\n\n\n\n\n" LF // let's align the line number

//////////////////////////////////////////////////////////////////////////
// Script begin
//////////////////////////////////////////////////////////////////////////
"local cjson = require(\"cjson\")" LF
LF
"-- Process data with addon configuration" LF
"local function process_json_addon(data, config)" LF
"    config.args = config.args or {}" LF
"    if config.name == nil then" LF
"        local errmsg = \"missing field `name` in json\"" LF
"        error(errmsg)" LF
"    end" LF
"    local addon = require(config.name)" LF
"    return addon.proc(data, config.args)" LF
"end" LF
LF
"-- Process json block" LF
"local function process_json_block(v)" LF
"    local config = cjson.from_json(v.code)" LF
"    local data = v.data" LF
"    if am.table_is_array(config) then" LF
"        for _, e in ipairs(config) do" LF
"            data = process_json_addon(data, e)" LF
"        end" LF
"    else" LF
"        data = process_json_addon(data, config)" LF
"    end" LF
"    return data" LF
"end" LF
LF
"-- Process lua block" LF
"local function process_lua_block(v)" LF
"    local trunk, errmsg = load(v.code)" LF
"    if not trunk then" LF
"        error(errmsg)" LF
"    end" LF
"    local b,addon = pcall(trunk)" LF
"    if b ~= true then" LF
"        error(addon)" LF
"    end" LF
"    return addon.proc(v.data, {})" LF
"end" LF
LF
"-- Preprocess file" LF
"local function preprocess(data)" LF
"    local ret = {}" LF
"    while true do" LF
"        local off_beg_0, off_end_0, group_lang, group_code, group_data" LF
"            = string.find(data, am.config.parser_pattern)" LF
"        if off_beg_0 == nil then" LF
"            ret[#ret + 1] = { data = data }" LF
"            break" LF
"        end" LF
"        if off_beg_0 > 1 then" LF
"            ret[#ret + 1] = { data = string.sub(data, 1, off_beg_0 - 1) }" LF
"        end" LF
"        ret[#ret + 1] = {" LF
"            lang = group_lang," LF
"            code = group_code," LF
"            data = group_data," LF
"        }" LF
"        data = string.sub(data, off_end_0 + 1)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"-- All runtime information" LF
"local rt = {}" LF
LF
"-- Read input file" LF
"rt.input_content = am.load_txt_file(am.config.input)" LF
LF
"-- Split input file into sequence of token" LF
"local payload = preprocess(rt.input_content)" LF
LF
"-- For each token let's do the magic" LF
"for _,v in ipairs(payload) do" LF
"    if v.lang == nil then" LF
"        -- do nothing" LF
"    elseif am.strcasecmp(v.lang, \"lua\") == 0 then" LF
"        v.data = process_lua_block(v)" LF
"    elseif am.strcasecmp(v.lang, \"json\") == 0 then" LF
"        v.data = process_json_block(v)" LF
"    else" LF
"        local err_msg = \"unknown lang `\" .. v.lang .. \"`.\"" LF
"        error(err_msg)" LF
"    end" LF
LF
"    if v.data == nil then" LF
"        v.data = \"\"" LF
"    end" LF
"end" LF
LF
"-- Generate content" LF
"rt.output_content = \"\"" LF
"for _,v in ipairs(payload) do" LF
"    rt.output_content = rt.output_content .. v.data .. \"\\n\"" LF
"end" LF
LF
"-- Write file" LF
"am.write_file(am.config.output, rt.output_content)" LF

//////////////////////////////////////////////////////////////////////////
// Script end
//////////////////////////////////////////////////////////////////////////
;

/* AMALGAMATE_DISPLACE_INCLUDE: amalgamate.h */
/* AMALGAMATE c:expand_include amalgamate.c [END] */



//////////////////////////////////////////////////////////////////////////
// Embed source code
//////////////////////////////////////////////////////////////////////////

#define AMALGAMATE_VERSION_STRINGIFY(x) AMALGAMATE_VERSION_STRINGIFY_2(x)
#define AMALGAMATE_VERSION_STRINGIFY_2(x) #x

#define AMALGAMATE_VERSION_STRING   \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_MAJRO) \
    "." \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_MINOR) \
    "." \
    AMALGAMATE_VERSION_STRINGIFY(AMALGAMATE_VERSION_PATCH)

typedef struct amalgamate_ctx
{
    lua_State* L;
} amalgamate_ctx_t;

static amalgamate_ctx_t G = { NULL };

static const char* s_help =
"amalgamate v" AMALGAMATE_VERSION_STRING " - Merge your source code into one big file.\n"
"Usage: amalgamate [OPTIONS] -- [FILES]\n"
"\n"
"OPTIONS:\n"
"  --input=PATH\n"
"    Input file path.\n"
"\n"
"  --output=PATH\n"
"    Path to output file.\n"
"\n"
"  --iquote=PATH\n"
"  --iquote=GROUP=PATH\n"
"    Add the directory dir to the list of directories to be searched. If `GROUP`\n"
"    exist, add the directory to the group. This option affect how to search the\n"
"    file (see `--man=search_file` for details).\n"
"\n"
"  --logfile=PATH\n"
"    Where to store log output. And exists content will be erased.\n"
"\n"
"  --list-addon\n"
"    List builtin addons and exit.\n"
"\n"
"  --list-function\n"
"    List builtin functions and exit.\n"
"\n"
"  --man=STRING\n"
"    Show manual of function or addon.\n"
"\n"
"  -v, --version\n"
"    Show software version and exit.\n"
"\n"
"  -h, --help\n"
"    Show this help and exit.\n"
"\n"
"  --verbose\n"
"    Show extra output.\n"
"\n";

static int _setup_arg_output(lua_State* L, int idx, char* str)
{
    lua_pushcfunction(L, am_f_fmtpath.addr);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "output");
    return 0;
}

static int _setup_arg_input(lua_State* L, int idx, char* str)
{
    /* Save input file path */
    lua_pushcfunction(L, am_f_fmtpath.addr);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);
    lua_setfield(L, idx, "input");

    return 0;
}

static int _setup_arg_iquote_with_group(lua_State* L, int idx, const char* group, const char* path)
{
    int sp = lua_gettop(L);

    lua_getfield(L, idx, "iquote"); // sp+1
    if (lua_getfield(L, -1, group) != LUA_TTABLE) // sp+2
    {
        lua_pop(L, 1);
        lua_newtable(L);
    }

    lua_pushstring(L, path); // sp+3
    lua_seti(L, sp + 2, luaL_len(L, sp + 2) + 1); // sp+2

    lua_setfield(L, sp + 1, group); // sp+1
    lua_setfield(L, idx, "iquote");

    return 0;
}

static int _setup_arg_iquote(lua_State* L, int idx, char* str)
{
    const char* pos = strstr(str, "=");
    if (pos == NULL)
    {
        return _setup_arg_iquote_with_group(L, idx, "", str);
    }

    lua_pushlstring(L, str, pos - str);

    const char* group = lua_tostring(L, -1);
    int ret = _setup_arg_iquote_with_group(L, idx, group, pos + 1);
    lua_pop(L, 1);

    return ret;
}

static int _setup_arg_man(lua_State* L, int idx, char* str)
{
    (void)idx;

    lua_pushcfunction(L, am_function_manual);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);

    if (lua_type(L, -1) == LUA_TSTRING)
    {
        goto show_man;
    }
    lua_pop(L, 1);

    lua_pushcfunction(L, am_addon_manual);
    lua_pushstring(L, str);
    lua_call(L, 1, 1);

    if (lua_type(L, -1) == LUA_TSTRING)
    {
        goto show_man;
    }
    lua_pop(L, 0);

    return luaL_error(L, "No manual for %s.", str);

show_man:
    fprintf(stdout, "%s\n", lua_tostring(L, -1));
    exit(EXIT_SUCCESS);
}

static void _clear_log_file(const char* str)
{
    FILE* file;
    char buf[64];

    int ret = fopen_s(&file, str, "wb");
    if (ret != 0)
    {
        strerror_r(ret, buf, sizeof(buf));
        fprintf(stderr, "open `%s` failed: %s(%d).\n", str, buf, ret);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    file = NULL;
}

static int _setup_arg_logfile(lua_State* L, int idx, char* str)
{
    lua_pushstring(L, str);
    lua_setfield(L, idx, "logfile");

    if (str[0] != ':')
    {
        _clear_log_file(str);
    }

    return 0;
}

static int _setup_arg_verbose(lua_State* L, int idx, char* str)
{
    (void)str;
    lua_pushboolean(L, 1);
    lua_setfield(L, idx, "verbose");
    return 0;
}

static int _setup_arg_list_addon(lua_State* L, int idx, char* str)
{
    (void)idx; (void)str;
    lua_pushcfunction(L, am_addon_list);
    lua_call(L, 0, 1);
    fprintf(stdout, "%s", lua_tostring(L, -1));
    exit(EXIT_SUCCESS);
}

static int _setup_arg_list_function(lua_State* L, int idx, char* str)
{
    (void)idx; (void)str;
    lua_pushcfunction(L, am_list_function);
    lua_call(L, 0, 1);
    fprintf(stdout, "%s\n", luaL_checkstring(L, -1));
    exit(EXIT_SUCCESS);
}

static int _parser_arguments(lua_State* L, int idx, int argc, char* argv[])
{
#define PARSER_LONGOPT_WITH_VALUE(OPT, FUNC)   \
    do {\
        int ret = -1; const char* opt = OPT;\
        size_t optlen = strlen(opt);\
        if (strncmp(argv[i], opt, optlen) == 0) {\
            if (argv[i][optlen] == '=') {\
                ret = FUNC(L, idx, argv[i] + optlen + 1);\
            } else if (i < argc - 1) {\
                ret = FUNC(L, idx, argv[i + 1]); i++;\
            }\
            if (ret != 0) {\
                return luaL_error(L, "Invalid argument to `%s'", opt);\
            }\
            continue;\
        }\
    } while (0)

#define PARSER_LONGOPT_NO_VALUE(OPT, FUNC)   \
    do {\
        const char* opt = OPT;\
        if (strcmp(argv[i], opt) == 0) {\
            FUNC(L, idx, NULL);\
        }\
    } while (0)

    int i;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("%s\n", s_help);
            exit(EXIT_SUCCESS);
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("v%s\n", AMALGAMATE_VERSION_STRING);
            exit(EXIT_SUCCESS);
        }

        PARSER_LONGOPT_WITH_VALUE("--output", _setup_arg_output);
        PARSER_LONGOPT_WITH_VALUE("--input", _setup_arg_input);
        PARSER_LONGOPT_WITH_VALUE("--iquote", _setup_arg_iquote);
        PARSER_LONGOPT_WITH_VALUE("--man", _setup_arg_man);
        PARSER_LONGOPT_WITH_VALUE("--logfile", _setup_arg_logfile);
        PARSER_LONGOPT_NO_VALUE("--verbose", _setup_arg_verbose);
        PARSER_LONGOPT_NO_VALUE("--list-addon", _setup_arg_list_addon);
        PARSER_LONGOPT_NO_VALUE("--list-function", _setup_arg_list_function);
    }

    return 0;

#undef PARSER_LONGOPT_WITH_VALUE
#undef PARSER_LONGOPT_NO_VALUE
}

static void _setup_default_arguments(lua_State* L, int idx)
{
    /* .verbose */
    lua_pushboolean(L, 0);
    lua_setfield(L, idx, "verbose");

    /* .iquote */
    lua_newtable(L);
    lua_setfield(L, idx, "iquote");

    /* .output */
    lua_pushstring(L, AMALGAMATE_DEFAULT_OUTPUT);
    lua_setfield(L, idx, "output");

    lua_pushstring(L, AMALGAMATE_DEFAULT_LOGFILE);
    lua_setfield(L, idx, "logfile");

    lua_pushstring(L, AMALGAMATE_PARSER_PATTERN);
    lua_setfield(L, idx, "parser_pattern");

    lua_pushstring(L, AMALGAMATE_DEFAULT_OUTPUT);
    lua_setfield(L, idx, "default_output");

    lua_pushstring(L, AMALGAMATE_DEFAULT_LOGFILE);
    lua_setfield(L, idx, "default_logfile");
}

static int _check_arguments(lua_State* L, int idx)
{
    if (lua_getfield(L, idx, "input") != LUA_TSTRING)
    {
        return luaL_error(L, "Missing argument `--input`.");
    }
    lua_pop(L, 1);

    return 0;
}

static void _generate_arg_table(lua_State* L, int argc, char* argv[])
{
    int sp = lua_gettop(L);

    lua_getglobal(L, AMALGAMATE_NAMESPACE); // sp+1

    lua_newtable(L); // sp + 2
    _setup_default_arguments(L, sp + 2);
    _parser_arguments(L, sp + 2, argc, argv);
    _check_arguments(L, sp + 2);

    lua_setfield(L, sp + 1, "config");
    lua_setglobal(L, AMALGAMATE_NAMESPACE);
}

static void _am_openlibs(lua_State* L)
{
    /* open cjson */
    luaL_requiref(L, "cjson", luaopen_cjson, 0);
    lua_pop(L, 1);

    /* Amalgamate API */
    luaopen_am(L);
    lua_setglobal(L, AMALGAMATE_NAMESPACE);
}

static int _pmain(lua_State* L)
{
    luaL_openlibs(L);
    _am_openlibs(L);
    am_addon_init(L);

    int argc = (int)lua_tointeger(L, 1);
    char** argv = lua_touserdata(L, 2);
    _generate_arg_table(L, argc, argv);

    int ret = luaL_loadbuffer(L, amalgamate_script, strlen(amalgamate_script),
        "amalgamate.lua");
    if (ret != LUA_OK)
    {
        return lua_error(L);
    }

    lua_call(L, 0, 0);

    return 0;
}

/**
 * @brief Lua error traceback helper.
 * @param[in] L     Lua VM.
 * @return          Always 1.
 */
static int _msg_handler(lua_State* L)
{
    const char* msg = lua_tostring(L, 1);
    if (msg == NULL)
    {  /* is error object not a string? */
        if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
            lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
        {
            return 1;  /* that is the message */
        }

        msg = lua_pushfstring(L, "(error object is a %s value)",
            luaL_typename(L, 1));
    }
    luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
    return 1;  /* return the traceback */
}

static void _at_exit(void)
{
    if (G.L != NULL)
    {
        lua_close(G.L);
        G.L = NULL;
    }
}

int main(int argc, char* argv[])
{
    atexit(_at_exit);

    G.L = luaL_newstate();

    lua_pushcfunction(G.L, _msg_handler);
    lua_pushcfunction(G.L, _pmain);
    lua_pushinteger(G.L, argc);
    lua_pushlightuserdata(G.L, argv);
    if (lua_pcall(G.L, 2, 0, 1) != LUA_OK)
    {
        fprintf(stderr, "%s", lua_tostring(G.L, -1));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
