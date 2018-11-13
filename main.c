/*
    lavagimp, autotype random quotes (gimps) by pressing hotkeys
	
    Copyright (C) 2018  lavajoe <joe89gunnar@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <windows.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include <stdbool.h>

#include <libconfig.h>
#include "lavagimp.h"

char gimp[999999][512];
int gimpN = 0;

int* allocate_mem(int*** arr, int n, int m)
{
  *arr = (int**)malloc(n * sizeof(int*));
  int *arr_data = malloc( n * m * sizeof(int));
  for(int i=0; i<n; i++)
     (*arr)[i] = arr_data + i * m ;
  return arr_data; //free point
}

void deallocate_mem(int*** arr, int* arr_data){
    free(arr_data);
    free(*arr);
}

int fileExists(char *filename) {
	if(access(filename, F_OK) != -1) {
    	return 1;
	} else {
	    return 0;
	}
}

void BailOut(char *msg)
{
	fprintf(stderr, "Exiting: %s\n", msg);
	exit(1);
}

int main() {

	printf("lavagimp version 2.0.0-a3 (development version). Copyright (C) 2018 lavajoe\nThis program comes with ABSOLUTELY NO WARRANTY; for details see the 'LICENSE' file.\nThis is free software, and you are welcome to redistribute it under certain conditions;\nsee the 'LICENSE' file for details.\n\n");
	
	//Load config file
	config_t cfg;
	
	const char *gimpfilecfg;
	config_init(&cfg);
	const char *modekey2;
	const char *insertkey2;
	const char *deletegimp2;
	const char *beforegimp;
	const char *aftergimp;
	bool pbg = false;
	bool pag = false;
	int putenter;
	int sleeptime;
	if (config_read_file(&cfg, "config/config.cfg") == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	

	if (config_lookup_string(&cfg, "gimpfile", &gimpfilecfg) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_string(&cfg, "insertgimp", &insertkey2) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_string(&cfg, "changemode", &modekey2) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_string(&cfg, "deletegimp", &deletegimp2) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_string(&cfg, "beforegimp", &beforegimp) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_string(&cfg, "aftergimp", &aftergimp) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_bool(&cfg, "putenter", &putenter) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}
	if (config_lookup_int(&cfg, "sleeptime", &sleeptime) == CONFIG_FALSE) {
		printf("Error parsing config file: %s.\n",config_error_text(&cfg));
	}

	if (strlen(beforegimp) < 1) {
		pbg = false;
	} else {
		pbg = true;
	}
	if (strlen(aftergimp) < 1) {
		pag = false;
	} else {
		pag = true;
	}
		
	//printf("beforegimp: %s.\naftergimp: %s.\n",beforegimp,aftergimp);
	//UINT modekey = modekey2;
	char gimpfile[64];
	strcpy(gimpfile, gimpfilecfg);

	char insertgimp3[64];
	strcpy(insertgimp3, insertkey2);

	char modekey3[64];
	strcpy(modekey3, modekey2);


	char deletegimp3[64];
	strcpy(deletegimp3, deletegimp2);

	UINT modekey = 69696969;
	UINT insertkey = 69696969;
	UINT deletegimp = 69696969;

        insertkey = findKey(insertgimp3);
	if (insertkey == 69696969) {
	  	printf("Invalid hotkey: %s\n",insertgimp3);
	  	getchar();
	  	exit(1);
	}

        modekey = findKey(modekey3);
	if (modekey == 69696969) {
	  	printf("Invalid hotkey: %s\n",modekey3);
	  	getchar();
	  	exit(1);
	}

        deletegimp = findKey(deletegimp3);
	if (deletegimp == 69696969) {
	  	printf("Invalid hotkey: %s\n",deletegimp3);
	  	getchar();
	  	exit(1);
	}

	printf("Loaded gimplist from: %s.\n",gimpfile);
	
	FILE *GIMPS;
	if (fileExists(gimpfile)) {
		char gimpBuffer[512];
		gimpN = 1;
		GIMPS = fopen(gimpfile, "r");
		char ch;
		while(!feof(GIMPS)) {
  			ch = fgetc(GIMPS);
  			if(ch == '\n') {
    			gimpN++;
  			}
  		}

  		//fclose(GIMPS);
	  	GIMPS = fopen(gimpfile, "r");
	  	int i = 1;
	  	for (i = 1; i <= gimpN; i++) {
			fgets(gimp[i], sizeof(gimp[i]), GIMPS);
			memset(gimp[i]+strlen(gimp[i])-1, '\0', 1);
		}
	} else {
		printf("gimps.txt not found.\n");
		getchar();
		exit(1);
		gimpN = -1;
	}

	if (gimpN < 1) {
		printf("gimps.txt is empty!");
		getchar();
		exit(1);
	}

	//RegisterHotKey(NULL, 100, MOD_ALT | MOD_CONTROL, 'S');

	UINT hk = NULL;
    
	if (RegisterHotKey(NULL, 1, hk, insertkey) == 0) {
		printf("Failed to register insert hotkey! (Maybe you have another instance of lavagimp open)\n");
		getchar();
		exit(1);
	}
	if (RegisterHotKey(NULL, 2, hk, modekey) == 0) {
		printf("Failed to register modechange hotkey! (Maybe you have another instance of lavagimp open)\n");
		getchar();
		exit(1);
	}
	if (RegisterHotKey(NULL, 3, hk, deletegimp) == 0) {
		printf("Failed to register insert hotkey! (Maybe you have another instance of lavagimp open)\n");
		getchar();
		exit(1);
	}
	RegisterHotKey(NULL, 4, hk, 0xA5);
	

	MSG msg;
	srand(time(NULL));
	HKL kl = LoadKeyboardLayout("US", KLF_ACTIVATE);

	int delLength = 0;
	int gimpLog = 1;
	int mode = 1;
	/*char htest;
        printf("enter: ");
	scanf("%c", &htest);
	//short vret = VkKeyScanEx('I', kl);
	printf("\ngot '%hd'",vret);*/
	/*
	HANDLE h;
   
  if (!OpenClipboard(NULL))
    BailOut("Can't open clipboard");
   
  h = GetClipboardData(CF_TEXT);
 
  printf("%s\n", (char *)h);
 
  CloseClipboard();*/

	while (GetMessageA(&msg, NULL, 0, 0) != 0) {//main loop
		if (msg.wParam == 3) {//delete gimp (end key)
			int i = 0;
			for (i = 0; i < delLength + 1; i++) {
				keybd_event(0x08,0,0,0);
				keybd_event(0x08,0,KEYEVENTF_KEYUP,0);
			}
		}
		if (msg.wParam == 2) {//mode switch (home key)
			mode++;
			if (mode == 5) {
				mode = 1;
			}
			switch (mode) {
				case 1:
					printf("Switched to: normal random mode (1)\n");
					break;
				case 2:
					printf("Switched to: slow type mode (2)\n");
					break;
				case 3:
					printf("Switched to: top to bottom mode (3)\n");
					break;
				case 4:
					printf("Switched to: Gimp collection mode (4)\n");
					break;
			}
		}
		if (msg.wParam == 1) {//action (insert key)
			if (mode == 4) {//gimp collection mode
				
				HANDLE h;
   
				if (!OpenClipboard(NULL)) {
					BailOut("Can't open clipboard");
				}
				h = GetClipboardData(CF_TEXT);
				printf("Putting gimp \"%s\" into gimps.txt.\n", (char *)h);
				CloseClipboard();
				
				/*GIMPS = fopen("gimps.txt", "w");
				fprintf(GIMPS, "%s",(char*)h);
				fclose(GIMPS);
				FILE *GIMPS2;
				int gimpN2;
				*/
				FILE *GIMPS2;
				//int gimpN2;
				GIMPS2 = fopen(gimpfile, "a+");
				//char gimp2[999999][512];
				
				if (!fileExists(gimpfile)) {	
					printf("gimps.txt not found!\n");
					exit(1);
				}
				
				fprintf(GIMPS2, "\n%s", (char*)h);
				fclose(GIMPS2);
				
			}
			if (mode == 3) {//start to bottom mode
				 int i = 0;
				 char buf[512];
				 memset(buf, 0, 512);
				 if (pbg) {
					strcat(buf, beforegimp);
				 }
				 strcat(buf, gimp[gimpLog]);
				 if (pag) {
					strcat(buf, aftergimp);
				 }
				 delLength = strlen(buf);
				 for (i = 0; i < strlen(buf); i++) {
					if (buf[i] == '?' || buf[i] == '>' || buf[i] == ':' || buf[i] == '!' || buf[i] == '@' || buf[i] == '#' || buf[i] == '$' || buf[i] == '%' || buf[i] == '^' || buf[i] == '&' || buf[i] == '*' || buf[i] == '(' || buf[i] == ')' || buf[i] == '_' || buf[i] == '+' || buf[i] == '"' || buf[i] == '<' || buf[i] == '|' || buf[i] == '~' || isupper(buf[i]) != 0) {
						keybd_event(0x10,0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
						keybd_event(0x10,0,KEYEVENTF_KEYUP,0);
					} else {
						keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
					}
				 }
				 if (putenter) {
					 keybd_event(0x0D,0,0,0);
				 }
				 
				if (gimpLog == gimpN) { gimpLog = 0; }
				gimpLog++;
			}
			if (mode == 2) { //slow type
				 int randomnumber = rand() % (gimpN - 1) + 1;
				 int i = 0;
				 char buf[512];
				 memset(buf, 0, 512);
				 if (pbg) {
					strcat(buf, beforegimp);
				 }
				 strcat(buf, gimp[randomnumber]);
				 if (pag) {
					strcat(buf, aftergimp);
				 }
				 delLength = strlen(buf);
				 for (i = 0; i < strlen(buf); i++) {
					if (buf[i] == '?' || buf[i] == '>' || buf[i] == ':' || buf[i] == '!' || buf[i] == '@' || buf[i] == '#' || buf[i] == '$' || buf[i] == '%' || buf[i] == '^' || buf[i] == '&' || buf[i] == '*' || buf[i] == '(' || buf[i] == ')' || buf[i] == '_' || buf[i] == '+' || buf[i] == '"' || buf[i] == '<' || buf[i] == '|' || buf[i] == '~' || isupper(buf[i]) != 0) {
						keybd_event(0x10,0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
						keybd_event(0x10,0,KEYEVENTF_KEYUP,0);
					} else {
						keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
						keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
					}
					Sleep(sleeptime); //60 before, 90 after, 75 now?
				 }
				 if (putenter) {
					 keybd_event(0x0D,0,0,0);
				 }
			}
			if (mode == 1) {//regular
				int randomnumber = rand() % (gimpN - 1) + 1;
             			int i = 0;
             			char buf[512];
				memset(buf, 0, 512);
				if (pbg) {
					strcat(buf, beforegimp);
				}
				//strncpy(buf, gimp[randomnumber], strlen(gimp[randomnumber]));
				strcat(buf, gimp[randomnumber]);
				if (pag) {
					strcat(buf, aftergimp);
				}
             			delLength = strlen(buf);
             			for (i = 0; i < strlen(buf); i++) {
             				if (buf[i] == '?' || buf[i] == '>' || buf[i] == ':' || buf[i] == '!' || buf[i] == '@' || buf[i] == '#' || buf[i] == '$' || buf[i] == '%' || buf[i] == '^' || buf[i] == '&' || buf[i] == '*' || buf[i] == '(' || buf[i] == ')' || buf[i] == '_' || buf[i] == '+' || buf[i] == '"' || buf[i] == '<' || buf[i] == '|' || buf[i] == '~' || isupper(buf[i]) != 0) {
             					keybd_event(0x10,0,0,0);
             					keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
             					keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
             					keybd_event(0x10,0,KEYEVENTF_KEYUP,0);
             				} else {
             					keybd_event(VkKeyScanEx(buf[i], kl),0,0,0);
             					keybd_event(VkKeyScanEx(buf[i], kl),0,KEYEVENTF_KEYUP,0);
             				}
              			}
				if (putenter) {
					 keybd_event(0x0D,0,0,0);
				}
	         		//keybd_event(VkKeyScanEx(' ', kl),0,0,0); //print space at the end of gimp
             			//keybd_event(VkKeyScanEx(' ', kl),0,KEYEVENTF_KEYUP,0);

			}
		}

		//delLength = strlen(gimp[randomnumber]);
	}

	return 0;
} 
