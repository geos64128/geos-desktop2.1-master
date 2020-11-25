// ============================================================
//
// GEOS 64 - DESKTOP V2.1
// A cc65 recreation of the GEOS v2.0 desktop application
// Written by Scott Hutter aka "xlar54"
// Special thanks to the cc65 development team
//
//=============================================================

#include <geos.h>
#include <stdlib.h>
#include <PeekPoke.h>
#include <errno.h>
#include "desktop.h"
#include "desktop-res.h"
#include "desktop-icons.h"
#include "desktop-vectors.h"
#include "desktop-bsw6pt.h"

struct window winClockFrame = {0, 15, 221, SC_PIX_WIDTH-1};
struct window winClockBackground = {1, 14, 222, SC_PIX_WIDTH-2};
struct window winPadFrame = {19, 146, 8, 263};
struct window winPadBackground = {20,145,9,262};

struct filehandle *curFileHandle;
unsigned numFiles = 0;
unsigned numSelected = 0;
unsigned long kbytesUsed = 0;
unsigned long kbytesfree = 0;
unsigned char datetime[19];
unsigned char backColor = 0;

const graphicStr clrScreen = {
        MOVEPENTO(0,0),
        NEWPATTERN(2),
        RECTANGLETO(319,199),
        GSTR_END };

void main(void)
{
    initInputDriver();
    initIconTable();

    // store for restore purpose
    backColor = PEEK(0x8c00);
    
    drawScreen();
    
    changeDevice(curDrive);
    
    initPrinterDriver();

    hook_into_system();
    MainLoop();
};

void initClock()
{
    InitDrawWindow(&winClockFrame);
    FrameRectangle(255);
    updateClock();
}

void initInputDriver()
{
    // Loads and installs first input driver on disk
    // if none found, defaults to joystick

    unsigned char buffer[17];
    unsigned char x;

    SetDevice(8);
    OpenDisk();
    x = FindFTypes (buffer, INPUT_DEVICE, 1, NULL);

    if (x == 1)
        GetFile(0,buffer,0,0,0);
}

void initPrinterDriver()
{
    // Loads and installs first printer driver on disk
    // if none found, "not on disk"

    unsigned char buffer[17];
    const char notondisk[] = "NOT ON DISK";
    unsigned char tmp;
    unsigned char x;

    SetDevice(8);
    OpenDisk();
    tmp = FindFTypes (buffer, PRINTER, 1, NULL);

    LoadCharSet ((struct fontdesc *)(bsw_small));

    if (tmp == 1)
    {
        x = centerOver(36, buffer);
        PutString(buffer,177, x);
    }
    else
    {
        x = centerOver(36, notondisk);
        PutString(notondisk,177, x); 
    }

    UseSystemFont();
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
    
    if(hr > 12)
    {
        hr = hr - 12;
        datetime[16] = 'P';
    }
    else
    {
        if (hr==0) hr = 12;
        datetime[16] = 'A';
    }
        

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
    
    HorizontalLine(255, 43, 8, 263);
}

