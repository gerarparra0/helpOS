#ifndef __DESCRIPTORS_H
#define __DESCRIPTORS_H

#include "system.h"

// long mode GDT pointer
struct gdt_ptr_struct
{
    uint16_t    limit;          // size of GDT in bytes
    uint64_t    base;           // holds the starting address of the GDT in virtual space
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// long mode GDT entry
struct gdt_entry_struct
{
    uint16_t    limit_low;
    uint16_t    base_low;

    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

// long mode IDT pointer
struct idt_ptr_struct
{
    uint16_t    limit;
    uint64_t    base;       // in long mode the base has to be a 64bit address
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// long mode IDT
struct idt_entry_struct
{
    uint16_t    offset_low;
    uint16_t    selector;
    
    uint8_t     ist;
    uint8_t     access;
    uint16_t    offset_middle;

    uint32_t    offset_high;

    uint32_t    reserved;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// initialize descriptor tables
void init_descriptors();


#endif