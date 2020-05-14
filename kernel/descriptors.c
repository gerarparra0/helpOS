#include "descriptors.h"

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
idt_entry_t     idt_entries[31];
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
    asm volatile("lgdt %0;"
                  :
                  : "m" (gdt_ptr));
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
    /*
    IST Field (Interrupt and Trap Gates). Bits 2:0 of byte +4. Long-mode interrupt gate and trap gate
    descriptors contain a new, 3-bit interrupt-stack-table (IST) field not present in legacy gate descriptors.
    The IST field is used as an index into the IST portion of a long-mode TSS. If the IST field is not 0, the
    index references an IST pointer in the TSS, which the processor loads into the RSP register when an
    interrupt occurs. If the IST index is 0, the processor uses the legacy stack-switching mechanism (with
    some modifications) when an interrupt occurs. See “Interrupt-Stack Table” on page 259 for more
    information.
    */

    // next implement and install all ISR handlers according to the AMD64 manual
}

static void idt_set_gate(uint8_t number, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t access)
{
    idt_entries[number].offset_low      = offset & 0xFFFF;
    idt_entries[number].offset_middle   = (offset >> 16) & 0xFFFF;
    idt_entries[number].offset_high     = (offset >> 32) & 0xFFFFFFFF;

    idt_entries[number].selector        = selector;

    idt_entries[number].ist             = ist & 0x07;
    idt_entries[number].access          = access;
}