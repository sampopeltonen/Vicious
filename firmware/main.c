#include <apple1.h>
#include "vicilib.h"
#include "sidfile.h"
#include "cffa1.h"

//extern word Destination;

byte const CFFA_MODULE_FILENAME[] = { 12, 'V', 'I', 'C', 'I', 'O', 'U', 'S', 'C', 'F', 'F', 'A', '1' };

int main (void)
{
	byte keybInput = 0;
	word fileLength;
	initVicilib();

	// is CFFA module loaded?
	
	// if not, is CFFA card present?
	
	// if it is, try to load VICIOUSCFFA1
	POKEW(CFFA1_DESTINATION, 0x7000);
	POKEW(CFFA1_FILENAME, (word)&CFFA_MODULE_FILENAME[0]);
	if(callCFFA1API(CFFA1_READFILE)!=0) {
		prints("\rERROR LOADING CFFA1 MODULE\r");
	}

	while(keybInput!='Q') {	
		prints("\rVICIOUS> ");
		keybInput = readkey() - 0x80;
		switch (keybInput) {
		case 'P':
			playSidFile(0x1000, 0x2000); // file length is just a guess, it's not known
			break;
		case 'S':
			prints("\rSTOP PLAYING\r");
			stopPlaying();
			break;
		case 'C':
			stopPlaying();
			gotoCFFA1();
			break;
		case 'L':
			stopPlaying();
			if((fileLength = loadFile(0x1000))!=0) {
				playSidFile(0x1000, fileLength);
			}
			break;
		case 'Q':
			prints("\rQUIT\r");
			break;
		default:
			prints("\r\r VICIOUS MENU (0.9)\r ------------------\r P - PLAY SID TUNE AT $1000");
			prints("\r S - STOP PLAYING\r C - CFFA1\r L - LOAD & PLAY SID TUNE\r Q - QUIT\r");
			break;
		}

	}
	return 1;
}
