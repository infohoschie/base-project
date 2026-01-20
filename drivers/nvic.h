// Registers from NVIC - Cortex-M0 peripheral
// These are to activate and debug Interrupts
// Details on Chapter 4.2 Nested Vectored Interrupt Controller (Page 109)

#define Interrupt_Set_Enable_00   0xE000E100 //  1 - Reset
#define Interrupt_Set_Enable_01   0xE000E104 //  2 - NMI
#define Interrupt_Set_Enable_02   0xE000E108 //  3 - Hard-Fault
#define Interrupt_Set_Enable_03   0xE000E10C //  4 - MPU / MEM-Manage

#define Interrupt_Set_Enable_04   0xE000E110 //  5 - BUS-Fault
#define Interrupt_Set_Enable_05   0xE000E114 //  6 - Usage-Fault
#define Interrupt_Set_Enable_06   0xE000E118 //  7 - Reserved
#define Interrupt_Set_Enable_07   0xE000E11C //  8 - Reserved

#define Interrupt_Set_Enable_08   0xE000E120 //  9 - Reserved
#define Interrupt_Set_Enable_09   0xE000E124 // 10 - Reserved
#define Interrupt_Set_Enable_10   0xE000E128 // 11 - SVCall
#define Interrupt_Set_Enable_11   0xE000E12C // 12 - Debug Monitor

#define Interrupt_Set_Enable_12   0xE000E130 // 13 - Reserved
#define Interrupt_Set_Enable_13   0xE000E134 // 14 - PendSV
#define Interrupt_Set_Enable_14   0xE000E138 // 15 - SysTick
#define Interrupt_Set_Enable_15   0xE000E13C // 16 - External 0

#define Interrupt_Set_Enable      0xE000E100 // [32...0] Interrupt

#define Interrupt_ICPR            0xE000E280 // Interrupt Clear-pending Register (on page 4-6)


#define Interrupt_ID2             (1 <<  2)  // Bit for User Interrupt ID: 2
#define Interrupt_ID8             (1 <<  8)  // Bit for User Interrupt ID: 8
#define Interrupt_ID9             (1 <<  9)  // Bit for User Interrupt ID: 9
#define Interrupt_ID10            (1 << 10)  // Bit for User Interrupt ID:10


// From System Control Block:
// Useful for showing States and Pending Status

#define ICSR                      0xE000ED04  // Interrupt Control and State Register
