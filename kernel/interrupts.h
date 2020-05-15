/*
0 Divide-by-Zero-Error #DE DIV, IDIV, AAM instructions
1 Debug #DB Instruction accesses and data accesses
2 Non-Maskable-Interrupt #NMI External NMI signal
3 Breakpoint #BP INT3 instruction
4 Overflow #OF INTO instruction
5 Bound-Range #BR BOUND instruction
6 Invalid-Opcode #UD Invalid instructions
7 Device-Not-Available #NM x87 instructions
8 Double-Fault #DF Exception during the handling of another exception or interrupt
9 Coprocessor-Segment-Overrun 
10 Invalid-TSS #TS Task-state segment access and task switch
11 Segment-Not-Present #NP Segment register loads
12 Stack #SS SS register loads and stack references
13 General-Protection #GP Memory accesses and protection checks
14 Page-Fault #PF Memory accesses when paging enabled
15 Reserved 
16 x87 Floating-Point Exception-Pending #MF x87 floating-point instructions
17 Alignment-Check #AC Misaligned memory accesses
18 Machine-Check #MC Model specific
19 SIMD Floating-Point #XF SSE floating-point instructions
20–27 Reserved
28 Hypervisor Injection Exception #HV Event injection
29 VMM Communication Exception #VC Virtualization event
30 Security Exception #SX Security-sensitive event in host
31 Reserved 
0–255 External Interrupts (Maskable)
0–255 Software Interrupts
*/

#include "descriptors.h"

void interrupt_handler(uint64_t error, uint64_t interrupt_n, uint64_t rflags);

/*
interrupt0()
interrupt1()
interrupt2()
interrupt3()
interrupt4()
interrupt5()
interrupt6()
interrupt7()
interrupt8()
interrupt9()
interrupt10()
interrupt11()
interrupt12()
interrupt13()
interrupt14()
interrupt15()
interrupt16()
interrupt17()
interrupt18()
interrupt19()
interrupt20()
interrupt21()
interrupt22()
interrupt23()
interrupt24()
interrupt25()
interrupt26()
interrupt27()
interrupt28()
interrupt29()
interrupt30()
interrupt31()
*/

// system interrupts
extern void interrupt0();
extern void interrupt1();
extern void interrupt2();
extern void interrupt3();
extern void interrupt4();
extern void interrupt5();
extern void interrupt6();
extern void interrupt7();
extern void interrupt8();
extern void interrupt9();
extern void interrupt10();
extern void interrupt11();
extern void interrupt12();
extern void interrupt13();
extern void interrupt14();
extern void interrupt15();
extern void interrupt16();
extern void interrupt17();
extern void interrupt18();
extern void interrupt19();
extern void interrupt20();
extern void interrupt21();
extern void interrupt22();
extern void interrupt23();
extern void interrupt24();
extern void interrupt25();
extern void interrupt26();
extern void interrupt27();
extern void interrupt28();
extern void interrupt29();
extern void interrupt30();
extern void interrupt31();
