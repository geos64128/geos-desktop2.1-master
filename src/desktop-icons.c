#include "desktop-icons.h"

void initIconTable() 
{
    free(myicontab);
    myicontab = (struct icontab*)calloc(1, sizeof(struct icontab));

    myicontab->number = 7;
    myicontab->mousepos.x = 0;
    myicontab->mousepos.y = 0;

    
    myicontab->tab[0].pic_ptr = 0;
    myicontab->tab[0].x = 35; // * 8 
    myicontab->tab[0].y = 22;
    myicontab->tab[0].width = 3; // * 8
    myicontab->tab[0].heigth = 21;
    myicontab->tab[0].proc_ptr = (unsigned) iconHandlerDrvA;

    myicontab->tab[1].pic_ptr = 0;
    myicontab->tab[1].x = 35; // * 8 
    myicontab->tab[1].y = 54;
    myicontab->tab[1].width = 3; // * 8 
    myicontab->tab[1].heigth = 21;
    myicontab->tab[1].proc_ptr = (unsigned)  iconHandlerDrvB;

    myicontab->tab[2].pic_ptr = 0;
    myicontab->tab[2].x = 35; // * 8 
    myicontab->tab[2].y = 86;
    myicontab->tab[2].width = 3; // * 8 
    myicontab->tab[2].heigth = 21;
    myicontab->tab[2].proc_ptr = (unsigned)  iconHandlerDrvC;

    myicontab->tab[3].pic_ptr = 0;
    myicontab->tab[3].x = 35; // * 8 
    myicontab->tab[3].y = 118;
    myicontab->tab[3].width = 3; // * 8 
    myicontab->tab[3].heigth = 21;
    myicontab->tab[3].proc_ptr = (unsigned)  iconHandlerDrvD;

    // trash
    myicontab->tab[4].pic_ptr = trashIcon;
    myicontab->tab[4].x = 35; // * 8 
    myicontab->tab[4].y = 154;
    myicontab->tab[4].width = 3; // * 8 
    myicontab->tab[4].heigth = 21;
    myicontab->tab[4].proc_ptr = (unsigned)  iconHandler;

    // printer
    myicontab->tab[5].pic_ptr = printerIcon;
    myicontab->tab[5].x = 3; // * 8 
    myicontab->tab[5].y = 154;
    myicontab->tab[5].width = 3; // * 8 
    myicontab->tab[5].heigth = 21;
    myicontab->tab[5].proc_ptr = (unsigned)  iconHandler;

    // close disk
    myicontab->tab[6].pic_ptr = closeIcon;
    myicontab->tab[6].x = 30; // * 8 
    myicontab->tab[6].y = 20;
    myicontab->tab[6].width = 2; // * 8 
    myicontab->tab[6].heigth = 11;
    myicontab->tab[6].proc_ptr = (unsigned)  iconCloseDiskHandler;

    // file icons
    fileIcons[0].pic_ptr = 0;
    fileIcons[0].x = 5; // * 8 
    fileIcons[0].y = 50;
    fileIcons[0].width = 3; // * 8 
    fileIcons[0].heigth = 21;

    fileIcons[1].pic_ptr = 0;
    fileIcons[1].x = 12; // * 8 
    fileIcons[1].y = 50;
    fileIcons[1].width = 3; // * 8 
    fileIcons[1].heigth = 21;

    fileIcons[2].pic_ptr = 0;
    fileIcons[2].x = 19; // * 8 
    fileIcons[2].y = 50;
    fileIcons[2].width = 3; // * 8 
    fileIcons[2].heigth = 21;

    fileIcons[3].pic_ptr = 0;
    fileIcons[3].x = 26; // * 8 
    fileIcons[3].y = 50;
    fileIcons[3].width = 3; // * 8 
    fileIcons[3].heigth = 21;
//
    fileIcons[4].pic_ptr = 0;
    fileIcons[4].x = 5; // * 8 
    fileIcons[4].y = 90;
    fileIcons[4].width = 3; // * 8 
    fileIcons[4].heigth = 21;

    fileIcons[5].pic_ptr = 0;
    fileIcons[5].x = 12; // * 8 
    fileIcons[5].y = 90;
    fileIcons[5].width = 3; // * 8 
    fileIcons[5].heigth = 21;
 
    fileIcons[6].pic_ptr = 0;
    fileIcons[6].x = 19; // * 8 
    fileIcons[6].y = 90;
    fileIcons[6].width = 3; // * 8 
    fileIcons[6].heigth = 21;

    fileIcons[7].pic_ptr = 0;
    fileIcons[7].x = 26; // * 8 
    fileIcons[7].y = 90;
    fileIcons[7].width = 3; // * 8 
    fileIcons[7].heigth = 21;
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

void updateDriveIcons()
{
    myicontab->tab[0].pic_ptr = getDriveIcon(DRIVE_A_TYPE);
    myicontab->tab[1].pic_ptr = getDriveIcon(DRIVE_B_TYPE);
    myicontab->tab[2].pic_ptr = getDriveIcon(DRIVE_C_TYPE);
    myicontab->tab[3].pic_ptr = getDriveIcon(DRIVE_D_TYPE);
}

void clearAllFileIcons()
{
    unsigned char idx = 0;
    unsigned char tmp = 0;

    drawWindow.top = 50;
    drawWindow.left = 24;
    drawWindow.bot = 140;
    drawWindow.right = 260;

    SetPattern(0);
    Rectangle();

    for(idx=0; idx<8;idx++)
    {
        for(tmp=0;tmp<63;tmp++)
            fileIconImages[idx][tmp+1] = 0;

        //updateFileIcon(idx, fileIconImages[idx]);
    }        

}

void updateFileIcon(unsigned char iconnumber, char *icon_pic)
{
    fileIcons[iconnumber].pic_ptr = icon_pic;
    fileIconWindows[iconnumber].top   = fileIcons[iconnumber].y;
    fileIconWindows[iconnumber].bot   = (fileIcons[iconnumber].y + fileIcons[iconnumber].heigth) - 1;
    fileIconWindows[iconnumber].left  = fileIcons[iconnumber].x*8;
    fileIconWindows[iconnumber].right = (fileIcons[iconnumber].x*8 + fileIcons[iconnumber].width*8) - 1;
    BitmapUp(&fileIcons[iconnumber]);
}

void selectFileIcon(unsigned char iconnumber)
{
    // reverse the icon image
    InitDrawWindow(&fileIconWindows[iconnumber]);
    InvertRectangle();

    fileIconSelected[iconnumber] = 1;
}

void unselectFileIcon(unsigned char iconnumber)
{
    // reverse the icon image
    InitDrawWindow(&fileIconWindows[iconnumber]);
    InvertRectangle();

    fileIconSelected[iconnumber] = 0;
}

void unselectAllFileIcons()
{
    unsigned char tmp = 0;

    //unselect all
    for(tmp=0; tmp<8;tmp++)
    {
        if(fileIconSelected[tmp] == 1)
            unselectFileIcon(tmp);
    }
}

void unselectAllFileIconsExcept(unsigned char iconnumber)
{
    unsigned char tmp = 0;

    //unselect others
    for(tmp=0; tmp<8;tmp++)
    {
        if(tmp != iconnumber && fileIconSelected[tmp] == 1)
        {
            unselectFileIcon(tmp);
            break;
        }
    }
}

void iconHandler() 
{
    remove_hook();
    ToBASIC();
}

void iconCloseDiskHandler()
{
    drawPad();
    drawFooter(0);
}

void iconHandlerDrvA()
{
    curPage = 1;
    changeDevice(8);
}

void iconHandlerDrvB()
{
    curPage = 1;
    changeDevice(9);
}

void iconHandlerDrvC()
{
    curPage = 1;
    changeDevice(10);
}

void iconHandlerDrvD()
{
    curPage = 1;
     changeDevice(11);
}


void iconHandlerRunApp()
{

}