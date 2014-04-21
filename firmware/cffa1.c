
#include <apple1.h>
#include "cffa1.h"
#include "sidfile.h"

#define FILE_LIST_LEN 15

#define PRODOS_FILESIZE_OFFSET 0x15

#define CFFA1_OPENDIR 0x10
#define CFFA1_READDIR 0x12
#define CFFA1_READFILE 0x22

#define CFFA1_DESTINATION 0x0
#define CFFA1_FILENAME 0x2
#define CFFA1_FILESIZE 0x9
#define CFFA1_ENTRYPTR 0xB

#define CFFA1_E_FILENOTFOUND 0x46

byte fileNames[FILE_LIST_LEN][1+16+2];


word loadFile(word destination) {
	byte i;
	byte l;
	byte ret;
	byte keybInput = 0;
	byte cont=1;
	callCFFA1API(CFFA1_OPENDIR);
	putchar('\r');
	while(cont) {
		i=0;
		while(i<FILE_LIST_LEN) {
			ret = callCFFA1API(CFFA1_READDIR);
			if(ret!=0) {
				cont=0;
				if(ret!=CFFA1_E_FILENOTFOUND)
					printb(ret);
				prints("\r\rQUIT");
				break;

			}
			_strcpy(&fileNames[i][1], PEEKW(CFFA1_ENTRYPTR)+1, 16);
			prints("\r");
			putchar(i+0x41);
			prints(") ");
			prints(&fileNames[i][1]);
			//prints(" ");
			//printw(PEEKW(PEEKW(CFFA1_ENTRYPTR)+PRODOS_FILESIZE_OFFSET));
			POKEW((word)&fileNames[i++][17], PEEKW(PEEKW(CFFA1_ENTRYPTR)+PRODOS_FILESIZE_OFFSET));

		}
		if(i==FILE_LIST_LEN) prints("\r\rCONTINUE");
		prints(" OR SELECT? ");
		keybInput = readkey() - 0x80;
		prints("\r");
		if(keybInput=='Q') break;
		if(keybInput>='A' && keybInput<=(i+0x40)) {
			i = keybInput-0x41;
			prints("\rLOADING ");
			prints(&fileNames[i][1]);
			prints("\r\r");
			
			l=0;
			while(1){
				if(fileNames[i][1+l]==0) {
					fileNames[i][0] = l;
					//printb(l);
					break;
				}
				l++;
			}

			POKEW(CFFA1_DESTINATION, destination);
			POKEW(CFFA1_FILENAME, (word)&fileNames[i][0]);
			//prints("\rFILENAME ADDR: ");
			//printw((word)&fileNames[i][0]);
			ret = callCFFA1API(CFFA1_READFILE);
			if(ret!=0) {
				prints("\rLOAD ERROR: ");
				printb(ret);
			}
			return PEEKW((word)&fileNames[i][17]);
			break;
		}
	}
	return 0;
}

