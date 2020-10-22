#ifndef _desktop_
#define _desktop_

char *hdr1 = " files,";
char *hdr2 = " selected";
char *hdr3 = " Kbytes used";
char *hdr4 = " Kbytes free";
unsigned char curPage = 1;

void newVectorHandler(void);
void hook_into_system(void);
void remove_hook(void);
void initClock();
void drawPad();
void updatePadHeader();
void updateDirectory();
void switchDevice(unsigned char deviceNumber);


#endif