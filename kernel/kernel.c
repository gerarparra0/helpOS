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
    int i = 40, y = 0;
    i = i / y;

    // hang for now
    while(1);
}