void drawFooter(unsigned char showPagingTabs)
{
    struct window pagingLine = {127,142,8,23};
    
    InitDrawWindow(&winPadBackground);

    if (showPagingTabs == TRUE)
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

void drawScreen()
{
    FillRam (0x8c00, backColor, 1000);
    GraphicsString(&clrScreen);
    
    DoMenu(&mainMenu);
    initClock();
    updateClock();   
}

void changeDevice(unsigned char deviceNumber)
{      
    SetDevice(deviceNumber);
    OpenDisk();

    if (_oserror != 0)
    {
        DlgBoxOk("Operation cancelled due to", "Missing or unformatted disk");
        drawPad();
        drawFooter(FALSE);
        return;
    }
    else
    {
        drawPad();
        drawFooter(TRUE);
        maxPage = getPageCount();

        //GetPtrCurDkNm(currentDiskName);  this doesnt work
        //replaced with...
        updateDiskName();
        
        if(!isGEOS)
        {
            if(DlgBoxYesNo("This is a NON-GEOS disk.", "Convert it?") == YES)
                SetGEOSDisk();
        }

        initIconTable();
        updateDriveIcons();
        DoIcons(myicontab);

        updatePadHeader();
        
        initIconTable();
        updateDriveIcons();
        
        curPage = 1;
        goPage(curPage);
        updateDirectory();
        DoIcons(myicontab);
    }
 
}

void updateDiskName()
{
    unsigned char* driveName;
    unsigned char z;

    if (curDrive == 8)  driveName = (char *)DRIVE_A_NAME;
    if (curDrive == 9)  driveName = (char *)DRIVE_B_NAME;
    if (curDrive == 10) driveName = (char *)DRIVE_C_NAME;
    if (curDrive == 11) driveName = (char *)DRIVE_D_NAME;

    // add padding
    currentDiskName[0] = ' ';

    // copy and clean up diskname
    for(z=1; z<19; z++)
    {
        if(driveName[z-1] == 0xa0)
            break;
        
        currentDiskName[z] = driveName[z-1];
    };

    // add padding
    currentDiskName[z++] = ' ';
    currentDiskName[z] = 0;
}

unsigned char goPage(unsigned char pageNumber)
{
    struct tr_se ts;

    if(pageNumber > maxPage)
        return 0;

    curPage = 1;
    
    Get1stDirEntry();
    ts.track = PEEK(0x8000);
    ts.sector = PEEK(0x8001);

    while(curPage != pageNumber)
    {
        ReadBuff(&ts);
        ts.track = PEEK(0x8000);
        ts.sector = PEEK(0x8001);

        curPage++;
    }
    
    return curPage;
}

void updateDirectory()
{
    unsigned ctr = 0;
    unsigned char z = 0;
    unsigned char eof = 0;
    unsigned tmp = 0;
    unsigned startPrint = 0;
    
    clearAllFileIcons();

    // GetNxtDirEntry() adds $20 to the current pointer, so
    // we subtract $20 so that the pointer gives us the
    // first file handle on this page
    r5 = 0x8002 - 0x20;
    
    do
    {   
        curFileHandle = (curPage == 1 && ctr == 0 ? Get1stDirEntry() : GetNxtDirEntry());
        
        if(curFileHandle == NULL)
            break;

        if (curFileHandle->dostype != 0)
        {
            // copy and clean up filename
            for(z=0; z<17; z++)
            {
                if(curFileHandle->name[z] == 0xa0) break;
                padIcons[ctr].filename[z] = curFileHandle->name[z];
            };

            padIcons[ctr].filename[z] = 0;

            if(GetFHdrInfo(curFileHandle) ==0)
            {
                //copy icon image data
                for(z=0; z < 63; z++)
                    padIcons[ctr].iconData[z+1] = fileHeader.icon_pic[z];
            }
            else
            {
                //copy cbm file icon image data
                for(z=0; z < 64; z++)
                    padIcons[ctr].iconData[z] = cbmFileIcon[z];
            }

            ctr++;
        } 
        else 
        {
            // empty icon space
            for(z=0; z < 63; z++)
                padIcons[ctr].iconData[z+1]  = 0;
            
            padIcons[ctr].filename[0] = 0;
            ctr++;
        }

        tmpr5 = r5;

    } while (ctr < 8);

    // Display icons and filenames
    // Desktop prints these in reverse order
    
    LoadCharSet ((struct fontdesc *)(bsw_small));
    
    tmp = (ctr == 8 ? 7 : ctr);
    do
    {
        // stamp the icon to the pad
        BitmapUp(&(padIcons[tmp].iconpic));

        // calculate the starting point for the filename
        // so that it is centered under the icon
        startPrint = centerOver(  (padIcons[tmp].iconpic.x*8 +padIcons[tmp].iconpic.width*8) - (padIcons[tmp].iconpic.width*8/2), padIcons[tmp].filename);

        if(tmp < 4)
            PutString(padIcons[tmp].filename, 74, startPrint);               
        else
            PutString(padIcons[tmp].filename, 114, startPrint);  
        
        if(tmp == 0)
            break;

        tmp--;

    } while(TRUE);
    
    UseSystemFont();
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, curPage,  135, 128);
    PutString("of", 135, 135);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, maxPage,  135, 147);
}

void updatePadHeader()
{
    unsigned long blksfree = 0;
    unsigned long tmp = 0;
    unsigned startPrint = 0;

    GetDirHead();

    blksfree = CalcBlksFree();
    tmp = r3;
    kbytesfree = blksfree * 256 / 1000;
    kbytesUsed = (tmp * 256 / 1000) - kbytesfree;

    numFiles = getFileCount();

    UseSystemFont();

    startPrint = centerOver(135, currentDiskName);
    PutString(currentDiskName, 27, startPrint);
    
    PutString(hdr1,39, 26);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numFiles,  39, 18);    
    
    PutString(hdr2,39, 66);    
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 62);
    
    PutString(hdr3,39, 126);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesUsed,  39, 116);
    
    PutString(hdr4,39, 196);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, kbytesfree, 39, 190);

}

void updateNumSelected()
{
    PutString("  ", 39,62);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 62);
}

unsigned centerOver(unsigned x, unsigned char *text)
{
    unsigned char len = 0;
    unsigned width = 0;
    unsigned char ctr = 0;

    if(text[0] == 0)
        return 0;

    while(text[len] != 0)
        len++;

    for(ctr=0;ctr<len;ctr++)
        width += GetCharWidth(text[ctr]);

    return (x - width/2);
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
        
    } while (curFileHandle != NULL);

    return ctr;
}

unsigned char getPageCount()
{
    struct tr_se ts;
    unsigned char pageCount;

    curFileHandle = Get1stDirEntry();
    ts.track = PEEK(0x8000);
    ts.sector = PEEK(0x8001);
    pageCount = 1;
    
    while(ts.track != 0)
    {
        ReadBuff(&ts);
        ts.track = PEEK(0x8000);
        ts.sector = PEEK(0x8001);
        pageCount++;
    };
    
    return pageCount;
}

#include "desktop-info.c"
#include "desktop-icons.c"
#include "desktop-vectors.c"
#include "desktop-menu.c"





