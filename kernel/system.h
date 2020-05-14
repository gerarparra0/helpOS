#ifndef __SYSTEM_H
#define __SYSTEM_H

/* we don't assume stdint.h exists */
typedef short int           int16_t;
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;
typedef uint32_t size_t;

size_t strlen(const char *str);
void *memcpy(void *dest, const void *src, size_t num);
void *memset(void *dest, uint32_t val, size_t num);

#endif