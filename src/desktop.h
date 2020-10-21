#ifndef _desktop_
#define _desktop_

#define DRIVE_A_TYPE  PEEK(0x848e)
#define DRIVE_B_TYPE  PEEK(0x848f)
#define DRIVE_C_TYPE  PEEK(0x8490)
#define DRIVE_D_TYPE  PEEK(0x8491)

char *hdr1 = " files,";
char *hdr2 = " selected";
char *hdr3 = " Kbytes used";
char *hdr4 = " Kbytes free";
unsigned char curPage = 1;

#endif