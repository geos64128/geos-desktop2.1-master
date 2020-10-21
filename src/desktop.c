#include <geos.h>
#include <stdlib.h>
#include <PeekPoke.h>
#include <errno.h>
#include "desktop.h"
#include "desktop-res.h"
#include "desktop-icons.h"


struct window winClockFrame = {0, 15, 221, SC_PIX_WIDTH-1};
struct window winClockBackground = {1, 14, 222, SC_PIX_WIDTH-2};
struct window winPadFrame = {19, 146, 8, 263};
struct window winPadBackground = {20,145,9,262};
unsigned char *mydate = "01/01/00  00:00 AM";
void_func oldVector;
struct filehandle *curFileHandle;

struct icontab myicontab;

void NewVectorHandler(void) {
        // update time
        
        
        oldVector();
}

void hook_into_system(void) {
        oldVector = intTopVector;
        intTopVector = NewVectorHandler;
}

void remove_hook(void) {
        intTopVector = oldVector;
}

void initClock()
{
    InitDrawWindow(&winClockFrame);
    FrameRectangle(255);

    SetPattern(0);
    InitDrawWindow(&winClockBackground);
    Rectangle();

    UseSystemFont();
    PutString(mydate, 10, 225);
    
}

void drawPad()
{
    
    struct window pagingLine = {129,142,8,23};

    // main frame
    InitDrawWindow(&winPadFrame);
    FrameRectangle(255);

    SetPattern(0);
    InitDrawWindow(&winPadBackground);
    Rectangle();

    // header lines
    HorizontalLine(255, 21, 8, 263);
    HorizontalLine(255, 23, 8, 263);
    HorizontalLine(255, 25, 8, 263);
    HorizontalLine(255, 27, 8, 263);
    HorizontalLine(255, 29, 8, 263);
    HorizontalLine(255, 31, 8, 263);
    
    HorizontalLine(255, 42, 8, 263);
    
    HorizontalLine(255, 142, 23, 263);
    HorizontalLine(255, 144, 8, 263);

    // page tab lines
    HorizontalLine(255, 129, 8, 23);
    VerticalLine(255,129, 142, 23);
    DrawLine(DRAW_DRAW, &pagingLine);

}

void iconHandler() 
{
    remove_hook();
    ToBASIC();
}

char *getDriveIcon(unsigned char id)
{
    switch (id)
    {
        case DRV_NULL: 
            return 0;
        case DRV_1541:
            return drvIcon1541;
        case DRV_1571:
            return drvIcon1571;
        case DRV_1581:
            return drvIcon1581;
        case (128 + DRV_1541):
            return drvIconREU;
        case (128 + DRV_1571):
            return drvIconREU;
        case (128 + DRV_1581):
            return drvIconREU;
        default:
            return drvIcon1541;
            
    }
}

void initIconTable() 
{
    myicontab.number = 15;
    myicontab.mousepos.x = 0;
    myicontab.mousepos.y = 0;

    
    myicontab.tab[0].pic_ptr = 0;
    myicontab.tab[0].x = 35; // * 8 
    myicontab.tab[0].y = 22;
    myicontab.tab[0].width = 3; // * 8
    myicontab.tab[0].heigth = 21;
    myicontab.tab[0].proc_ptr = (unsigned) iconHandler;

    myicontab.tab[1].pic_ptr = 0;
    myicontab.tab[1].x = 35; // * 8 
    myicontab.tab[1].y = 54;
    myicontab.tab[1].width = 3; // * 8 
    myicontab.tab[1].heigth = 21;
    myicontab.tab[1].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[2].pic_ptr = 0;
    myicontab.tab[2].x = 35; // * 8 
    myicontab.tab[2].y = 86;
    myicontab.tab[2].width = 3; // * 8 
    myicontab.tab[2].heigth = 21;
    myicontab.tab[2].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[3].pic_ptr = 0;
    myicontab.tab[3].x = 35; // * 8 
    myicontab.tab[3].y = 118;
    myicontab.tab[3].width = 3; // * 8 
    myicontab.tab[3].heigth = 21;
    myicontab.tab[3].proc_ptr = (unsigned)  iconHandler;

    // trash
    myicontab.tab[4].pic_ptr = trashIcon;
    myicontab.tab[4].x = 35; // * 8 
    myicontab.tab[4].y = 154;
    myicontab.tab[4].width = 3; // * 8 
    myicontab.tab[4].heigth = 21;
    myicontab.tab[4].proc_ptr = (unsigned)  iconHandler;

    // printer
    myicontab.tab[5].pic_ptr = printerIcon;
    myicontab.tab[5].x = 3; // * 8 
    myicontab.tab[5].y = 154;
    myicontab.tab[5].width = 3; // * 8 
    myicontab.tab[5].heigth = 21;
    myicontab.tab[5].proc_ptr = (unsigned)  iconHandler;

    // close disk
    myicontab.tab[6].pic_ptr = closeIcon;
    myicontab.tab[6].x = 30; // * 8 
    myicontab.tab[6].y = 20;
    myicontab.tab[6].width = 2; // * 8 
    myicontab.tab[6].heigth = 11;
    myicontab.tab[6].proc_ptr = (unsigned)  iconHandler;

    // file icons
    myicontab.tab[7].pic_ptr = 0;
    myicontab.tab[7].x = 5; // * 8 
    myicontab.tab[7].y = 50;
    myicontab.tab[7].width = 3; // * 8 
    myicontab.tab[7].heigth = 21;
    myicontab.tab[7].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[8].pic_ptr = 0;
    myicontab.tab[8].x = 12; // * 8 
    myicontab.tab[8].y = 50;
    myicontab.tab[8].width = 3; // * 8 
    myicontab.tab[8].heigth = 21;
    myicontab.tab[8].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[9].pic_ptr = 0;
    myicontab.tab[9].x = 19; // * 8 
    myicontab.tab[9].y = 50;
    myicontab.tab[9].width = 3; // * 8 
    myicontab.tab[9].heigth = 21;
    myicontab.tab[9].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[10].pic_ptr = 0;
    myicontab.tab[10].x = 26; // * 8 
    myicontab.tab[10].y = 50;
    myicontab.tab[10].width = 3; // * 8 
    myicontab.tab[10].heigth = 21;
    myicontab.tab[10].proc_ptr = (unsigned)  iconHandler;
//
    myicontab.tab[11].pic_ptr = 0;
    myicontab.tab[11].x = 5; // * 8 
    myicontab.tab[11].y = 95;
    myicontab.tab[11].width = 3; // * 8 
    myicontab.tab[11].heigth = 21;
    myicontab.tab[11].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[12].pic_ptr = 0;
    myicontab.tab[12].x = 12; // * 8 
    myicontab.tab[12].y = 95;
    myicontab.tab[12].width = 3; // * 8 
    myicontab.tab[12].heigth = 21;
    myicontab.tab[12].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[13].pic_ptr = 0;
    myicontab.tab[13].x = 19; // * 8 
    myicontab.tab[13].y = 95;
    myicontab.tab[13].width = 3; // * 8 
    myicontab.tab[13].heigth = 21;
    myicontab.tab[13].proc_ptr = (unsigned)  iconHandler;

    myicontab.tab[14].pic_ptr = 0;
    myicontab.tab[14].x = 26; // * 8 
    myicontab.tab[14].y = 95;
    myicontab.tab[14].width = 3; // * 8 
    myicontab.tab[14].heigth = 21;
    myicontab.tab[14].proc_ptr = (unsigned)  iconHandler;

}

