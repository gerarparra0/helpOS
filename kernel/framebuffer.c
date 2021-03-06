#include "framebuffer.h"

// imported virtual addresses
extern BOOTBOOT bootboot;           // see bootboot.h
extern uint8_t fb;                  // linear framebuffer mapped

int fb_x = 0, fb_y = 0;

// psf header
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
} __attribute__((packed)) psf2_t;
extern volatile unsigned char _binary_font_psf_start;

// print a single character with a background and foreground given a PSF font
void fb_putchar(unsigned short int c, int x, int y, uint32_t fg, uint32_t bg)
{
    psf2_t *font = (psf2_t*)&_binary_font_psf_start;

    int bytesperline = (font->width + 7) / 8;

    unsigned char *glyph = (unsigned char *)&_binary_font_psf_start + font->headersize + (c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
    int offs = (y * font->height * bootboot.fb_scanline) + (x * (font->width + 1) * 4);

    int line, mask;

    for(int i = 0; i < font->height; i++)
    {
        line = offs;
        mask = 1 << (font->width - 1);
        // display a row
        for(int j = 0; j < font->width; j++)
        {
            *(uint32_t*)(&fb + line) = (((uint32_t) *glyph) & (mask) ? fg : bg);
            mask >>= 1;
            line += 4;
        }
        
        glyph += bytesperline;
        offs += bootboot.fb_scanline;
    }

    if(x >= bootboot.fb_width)
    {
        fb_x = 0;
        fb_y++;
    }
}

// print a string
void fb_puts(char *str)
{
    while(*str)
    {
        fb_putc(*str);
        str++;
    }
}

// clear the framebuffer without saving
void fb_clear()
{
    memset(&fb, 0x0, bootboot.fb_size);
    fb_x = 0; fb_y = 0;
}

// need to implement more single character behavior as I go along
void fb_putc(unsigned short int c)
{
    switch(c)
    {
        case '\n':
            fb_y++;
            fb_x = 0;
            break;
        default:
            fb_putchar(c, fb_x, fb_y, 0xFFFFFFFF, 0x0);
            fb_x++;
            break;
    }
}

// for now these routines print the numbers in reverse :(
// need to find an algorithm to reverse them before having kmalloc()
void fb_print_hex(long int hex)
{
    if(hex == 0)
        fb_putc('0');
    
    else
    {
        // i is the 'size' of the number
        // t_i is to remember i so we can reset the fb_x
        long int copy = hex;
        int i = 0, t_i = 0;

        while(copy)
        {
            i++;
            copy /= 16;
        }

        t_i = i;

        while(hex)
        {
            if(hex%16 < 0xA)
                fb_putchar((unsigned short)('0' + hex%16), (fb_x + i--) - 1, fb_y, 0xFFFFFFFF, 0x0);
            else
                fb_putchar((unsigned short)('A' + hex%16 - 10), (fb_x + i--) - 1, fb_y, 0xFFFFFFFF, 0x0);
            
            hex /= 16;
        }

        fb_x += t_i;
    }
}

void fb_print_dec(long int dec)
{   
    if(dec == 0)
    {
        fb_putc('0');
    }

    else
    {
        long int copy = dec;
        // i is the 'size' of the number
        // t_i is to remember i so we can reset the fb_x
        int i = 0, t_i = 0;

        while(copy)
        {
            i++;
            copy /= 10;
        }

        // dont forget!
        t_i = i;

        while(dec)
        {
            fb_putchar((unsigned short)('0' + dec%10), (fb_x + i--) - 1, fb_y, 0xFFFFFFFF, 0x0);
            dec /= 10;
        }

        fb_x += t_i;
    }
}