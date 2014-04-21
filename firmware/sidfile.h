
#ifndef SIDFILE_H_
#define SIDFILE_H_

#include "vicilib.h"

#define SID_HEADER1_LEN 0x76

#define SID 0xbf00

typedef struct SidHeader1 {
	word location;
	byte magicId[4];
	word version;
	word dataOffset;
	word loadAddress;
	word initAddress;
	word playAddress;
	word songs;
	word startSong;
	byte speed[4];
	byte title[32];
	byte author[32];
	byte release[32];
} SidHeader1;


void playSidFile(word address, word fileSize);

/* FALSE if header not found */
byte readSidHeader(word address, SidHeader1* header);

word moveSIDCodeToPlace(SidHeader1* header1, word dataLen);

void _strcpy(byte* to, word from, word len);

#endif
