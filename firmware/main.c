#include <apple1.h>
#include "vicilib.h"
#include "sidfile.h"
#include "cffa1.h"

//extern word Destination;

int main (void)
{
	byte keybInput = 0;
	initVicilib();
	while(keybInput!='Q') {	
		prints("\rVICIOUS> ");
		keybInput = readkey() - 0x80;
		switch (keybInput) {
		case 'P':
			playSidFile(0x1000, 0x2000);
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
			playSidFile(0x1000, loadFile(0x1000));
			break;
		case 'Q':
			prints("\rQUIT\r");
			break;
		default:
			prints("\r\r VICIOUS MENU (0.9)\r ------------------");
			prints("\r P - PLAY SID TUNE");
			prints("\r S - STOP PLAYING");
			prints("\r C - CFFA1");
			prints("\r L - LOAD & PLAY SID TUNE");
			prints("\r Q - QUIT\r");
			break;
		}

	}
	return 1;
}
