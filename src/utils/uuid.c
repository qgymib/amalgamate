#include "uuid.h"
#include <stddef.h>

static unsigned long s_rand_seed = 1;

static unsigned long _uuid_rand(void)
{
    s_rand_seed = 1103515245UL * s_rand_seed + 12345;
    return s_rand_seed;
}

static char _uuid_get_char(void)
{
    static char s_key[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f',
    };

    unsigned long key = _uuid_rand();
    size_t pos = key % sizeof(s_key);
    return s_key[pos];
}

void amalgamate_uuid_gen(amalgamate_uuid_t* uuid)
{
    size_t i;
    for (i = 0; i < 8; i++)
    {
        uuid->uuid[i] = _uuid_get_char();
    }
    uuid->uuid[8] = '-';
    for (i = 9; i < 13; i++)
    {
        uuid->uuid[i] = _uuid_get_char();
    }
    uuid->uuid[13] = '-';
    for (i = 14; i < 18; i++)
    {
        uuid->uuid[i] = _uuid_get_char();
    }
    uuid->uuid[18] = '-';
    for (i = 19; i < 23; i++)
    {
        uuid->uuid[i] = _uuid_get_char();
    }
    uuid->uuid[23] = '-';
    for (i = 24; i < 36; i++)
    {
        uuid->uuid[i] = _uuid_get_char();
    }
    uuid->uuid[36] = '\0';
}
