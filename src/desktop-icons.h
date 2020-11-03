#ifndef _desktop_icons_
#define _desktop_icons_

#include <stdlib.h>
#define DRIVE_A_TYPE  PEEK(0x848e)
#define DRIVE_B_TYPE  PEEK(0x848f)
#define DRIVE_C_TYPE  PEEK(0x8490)
#define DRIVE_D_TYPE  PEEK(0x8491)

extern struct icontab *myicontab;
extern struct iconpic fileIcons[8];
extern struct window fileIconWindows[8];

extern unsigned char fileIconNames[8][17];
extern char fileIconImages[][64];
extern unsigned char fileIconSelected[8];


void initIconTable();
char *getDriveIcon(unsigned char id);
void updateDriveIcons();
void updateFileIcon(unsigned char iconnumber, char *icon_pic);
void clearAllFileIcons();
void selectFileIcon(unsigned char iconnumber);
void unselectFileIcon(unsigned char iconnumber);
void unselectAllFileIcons();
void unselectAllFileIconsExcept(unsigned char iconnumber);
void iconHandler();
void iconCloseDiskHandler();
void iconHandlerDrvA();
void iconHandlerDrvB();
void iconHandlerDrvC();
void iconHandlerDrvD();
void iconHandlerRunApp();



#endif