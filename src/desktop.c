#include <geos.h>
#include <stdlib.h>
#include <PeekPoke.h>
#include <errno.h>
#include "desktop.h"
#include "desktop-res.h"
#include "desktop-icons.h"
#include "desktop-vectors.h"

struct window winClockFrame = {0, 15, 221, SC_PIX_WIDTH-1};
struct window winClockBackground = {1, 14, 222, SC_PIX_WIDTH-2};
struct window winPadFrame = {19, 146, 8, 263};
struct window winPadBackground = {20,145,9,262};
unsigned char *mydate = "01/01/00  00:00 AM";

struct filehandle *curFileHandle;
unsigned numFiles = 0;
unsigned numSelected = 0;
unsigned kbytesUsed = 0;
unsigned kbytesfree = 0;


void main(void)
{
    initClock();
    initIconTable();
    DoMenu(&mainMenu);

    changeDevice(PEEK(0x8489));
    
    hook_into_system();
    MainLoop();
};


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
    
    struct window pagingLine = {127,142,8,23};

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
    HorizontalLine(255, 127, 8, 23);
    VerticalLine(255,127, 142, 23);
    DrawLine(DRAW_DRAW, &pagingLine);

}

void changeDevice(unsigned char deviceNumber)
{
    char answer;
    drawPad();

    SetDevice(deviceNumber);
    OpenDisk();
    
    if(!isGEOS)
    {
        answer = DlgBoxYesNo("This is a NON-GEOS disk.", "Convert it?");

        if(answer == YES)
        {
            SetGEOSDisk();
        }
        else
        {
            DlgBoxOk("Hang on...", "Code not yet implemented");
            return;
        }
    }

    initIconTable();
    updateDriveIcons();
    DoIcons(myicontab);

    updatePadHeader();
    
    initIconTable();
    updateDriveIcons();
    updateDirectory();
    DoIcons(myicontab);

}

void updateDirectory()
{
    unsigned char z = 0;
    unsigned char ctr = 0;
    unsigned tmp = 0;
    unsigned char fnames[8][17];

    UseSystemFont();

    if(curPage == 1)
        curFileHandle = Get1stDirEntry();
    else
        curFileHandle = GetNxtDirEntry();

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
            PutString(fnames[ctr], 123, 40 + ((ctr-4)*50));  
    }
}

void updatePadHeader()
{
    char *diskName = (char *)(0x841e);
    char newDiskName[17];
    unsigned blksfree = 0;
    unsigned char z;
    
    // copy and clean up diskname
    for(z=0; z<17; z++)
    {
        if(diskName[z] == 0xa0)
            break;
        newDiskName[z] = diskName[z];
    };
    newDiskName[z] = 0; 

    GetDirHead();
    blksfree = CalcBlksFree();
    
    UseSystemFont();

    PutString(newDiskName, 27, 100);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, curPage,  135, 135);
    
    PutString(hdr1,39, 23);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numFiles,  39, 18);
    
    PutString(hdr2,39, 68);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 64);
    
    PutString(hdr3,39, 123);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesUsed,  39, 118);
    
    PutString(hdr4,39, 206);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesfree, 39, 200);
    
}

#include "desktop-vectors.c"
#include "desktop-menu.c"
#include "desktop-icons.c"



