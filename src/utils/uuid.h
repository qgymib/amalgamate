#ifndef __AMALGAMATE_UTILS_UUID_H__
#define __AMALGAMATE_UTILS_UUID_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef struct amalgamate_uuid
{
	char uuid[37];
} amalgamate_uuid_t;

void amalgamate_uuid_gen(amalgamate_uuid_t* uuid);

#ifdef __cplusplus
}
#endif
#endif
