#include "sidfile.h"


void _memcpy(byte* to, word from, word len) {
	word i=0;
	while(i<len) {
		to[i] = PEEK(from+i);
		i++;
	}
}

void _strcpy(byte* to, word from, word len) {
	word i=0;
	while(i<len) {
		byte c = PEEK(from+i);
		if(c>96) c-=32;
		to[i] = c;
		i++;
	}
	to[len-1] = '\0';
}

word _readBigEndianW(word address) {
	word ret = PEEK(address)<<8;
	return(ret + PEEK(address+1));
}

byte readSidHeader(word address, SidHeader1* header1) {
	header1->location = address;
	_memcpy((byte*)header1->magicId, address, 4);
	if(header1->magicId[0]!='P' ||
		header1->magicId[1]!='S' ||
		header1->magicId[2]!='I' ||
		header1->magicId[3]!='D') return 0;
	header1->version     = _readBigEndianW(address+4);
	header1->dataOffset  = _readBigEndianW(address+6);
	header1->loadAddress = _readBigEndianW(address+8);
	header1->initAddress = _readBigEndianW(address+10);
	header1->playAddress = _readBigEndianW(address+12);
	header1->songs       = _readBigEndianW(address+14);
	header1->startSong   = _readBigEndianW(address+16);
	_memcpy((byte*)header1->speed,   address+18, 4);
	_strcpy((byte*)header1->title,   address+0x16, 32);
	_strcpy((byte*)header1->author,  address+0x36, 32);
	_strcpy((byte*)header1->release, address+0x56, 32);

	// TODO: read v2 of the header	
	return 1;
}


word moveSIDCodeToPlace(SidHeader1* header1, word dataLen) {
	word loadAddress;
	word dataAddressFrom = header1->location + header1->dataOffset;
	if(header1->loadAddress!=0) {
		loadAddress = header1->loadAddress;
	}
	else {
		loadAddress = PEEKW(dataAddressFrom);
		dataAddressFrom += 2;
	}
	_memcpy((byte*)loadAddress, dataAddressFrom, dataLen);
	return loadAddress;
}


void playSidFile(word address, word fileSize) {
	SidHeader1 header1;

	word loadAddress;

	prints("\r\rVICIOUS SID PLAYER\r");

	if(readSidHeader(address, &header1)) {
		//prints("\rSID TYPE: ");   printsl(header1.magicId, 4);
		//prints(" V.");            printw(header1.version);
		prints("\rTITLE:   ");    prints(header1.title);
		prints("\rAUTHOR:  ");    prints(header1.author);
		prints("\rRELEASE: ");    prints(header1.release);
		prints("\rSONGS: $");      printw(header1.songs);
		prints(" DEFAULT: $");     printw(header1.startSong);
		//prints("\rDATAOFFSET: "); printw(header1.dataOffset);
		//prints("\rLOAD ADDRESS: "); printw(header1.loadAddress);
		prints("\rUSING FILE SIZE: $"); printw(fileSize);
		prints("\rINIT ADDRESS:    $"); printw(header1.initAddress);
		prints("\rPLAY ADDRESS:    $"); printw(header1.playAddress);
	
		loadAddress = moveSIDCodeToPlace(&header1, fileSize);
	
		prints("\rLOAD ADDRESS:    $"); printw(loadAddress);
		prints("\r");
	
		fixSIDTune(loadAddress, fileSize);
	
		initSIDTune(header1.initAddress, header1.playAddress);
	
	
		POKEW(CIA_TIMER_A_VALUE, 0x4e20); // is this about 50Hz
		POKE(CIA_IRQ_CTRL, BIT_CIA_IRQ_CTRL_TIMER_A_UNDERFLOW+BIT_CIA_IRQ_CTRL_FILL_BIT);
		
		prints("START PLAYING...\r");
		// start CIA timer A
		POKE(CIA_TIMER_A_CTRL, BIT_CIA_TIMER_LOAD_VALUE+BIT_CIA_TIMER_START);
	}
	else {  // Header not found
		prints("\rSID TUNE NOT FOUND IN ADDRESS $");
		printw(address);
		prints("\r");
	}

	//while(1) ;

}
