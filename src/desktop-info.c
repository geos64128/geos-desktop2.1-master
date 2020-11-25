#include "desktop-info.h"

void info_draw(char *filename)
{
    // snapshot the area
    InitDrawWindow(&infoFrame);
    ImprintRectangle();

    // only write to foreground 
    // (so we can recover later)
    dispBufferOn = ST_WR_FORE;

    InitDrawWindow(&infoFrame);
    FrameRectangle(255);

    SetPattern(0);
    InitDrawWindow(&infoBackground);
    Rectangle();

    // header lines
    HorizontalLine(255, 45, 71, 239);
    HorizontalLine(255, 47, 71, 239);
    HorizontalLine(255, 49, 71, 239);
    HorizontalLine(255, 51, 71, 239);
    HorizontalLine(255, 53, 71, 239);
    HorizontalLine(255, 55, 71, 239);

    info_initIconTable();

    info_update(filename);

    DoIcons(myicontab);
}

void info_initIconTable() 
{
    free(myicontab);
    myicontab = (struct icontab*)calloc(1, sizeof(struct icontab));

    myicontab->number = 1;
    myicontab->mousepos.x = 0;
    myicontab->mousepos.y = 0;

    // close window
    myicontab->tab[0].pic_ptr = closeIcon;
    myicontab->tab[0].x = 27; // * 8 
    myicontab->tab[0].y = 44;
    myicontab->tab[0].width = 2; // * 8 
    myicontab->tab[0].height = 11;
    myicontab->tab[0].proc_ptr = (unsigned)  on_infoClose;
}

void padName(char *filename, char *newfilename)
{
    unsigned char z;

    // add padding
    newfilename[0] = ' ';

    // copy and clean up
    for(z=1; z<19; z++)
    {
        if(filename[z-1] == 0xa0)
            break;
        
        newfilename[z] = filename[z-1];
    };

    // add padding
    newfilename[z++] = ' ';
    newfilename[z] = 0;
}

void info_update(unsigned char *filename)
{
    unsigned char r;
    struct filehandle myfilehandle;
    unsigned startPrint;
    char paddedfilename[19];
    char doBold[5] = CBOLDON "";
    char doPlain[5] = CPLAINTEXT "";

    r = FindFile(filename);

    if(r == 0)
    {
        myfilehandle = dirEntryBuf;
        if(GetFHdrInfo(&myfilehandle) ==0)
        {
            PutString("disk:", 63, 99);
            PutString("type:", 74, 97);
            PutString("class:", 85, 96);
            PutString("structure:", 96, 80);
            PutString("size:", 107, 99);
            PutString("modified:", 118, 80);
            PutString("author:", 129, 90);

            PutString(doBold, 64,125);
            PutString("Write Protect", 140,125);
            PutString(doPlain, 64,125);

            HorizontalLine(255, 145, 74, 236);
            HorizontalLine(255, 176, 74, 236);
            VerticalLine(255, 145, 176, 74);
            VerticalLine(255, 145, 176, 236);

            padName(&myfilehandle.name, &paddedfilename);
            startPrint = centerOver(155, paddedfilename);
            PutString(paddedfilename, 51, startPrint);

            PutString(doBold, 64,125);

            PutString(currentDiskName, 63, 125);

            switch(fileHeader.type)
            {
                case APPLICATION:
                    PutString("Application", 74, 125);
                    break;
                case AUTO_EXEC:
                    PutString("Auto-Exec", 74, 125);
                    break;
                case NOT_GEOS:
                case BASIC:
                case ASSEMBLY:
                    PutString("BASIC Prg.", 74, 125);
                    break;
                case DATA:
                case APPL_DATA:
                    PutString("Appl. Data", 74, 125);
                    break;
                case SYSTEM:
                    PutString("System", 74, 125);
                    break;
                case DESK_ACC:
                    PutString("Desk Accessory", 74, 125);
                    break;
                case FONT:
                    PutString("Font", 74, 125);
                    break;
                case PRINTER:
                    PutString("Printer Driver", 74, 125);
                    break;
                case INPUT_DEVICE:
                    PutString("C64 Input Driver", 74, 125);
                    break;
            }
            
            PutString(fileHeader.class_name, 85, 125);

            switch (fileHeader.structure)
            {
                case SEQUENTIAL:
                    PutString("SEQUENTIAL", 96, 125);
                    break;
                case VLIR:
                    PutString("VLIR", 96, 125);
                    break;
            }

            PutDecimal(SET_LEFTJUST + SET_SURPRESS, myfilehandle.size,  107, 125);

            PutDecimal(SET_LEFTJUST + SET_SURPRESS, myfilehandle.date.f_month,  118, 125);

            PutString(fileHeader.author, 129, 125);

            PutString(fileHeader.note, 155, 80);

            PutString(CPLAINTEXT, 64,125);
        }
    }

    
}

void on_infoClose()
{
    // Restore the screen
    InitDrawWindow(&infoFrame);
    RecoverRectangle();

    dispBufferOn = ST_WR_FORE | ST_WR_BACK;

    initIconTable();
    updateDriveIcons();
    DoIcons(myicontab);

    unselectAllFileIcons();

    goPage(curPage);
    updateDirectory();
}