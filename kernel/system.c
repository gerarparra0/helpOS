#include "system.h"

size_t strlen(const char *str)
{
    size_t i;

    for(i = 0; str[i] != '\0'; i++);

    return i;
}

// copy bytes from source to dest
void *memcpy(void *dest, const void *src, size_t num)
{
    char *d_cpy = dest;
    const char *s_cpy = src;

    while(num--)
        *d_cpy++ = *s_cpy++;
    
    return dest;
}

// 
void *memset(void *dest, uint32_t val, size_t num)
{
    uint8_t *d_cpy = dest;

    while(num--)
        *d_cpy++ = (uint8_t) val;

    return dest;
}