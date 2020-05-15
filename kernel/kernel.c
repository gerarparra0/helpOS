#include "framebuffer.h"
#include "descriptors.h"

// called by bootboot as it hands over control
void _start()
{
    // 
    fb_clear();

    // install 64bit drivers
    fb_puts("Installing Descriptors...\n");
    init_descriptors();
    fb_puts("Descriptors Installed.\n");

    fb_puts("Interrupt test...\n");
    asm volatile("#GP");

    // hang for now
    while(1);
}