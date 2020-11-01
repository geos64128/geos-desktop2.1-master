#include <geos.h>
#include <stdlib.h>
#include <PeekPoke.h>
#include <errno.h>
#include "desktop.h"
#include "desktop-res.h"
#include "desktop-icons.h"
#include "desktop-vectors.h"
#include "desktop-bsd6pt.h"

struct window winClockFrame = {0, 15, 221, SC_PIX_WIDTH-1};
struct window winClockBackground = {1, 14, 222, SC_PIX_WIDTH-2};
struct window winPadFrame = {19, 146, 8, 263};
struct window winPadBackground = {20,145,9,262};

struct filehandle *curFileHandle;
unsigned numFiles = 0;
unsigned numSelected = 0;
unsigned kbytesUsed = 0;
unsigned kbytesfree = 0;
unsigned char datetime[19];

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
    updateClock();
}

void updateClock()
{
    unsigned char strMonth[3];
    unsigned char strDay[3];
    unsigned char strYear[3];
    unsigned char strHour[3];
    unsigned char strMinute[3];
    unsigned char hr = 0;

    SetPattern(0);
    InitDrawWindow(&winClockBackground);
    Rectangle();
    
    hr = system_date.s_hour;
    
    if(hr > 11)
    {
       datetime[16] = 'P';
       hr = 24-hr;
    }
    else
        datetime[16] = 'A';

    if(hr == 0) 
        hr = 12;           
    
    itoa(system_date.s_month, (char *)strMonth, 10);
    itoa(system_date.s_day, (char *)strDay, 10);
    itoa(system_date.s_year, (char *)strYear, 10);
    itoa(hr, (char *)strHour, 10);
    itoa(system_date.s_minutes, (char *)strMinute, 10);

    if(strMonth[1] == 0)
    {
        strMonth[1] = strMonth[0]; strMonth[0] = '0'; strMonth[2] = 0;
    }
    if(strDay[1] == 0)
    {
        strDay[1] = strDay[0]; strDay[0] = '0'; strDay[2] = 0;
    }
    if(strYear[1] == 0)
    {
        strYear[1] = strYear[0]; strYear[0] = '0'; strYear[2] = 0;
    }
    if(strHour[1] == 0)
    {
        strHour[1] = strHour[0]; strHour[0] = '0'; strHour[2] = 0;
    }
    if(strMinute[1] == 0)
    {
        strMinute[1] = strMinute[0]; strMinute[0] = '0'; strMinute[2] = 0;
    }

    datetime[0] = strMonth[0];
    datetime[1] = strMonth[1];
    datetime[2] = '/';
    datetime[3] = strDay[0];
    datetime[4] = strDay[1];
    datetime[5] = '/';
    datetime[6] = strYear[0];
    datetime[7] = strYear[1];
    datetime[8] = ' ';
    datetime[9] = ' ';
    datetime[10] = strHour[0];
    datetime[11] = strHour[1];
    datetime[12] = ':';
    datetime[13] = strMinute[0];
    datetime[14] = strMinute[1];
    datetime[15] = ' ';

    datetime[17] = 'M';
    datetime[18] = 0;

    UseSystemFont();
    PutString(datetime, 10, 225);
}

void drawPad()
{
    
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
}

void drawFooter(unsigned char showPagingTabs)
{
    struct window pagingLine = {127,142,8,23};
    
    InitDrawWindow(&winPadBackground);

    if (showPagingTabs == 1)
    {
        HorizontalLine(255, 142, 23, 263);     
        
        // page tab lines
        HorizontalLine(255, 127, 8, 23);
        VerticalLine(255,127, 142, 23);
        DrawLine(DRAW_DRAW, &pagingLine);        
    }
    else
    {
        HorizontalLine(255, 142, 8, 263);
    }
    
    HorizontalLine(255, 144, 8, 263);
}

void changeDevice(unsigned char deviceNumber)
{
    char answer;
    drawPad();
    drawFooter(1);

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
            drawPad();
            drawFooter(0);
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
    
    UseSystemFont();

    if(curPage == 1)
        curFileHandle = Get1stDirEntry();
    else
        curFileHandle = GetNxtDirEntry();

    do
    {       
        if (curFileHandle->dostype != 0)
        {     
            //PutDecimal(SET_LEFTJUST + SET_SURPRESS, curFileHandle->dostype,  190, 10 + (20*ctr));
            // r5 (curFileHandle) is trashed by DoIcons and PutString
            tmp = r5;
            if(GetFHdrInfo(curFileHandle) == 0) 
            {
                //copy icon image data
                for(z=0; z < 63; z++)
                    fileIconImages[ctr][z+1] = fileHeader.icon_pic[z];

                // copy and clean up filename
                for(z=0; z<17; z++)
                {
                    if(curFileHandle->name[z] == 0xa0)
                        break;
                    fileIconNames[ctr][z] = curFileHandle->name[z];
                };
                fileIconNames[ctr][z] = 0;
                ctr++;              
            }
            r5 = tmp;   
        }

        // empty icon space
        if(curFileHandle->dostype == 0 && curFileHandle->name[0] == 0)
        {
            for(z=0; z < 63; z++)
                fileIconImages[ctr][z+1] = 0;
            
            fileIconNames[ctr][0] = 0;
            ctr++;  
        }
        
        if(ctr < 8)
            curFileHandle = GetNxtDirEntry();
        
    } while (ctr < 8);

    // Display icons and filenames
    // Desktop prints these in reverse order

    LoadCharSet ((struct fontdesc *)(bsd_small));
    
    tmp = (ctr == 8 ? 7 : ctr);
    do
    {
        updateFileIcon(tmp, fileIconImages[tmp]);

        if(tmp < 4)
            PutString(fileIconNames[tmp], 74, 40 + (tmp*50));
        else
            PutString(fileIconNames[tmp], 114, 40 + ((tmp-4)*50));  
        
        if(tmp == 0)
            break;

        tmp--;

    } while(TRUE);
    
    UseSystemFont();

    PutDecimal(SET_LEFTJUST + SET_SURPRESS, curPage,  135, 135);
}

void updatePadHeader()
{
    char *diskName = (char *)(0x841e);
    char newDiskName[17];
    unsigned blksfree = 0;
    unsigned long tmp = 0;
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

    r5 = 0x8200;
    blksfree = CalcBlksFree();
    tmp = blksfree * 256;
    kbytesfree = tmp/256;

    numFiles = getFileCount();

    UseSystemFont();

    PutString(newDiskName, 27, 100);
        
    PutString(hdr1,39, 27);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numFiles,  39, 18);
    
    PutString(hdr2,39, 68);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 64);
    
    PutString(hdr3,39, 123);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesUsed,  39, 118);
    
    PutString(hdr4,39, 206);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesfree, 39, 200);
    
}

unsigned getFileCount()
{
    unsigned ctr = 0;
    unsigned char eof = 0;

    curFileHandle = Get1stDirEntry();

    do
    {       
        if (curFileHandle->dostype != 0)
            ctr++;              
        
        curFileHandle = GetNxtDirEntry();
        asm("sty $02");
        eof = PEEK(2);
        
    } while (eof == 0);

    return ctr;
}

#include "desktop-icons.c"
#include "desktop-vectors.c"
#include "desktop-menu.c"




