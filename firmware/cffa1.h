
#ifndef CFFA1_H_
#define CFFA1_H_

#define CFFA1_DESTINATION 0x0
#define CFFA1_FILENAME 0x2

#define CFFA1_READFILE 0x22

#include "vicilib.h"

extern void gotoCFFA1();

extern byte __fastcall__ callCFFA1API(byte function);

word loadFile(word destination);


#endif
