#include "descriptors.h"
#include "interrupts.h"
#include "framebuffer.h"

// we need 5 entries
// gdt_entries[0] always null
// gdt_entries[1] kernel code segment
// gdt_entries[2] kernel data segment
// gdt_entries[3] user code segment
// gdt_entries[4] user data segment
gdt_entry_t     gdt_entries[5];
gdt_ptr_t       gdt_ptr;

// internal functions
// intialize GDT structure
static void gdt_init();
// set a single gate for the GDT
static void gdt_set_gate(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

// for now only make the first 31 faults
idt_entry_t     idt_entries[32];
idt_ptr_t       idt_ptr;

static void idt_init();
static void idt_set_gate(uint8_t number, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t access);

void init_descriptors()
{
    gdt_init();
    idt_init();
}

static void gdt_init()
{
    gdt_ptr.base = (uint64_t)&gdt_entries;
    gdt_ptr.limit = sizeof(gdt_entry_t) * 5 - 1;

    // setup entries
    // null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);    // null

    // kernel code segment
    // access
    // C    = 0 (non-conforming)
    // DPL  = 0 (highest priority)
    // P    = 1 (present)
    // granularity
    // L    = 1 (long mode)
    // D    = 0 (64 bit only system)
    gdt_set_gate(1, 0x0, 0x0, 0x98, 0x20);
    // kernel data segment
    // only care if the segment is present
    gdt_set_gate(2, 0x0, 0x0, 0x80, 0x0);

    // user mode descriptors
    // code
    gdt_set_gate(3, 0x0, 0x0, 0xFC, 0x20);
    // data
    // only neds to be present
    gdt_set_gate(4, 0x0, 0x0, 0x80, 0x0);
    
    // flush gdt
    asm volatile("lgdt %0;": : "m" (gdt_ptr));
}

static void gdt_set_gate(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_entries[number].base_low        = base & 0xFFFF;
    gdt_entries[number].base_middle     = (base >> 16) & 0xFF;
    gdt_entries[number].base_high       = (base >> 24) & 0xFF;

    gdt_entries[number].limit_low       = limit & 0xFFFF;
    gdt_entries[number].granularity     = (limit >> 16) & 0x0F;

    gdt_entries[number].granularity     |= granularity & 0xF0;
    gdt_entries[number].access          = access;
}

static void idt_init()
{
    idt_ptr.base = (uint64_t)&idt_entries;
    idt_ptr.limit = sizeof(idt_entry_t) * 32 - 1;

    // 0x8 is the code kernel code segment (each GDT entry is 8 bytes), to be used as the selector of the interrupt routines
    // 0 IST for now
    // 0x8E: P = 1, DPL = 00, 0, Interrupt Gate (E)
    idt_set_gate(0, (uint64_t)interrupt0, 0x8, 0x0, 0x8E);
    idt_set_gate(1, (uint64_t)interrupt1, 0x8, 0x0, 0x8E);
    idt_set_gate(2, (uint64_t)interrupt2, 0x8, 0x0, 0x8E);
    idt_set_gate(3, (uint64_t)interrupt3, 0x8, 0x0, 0x8E);
    idt_set_gate(4, (uint64_t)interrupt4, 0x8, 0x0, 0x8E);
    idt_set_gate(5, (uint64_t)interrupt5, 0x8, 0x0, 0x8E);
    idt_set_gate(6, (uint64_t)interrupt6, 0x8, 0x0, 0x8E);
    idt_set_gate(7, (uint64_t)interrupt7, 0x8, 0x0, 0x8E);
    idt_set_gate(8, (uint64_t)interrupt8, 0x8, 0x0, 0x8E);
    idt_set_gate(9, (uint64_t)interrupt9, 0x8, 0x0, 0x8E);
    idt_set_gate(10, (uint64_t)interrupt10, 0x8, 0x0, 0x8E);
    idt_set_gate(11, (uint64_t)interrupt11, 0x8, 0x0, 0x8E);
    idt_set_gate(12, (uint64_t)interrupt12, 0x8, 0x0, 0x8E);
    idt_set_gate(13, (uint64_t)interrupt13, 0x8, 0x0, 0x8E);
    idt_set_gate(14, (uint64_t)interrupt14, 0x8, 0x0, 0x8E);
    idt_set_gate(15, (uint64_t)interrupt15, 0x8, 0x0, 0x8E);
    idt_set_gate(16, (uint64_t)interrupt16, 0x8, 0x0, 0x8E);
    idt_set_gate(17, (uint64_t)interrupt17, 0x8, 0x0, 0x8E);
    idt_set_gate(18, (uint64_t)interrupt18, 0x8, 0x0, 0x8E);
    idt_set_gate(19, (uint64_t)interrupt19, 0x8, 0x0, 0x8E);
    idt_set_gate(20, (uint64_t)interrupt20, 0x8, 0x0, 0x8E);
    idt_set_gate(21, (uint64_t)interrupt21, 0x8, 0x0, 0x8E);
    idt_set_gate(22, (uint64_t)interrupt22, 0x8, 0x0, 0x8E);
    idt_set_gate(23, (uint64_t)interrupt23, 0x8, 0x0, 0x8E);
    idt_set_gate(24, (uint64_t)interrupt24, 0x8, 0x0, 0x8E);
    idt_set_gate(25, (uint64_t)interrupt25, 0x8, 0x0, 0x8E);
    idt_set_gate(26, (uint64_t)interrupt26, 0x8, 0x0, 0x8E);
    idt_set_gate(27, (uint64_t)interrupt27, 0x8, 0x0, 0x8E);
    idt_set_gate(28, (uint64_t)interrupt28, 0x8, 0x0, 0x8E);
    idt_set_gate(29, (uint64_t)interrupt29, 0x8, 0x0, 0x8E);
    idt_set_gate(30, (uint64_t)interrupt30, 0x8, 0x0, 0x8E);
    idt_set_gate(31, (uint64_t)interrupt31, 0x8, 0x0, 0x8E);

    asm volatile("lidt %0": :"m"(idt_ptr));
}

static void idt_set_gate(uint8_t number, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t access)
{
    // some debug info
    idt_entries[number].offset_low      = offset & 0xFFFF;
    idt_entries[number].offset_middle   = (offset >> 16) & 0xFFFF;
    idt_entries[number].offset_high     = (offset >> 32) & 0xFFFFFFFF;

    idt_entries[number].selector        = selector;

    idt_entries[number].ist             = ist & 0x07;
    idt_entries[number].access          = access;
}

void interrupt_handler(uint64_t error, uint64_t interrupt_n, uint64_t rflags)
{
    fb_puts("Interrupt "); fb_print_dec(interrupt_n); fb_puts(" fired with error code: ");
    fb_print_hex(error); fb_puts(" RFLAGS register: "); fb_print_hex(rflags); fb_putc('\n'); 
}