#include <apple1.h>
#include "vicilib.h"
#include "sidfile.h"
#include "cffa1.h"

//extern word Destination;

byte const CFFA_MODULE_FILENAME[] = { 12, 'V', 'I', 'C', 'I', 'O', 'U', 'S', 'C', 'F', 'F', 'A', '1' };

byte const CFFA_SIGNATURE[2] = {0xcf, 0xfa};

byte const MENU_STRING[] = 
			"\r\r VICIOUS MENU (0.9)\r"
			" ------------------\r"
			" P - PLAY SID TUNE AT $1000\r"
			" S - STOP PLAYING\r"
			" C - CFFA1\r"
			" L - LOAD & PLAY SID TUNE\r"
			" A - ABOUT\r"
			" Q - QUIT\r";

byte const ABOUT_STRING[] = "\r\rVICIOUS SOUND CARD FOR APPLE-1\rBY SAMPO PELTONEN\rSEARCH GITHUB.COM FOR DOCUMENTATION\r";

int main (void)
{
	byte keybInput = 0;
	word fileLength;
	initVicilib();

	// is CFFA module loaded?
	// It is loaded if address $7004 contains "VICIOUS"
	if(memcmp((byte*)0x7004, (byte*)&CFFA_MODULE_FILENAME[1], 7)) {
		//prints("\rIS LOADED\r");
	}
	else {
		//prints("\rNOT LOADED\r");

		// if not, is CFFA card present?
		if(memcmp((byte*)0xAFDC, (byte*)&CFFA_SIGNATURE[0], 2)) {
			//prints("\rLOADING CFFA MODULE\r");
			// if it is, try to load VICIOUSCFFA1
			POKEW(CFFA1_DESTINATION, 0x7000);
			POKEW(CFFA1_FILENAME, (word)&CFFA_MODULE_FILENAME[0]);
			if(callCFFA1API(CFFA1_READFILE)!=0) {
				prints("\rERROR LOADING CFFA1 MODULE\r");
			}
		}
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
		case 'A':
			prints((byte*)&ABOUT_STRING[0]);
			break;
		case 'Q':
			prints("\rQUIT\r");
			break;
		default:
			prints((byte*)&MENU_STRING[0]);
			break;
		}

	}
	return 1;
}
