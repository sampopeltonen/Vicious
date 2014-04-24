
#ifndef VICILIB_H_
#define VICILIB_H_

typedef unsigned char byte;
typedef unsigned word;

#define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
#define POKEW(addr,val)    (*(unsigned*) (addr) = (val))
#define PEEK(addr)         (*(unsigned char*) (addr))
#define PEEKW(addr)        (*(unsigned*) (addr))

// SID is visible in address     BF00
#define SID                    0xbf00


// CIA is visible in address     BF80
#define CIA_PORT_A             0xbf80
#define CIA_PORT_B             0xbf81
#define CIA_PORT_A_DATA_DIR    0xbf82
#define CIA_PORT_B_DATA_DIR    0xbf83
#define CIA_TIMER_A_VALUE      0xbf84  // word
#define CIA_TIMER_B_VALUE      0xbf86  // word
#define CIA_TOD_DS             0xbf88
#define CIA_TOD_S              0xbf89
#define CIA_TOD_MIN            0xbf8a
#define CIA_TOD_HOUR           0xbf8b
#define CIA_SERIAL_SHIFT_REG   0xbf8c
#define CIA_IRQ_CTRL           0xbf8d
#define CIA_TIMER_A_CTRL       0xbf8e
#define CIA_TIMER_B_CTRL       0xbf8f


// Only relevant bits defined here

#define BIT_CIA_TIMER_START                         0x1
#define BIT_CIA_TIMER_UNDERFLOW_STOP                0x2
#define BIT_CIA_TIMER_LOAD_VALUE                    0x10
#define BIT_CIA_TIMER_B_COUNT_UNDERFLOWS_OF_TIMER_A 0x20

#define BIT_CIA_IRQ_CTRL_TIMER_A_UNDERFLOW          0x1
#define BIT_CIA_IRQ_CTRL_TIMER_B_UNDERFLOW          0x2
#define BIT_CIA_IRQ_CTRL_FILL_BIT                   0x80  // set bits are set to this value

// These are implemented in viciliba.s

extern void initVicilib();

extern void __fastcall__ putchar(byte c);

extern void __fastcall__ printb(byte c);
extern void irq;

extern void __fastcall__ initSIDTune(word initAddress, word playAddress);


//extern unsigned char __fastcall__ copyshort(unsigned char len, void *src, void *dst);


// Implemented in vicilibc.c

void prints(byte* string);

void printsl(byte* string, byte len);

void printw(word w);

//void setIRQHandlerAddress(word address);

void fixSIDTune(word address, word len);

void stopPlaying();

byte memcmp(byte* a1, byte* a2, byte len);

#endif

