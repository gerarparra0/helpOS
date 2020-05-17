#include "descriptors.h"
#include "interrupts.h"
#include "framebuffer.h"

// we need 5 entries
// gdt_entries[0] always null
// gdt_entries[1] kernel code segment
// gdt_entries[2] kernel data segment
gdt_entry_t     gdt_entries[3];
gdt_ptr_t       gdt_ptr;

// internal functions
// intialize GDT structure
static void gdt_init();
// set a single gate for the GDT
static void gdt_set_gate(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

// for now only make the first 31 faults
idt_entry_t     idt_entries[256];
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
    gdt_ptr.limit = sizeof(gdt_entry_t) * 3 - 1;

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
    gdt_set_gate(1, 0x0, 0x0, 0x9A, 0x20);
    // kernel data segment
    // only care if the segment is present
    gdt_set_gate(2, 0x0, 0x0, 0x92, 0x0);
    
    // flush gdt
    asm("lgdt %0": : "m" (gdt_ptr));
}

static void gdt_set_gate(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_entries[number].base_low        = base & 0xFFFF;
    gdt_entries[number].base_middle     = (base >> 16) & 0xFF;
    gdt_entries[number].base_high       = (base >> 24) & 0xFF;

    gdt_entries[number].limit_low       = limit & 0xFFFF;

    gdt_entries[number].granularity     = granularity;
    gdt_entries[number].access          = access;
}

static void idt_init()
{
    idt_ptr.base = (uint64_t)&idt_entries;
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    // 0x8 is the code kernel code segment (each GDT entry is 8 bytes), to be used as the selector of the interrupt routines
    // 0 IST for now
    // 0x8E: P = 1, DPL = 00, 0, Interrupt Gate (E)
    idt_set_gate(0, (uint64_t)interrupt0, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(1, (uint64_t)interrupt1, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(2, (uint64_t)interrupt2, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(3, (uint64_t)interrupt3, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(4, (uint64_t)interrupt4, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(5, (uint64_t)interrupt5, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(6, (uint64_t)interrupt6, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(7, (uint64_t)interrupt7, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(8, (uint64_t)interrupt8, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(9, (uint64_t)interrupt9, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(10, (uint64_t)interrupt10, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(11, (uint64_t)interrupt11, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(12, (uint64_t)interrupt12, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(13, (uint64_t)interrupt13, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(14, (uint64_t)interrupt14, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(15, (uint64_t)interrupt15, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(16, (uint64_t)interrupt16, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(17, (uint64_t)interrupt17, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(18, (uint64_t)interrupt18, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(19, (uint64_t)interrupt19, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(20, (uint64_t)interrupt20, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(21, (uint64_t)interrupt21, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(22, (uint64_t)interrupt22, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(23, (uint64_t)interrupt23, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(24, (uint64_t)interrupt24, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(25, (uint64_t)interrupt25, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(26, (uint64_t)interrupt26, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(27, (uint64_t)interrupt27, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(28, (uint64_t)interrupt28, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(29, (uint64_t)interrupt29, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(30, (uint64_t)interrupt30, sizeof(gdt_entries[0]), 0x0, 0x8E);
    idt_set_gate(31, (uint64_t)interrupt31, sizeof(gdt_entries[0]), 0x0, 0x8E);

    asm volatile("lidt %0": :"m"(idt_ptr));
}

static void idt_set_gate(uint8_t number, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t access)
{
    offset |= 0xFFF0000000000000;
    // some debug info
    idt_entries[number].offset_low      = offset & 0xFFFF;
    idt_entries[number].offset_middle   = (offset >> 16) & 0xFFFF;
    idt_entries[number].offset_high     = (offset >> 32) & 0xFFFFFFFF;
    //idt_entries[number].offset_high     |= 0xFFFF0000;

    idt_entries[number].selector        = selector;

    idt_entries[number].ist             = ist & 0x7;
    idt_entries[number].access          = access;
    idt_entries[number].reserved        = 0x0;
}

void interrupt_handler(registers_t registers)
{
    fb_puts("Interrupt "); fb_print_dec(registers.interrupt); fb_puts(" fired with error code "); fb_print_dec(registers.error); fb_putc('\n');
}