void updateFileIcon(unsigned char iconnumber, char *icon_pic)
{
    myicontab.tab[7+iconnumber].pic_ptr = icon_pic;
}

void updateDriveIcons()
{
    myicontab.tab[0].pic_ptr = getDriveIcon(DRIVE_A_TYPE);
    myicontab.tab[1].pic_ptr = getDriveIcon(DRIVE_B_TYPE);
    myicontab.tab[2].pic_ptr = getDriveIcon(DRIVE_C_TYPE);
    myicontab.tab[3].pic_ptr = getDriveIcon(DRIVE_D_TYPE);
}

void updateDirectory()
{
    unsigned char z = 0;
    unsigned char ctr = 0;
    unsigned tmp = 0;
    unsigned char fnames[8][17];

    UseSystemFont();
    curFileHandle = Get1stDirEntry();

    do
    {
        if (curFileHandle->dostype != 0x00 && curFileHandle->dostype != 0x20); 
        {
            // r5 (curFileHandle) is trashed by DoIcons and PutString
            tmp = r5;   
        
            if(GetFHdrInfo(curFileHandle) == 0) 
            {
                //copy icon data
                for(z=0; z < 63; z++)
                    fileIcons[ctr][z+1] = fileHeader.icon_pic[z];

                // copy and clean up filename
                for(z=0; z<17; z++)
                {
                    if(curFileHandle->name[z] == 0xa0)
                        break;
                    fnames[ctr][z] = curFileHandle->name[z];
                };
                fnames[ctr][z] = 0;             
            }
            
            r5 = tmp;
            curFileHandle = GetNxtDirEntry();
        }
        
        ctr++;

    } while (ctr < 8);

    // Display icons and filenames
    for(ctr=0; ctr<8;ctr++)
    {
        updateFileIcon(ctr, fileIcons[ctr]);

        if(ctr < 4)
            PutString(fnames[ctr], 80, 40 + (ctr*50));
        else
            PutString(fnames[ctr], 128, 40 + ((ctr-4)*50));  
    }
}

void updatePadHeader()
{
    char *diskName = (char *)(0x841e);
    unsigned blksfree = 0;
    
    GetDirHead();
    blksfree = CalcBlksFree();
    
    UseSystemFont();

    PutDecimal(SET_LEFTJUST + SET_SURPRESS, curPage,  135, 135);
    PutString(diskName, 27, 100);
    PutString(hdr1,39, 26);
    PutString(hdr2,39, 64);
    PutString(hdr3,39, 125);
    
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, blksfree, 39, 180);
    PutString(hdr4,39, 206);
}

void main(void)
{
    initClock();
    initIconTable();
    DoMenu(&mainMenu);

    drawPad();
    updatePadHeader();
    
    updateDriveIcons();
    DoIcons(&myicontab);

    updateDirectory();
    DoIcons(&myicontab);

    updateDriveIcons();
    DoIcons(&myicontab);
    
    hook_into_system();
    MainLoop();
};

#include "desktop-menu.c"


