
#include "vicilib.h"

#define IRQ_VECTOR 0x0000  // This is where Apple-1 IRQ vector points to
//#define JMP 0x4C

const byte storeOpCodes[] = {
	0x8d,
	0x9d,
	0x99,
	0x81,
	0x91,
	0x8e,
	0x8c
}; 

void prints(unsigned char* string) {
	byte i = 0;
	byte c;
	while((c = string[i++])!='\0') {
		putchar(c);
	}	
}

void printsl(byte* string, byte len) {
	byte i=0;
	while(i<len) {
		putchar(string[i++]);
	}
}

void printw(word w) {
	byte lsb = (byte) w;
	printb((byte)(w>>8));
	printb(lsb);
}

/*
void setIRQHandlerAddress(word address) {
	POKE(IRQ_VECTOR, JMP);
	POKEW(IRQ_VECTOR+1, address);
}
*/

byte _isStoreOpCode(byte b) {
	byte i=0;
	while(i<7)
		if(storeOpCodes[i++]==b) return 1;
	return 0;
}

void fixSIDTune(word address, word len) {
	word i=0, count=0;
	prints("FIXING SID TUNE AT $");
	printw(address);
	prints("...\r");
	while(i<len) {
		if(PEEK(address+i+2)==0xd4 && 
				_isStoreOpCode(PEEK(address+i)) &&
				(PEEK(address+i+1)<0x1d))
		{
			POKE(address+i+2, 0xbf);
			//prints("  FIXED SID ADDRESS AT ");
			//printw(address+i+1);
			//prints("\r");
			++count;
		}
		++i;
	}
	prints("DONE: FIXED $");
	printw(count);
	prints(" SID ADDRESSES.\r");

}

void stopPlaying() {
	int i=0;
	POKE(CIA_TIMER_A_CTRL, 0);
	while(i<=24) {
		POKE(SID+i, 0);
		i++;
	}

}
