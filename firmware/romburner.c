
#include <apple1.h>

typedef unsigned char byte;
typedef unsigned word;

#define ROM_IMAGE_SIZE 3840
#define PROM 0xB000
#define ROM_IMAGE_START_ADDRESS 0x1300  // defined in linker config

#define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
#define POKEW(addr,val)    (*(unsigned*) (addr) = (val))
#define PEEK(addr)         (*(unsigned char*) (addr))
#define PEEKW(addr)        (*(unsigned*) (addr))


extern void __fastcall__ putchar(byte c);
extern void __fastcall__ printb(byte c);


//extern word _END_LOAD__[];
//extern word _END_SIZE__[];


void prints(unsigned char* string) {
	byte i = 0;
	byte c;
	while((c = string[i++])!='\0') {
		putchar(c);
	}	
}

void printw(word w) {
	byte lsb = (byte) w;
	printb((byte)(w>>8));
	printb(lsb);
}




int main(void) {
	word i=0;

	//word imageStartAddress = (word)_END_LOAD__ + (word)_END_SIZE__;
	word imageStartAddress = ROM_IMAGE_START_ADDRESS;

	prints("\r\rVICIOUS SOUND CARD FIRMWARE ROM BURNER\r");


	prints("START ADDRESS: ");
	printw(imageStartAddress);
	prints("\r");

	while(i<ROM_IMAGE_SIZE) {
		POKE(PROM+i, PEEK(imageStartAddress+i));
		putchar('*');
		i++;
	}
	prints("\rBURN FINISHED\r");
	return 1;
}
