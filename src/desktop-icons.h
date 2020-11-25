#ifndef _desktop_icons_
#define _desktop_icons_

#define DRIVE_A_TYPE  PEEK(0x848e)
#define DRIVE_B_TYPE  PEEK(0x848f)
#define DRIVE_C_TYPE  PEEK(0x8490)
#define DRIVE_D_TYPE  PEEK(0x8491)

struct icontab *myicontab;

struct padIcon {
    unsigned char iconData[64];
    struct iconpic iconpic;
    struct window window;
    unsigned char filename[17];
    unsigned char selected;
} padIcons[8];

struct pixel location;
unsigned char dragMode = 0;
struct filehandle *loadFileHandle;

char drvIcon1541[] = {192,170,170,170,127,255,253,192,0,2,95,
255,251,223,255,250,64,0,3,199,255,194,71,255,195,199,255,194,
68,0,67,215,255,194,71,255,195,255,255,254,85,85,85,170,170,
170,85,85,85,170,170,170,85,85,85,170,170,170,85,85,85,170,170,170};

char drvIcon1571[] = {192,0,0,0,127,255,254,64,66,2,64,126,2,
64,66,2,119,255,242,119,255,242,64,66,2,64,126,2,85,66,114,
107,66,114,64,66,2,127,255,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0};

char drvIcon1581[] = {192,170,170,170,127,255,255,192,66,2,64,126,3,
192,66,2,119,255,243,247,255,242,64,66,3,192,126,2,85,66,115,235,66,
114,64,66,3,255,255,254,85,85,85,170,170,170,85,85,85,170,170,170,
85,85,85,170,170,170,85,85,85,170,170,170};

char drvIconREU[] = {192,170,170,170,127,255,255,192,0,2,64,0,3,255,
255,254,64,0,3,255,255,254,64,0,3,255,255,254,64,0,3,192,0,2,64,0,
3,192,0,2,127,255,255,192,32,0,64,44,235,213,42,138,64,44,203,192,
42,138,127,234,239,170,170,170};

char trashIcon[] = {192,171,255,234,126,33,127,228,81,3,190,
74,125,193,255,131,192,0,69,162,16,69,162,16,171,165,40,171,
149,41,17,152,197,17,136,198,17,200,194,43,88,194,43,212,198,
38,101,69,71,229,41,66,64,40,131,240,16,142,94,16,121,171,255,
234};

char printerIcon[] = {192,170,170,170,85,85,85,170,170,170,
87,255,213,171,0,106,85,188,53,171,128,42,87,28,85,174,0,255,
90,60,131,177,0,69,99,255,233,199,255,157,192,0,63,255,255,
222,128,0,93,159,192,90,128,6,85,128,0,106,255,255,213,170,
170,170};

char closeIcon[] = {150,255,255,128,1,128,1,128,1,135,225,135,
225,135,225,128,1,128,1,128,1,255,255};

char cbmFileIcon[] = {192,
0,1,252,0,2,2,255,252,1,128,0,1,129,248,1,131,248,1,135,7,193,
135,7,129,135,0,1,135,7,129,131,7,193,129,248,1,129,248,1,128,0,1,
129,130,1,130,6,1,131,138,1,130,95,1,129,130,1,128,0,1,255,255,255
};

char multiFileIcon[] = {192,
255,255,255,128,0,1,128,0,1,162,0,137,182,4,129,170,149,233,162,148,137,
162,148,137,162,116,105,128,0,1,128,0,1,143,88,1,136,9,193,142,74,33,
136,75,225,136,74,1,136,73,225,128,0,1,128,0,1,128,0,1,255,255,255,
};

void initIconTable();
char *getDriveIcon(unsigned char id);
void updateDriveIcons();
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
void iconHandlerRunApp(unsigned char iconnumber);

signed char clickPagerCheck();
signed char clickFileIconCheck();
unsigned char dblClickFileIconCheck();

void iconBeginDrag(unsigned char iconnumber);
void iconEndDrag();


#endif