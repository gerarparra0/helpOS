#include "framebuffer.h"
#include "descriptors.h"

void _start()
{
    // 
    fb_clear();

    // install 64bit drivers
    fb_puts("Installing GDT...\n");
    init_descriptors();
    fb_puts("GDT Installed.\n");

    fb_print_hex(1234567890);

    // hang for now
    while(1);
}