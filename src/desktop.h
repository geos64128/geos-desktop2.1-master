#ifndef _desktop_
#define _desktop_

#define CUR_DEVICE  PEEK(0x8489)

#define DRIVE_A_TYPE  PEEK(0x848e)
#define DRIVE_B_TYPE  PEEK(0x848f)
#define DRIVE_C_TYPE  PEEK(0x8490)
#define DRIVE_D_TYPE  PEEK(0x8491)

extern char *hdr1;
extern char *hdr2;
extern char *hdr3;
extern char *hdr4;

extern unsigned char curPage;

void initClock();
void drawPad();
void updatePadHeader();
void updateDirectory();
void changeDevice(unsigned char deviceNumber);
void updateClock();
unsigned getFileCount();


#endif