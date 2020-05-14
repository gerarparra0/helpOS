#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

#include "system.h"
#include "bootboot.h"

void fb_puts(char *s);
//void fb_putchar(unsigned short int c, int x, int y, uint32_t fg, uint32_t bg);

void fb_putc(unsigned short int c);
void fb_clear();

void fb_print_hex(long int dec);
void fb_print_dec(long int dec);

#endif