#ifndef _desktop_
#define _desktop_

#define CUR_DEVICE  PEEK(0x8489)

#define DRIVE_A_TYPE  PEEK(0x848e)
#define DRIVE_B_TYPE  PEEK(0x848f)
#define DRIVE_C_TYPE  PEEK(0x8490)
#define DRIVE_D_TYPE  PEEK(0x8491)

#define DRIVE_A_NAME 0x841e;
#define DRIVE_B_NAME 0x8430;
#define DRIVE_C_NAME 0x88dc;
#define DRIVE_D_NAME 0x88ee;

char *hdr1 = " files,";
char *hdr2 = " selected";
char *hdr3 = " Kbytes used";
char *hdr4 = " Kbytes free";
char currentDiskName[20];
unsigned tmpr5;

unsigned char curPage = 1;
unsigned char maxPage = 1;

void initClock();
void initInputDriver();
void initPrinterDriver();
void drawScreen();
void drawPad();
void drawFooter(unsigned char showPagingTabs);
void updatePadHeader();
void updateNumSelected();
unsigned char getPageCount();
unsigned char goPage(unsigned char pageNumber);
void updateDirectory();
void changeDevice(unsigned char deviceNumber);
void updateDiskName();
void updateClock();
unsigned getFileCount();
unsigned centerOver(unsigned x, unsigned char *text);


#endif