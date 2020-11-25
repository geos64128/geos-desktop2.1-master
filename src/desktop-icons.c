#include "desktop-icons.h"

void initIconTable() 
{
    unsigned char tmp;
    unsigned char tmp2;

    free(myicontab);
    myicontab = (struct icontab*)calloc(1, sizeof(struct icontab));

    myicontab->number = 7;
    myicontab->mousepos.x = 0;
    myicontab->mousepos.y = 0;

    
    myicontab->tab[0].pic_ptr = 0;
    myicontab->tab[0].x = 35; // * 8 
    myicontab->tab[0].y = 22;
    myicontab->tab[0].width = 3; // * 8
    myicontab->tab[0].height = 21;
    myicontab->tab[0].proc_ptr = (unsigned) iconHandlerDrvA;

    myicontab->tab[1].pic_ptr = 0;
    myicontab->tab[1].x = 35; // * 8 
    myicontab->tab[1].y = 54;
    myicontab->tab[1].width = 3; // * 8 
    myicontab->tab[1].height = 21;
    myicontab->tab[1].proc_ptr = (unsigned)  iconHandlerDrvB;

    myicontab->tab[2].pic_ptr = 0;
    myicontab->tab[2].x = 35; // * 8 
    myicontab->tab[2].y = 86;
    myicontab->tab[2].width = 3; // * 8 
    myicontab->tab[2].height = 21;
    myicontab->tab[2].proc_ptr = (unsigned)  iconHandlerDrvC;

    myicontab->tab[3].pic_ptr = 0;
    myicontab->tab[3].x = 35; // * 8 
    myicontab->tab[3].y = 118;
    myicontab->tab[3].width = 3; // * 8 
    myicontab->tab[3].height = 21;
    myicontab->tab[3].proc_ptr = (unsigned)  iconHandlerDrvD;

    // trash
    myicontab->tab[4].pic_ptr = trashIcon;
    myicontab->tab[4].x = 35; // * 8 
    myicontab->tab[4].y = 154;
    myicontab->tab[4].width = 3; // * 8 
    myicontab->tab[4].height = 21;
    myicontab->tab[4].proc_ptr = (unsigned)  iconHandler;

    // printer
    myicontab->tab[5].pic_ptr = printerIcon;
    myicontab->tab[5].x = 3; // * 8 
    myicontab->tab[5].y = 154;
    myicontab->tab[5].width = 3; // * 8 
    myicontab->tab[5].height = 21;
    myicontab->tab[5].proc_ptr = (unsigned)  iconHandler;

    // close disk
    myicontab->tab[6].pic_ptr = closeIcon;
    myicontab->tab[6].x = 30; // * 8 
    myicontab->tab[6].y = 20;
    myicontab->tab[6].width = 2; // * 8 
    myicontab->tab[6].height = 11;
    myicontab->tab[6].proc_ptr = (unsigned)  iconCloseDiskHandler;

    // file icons
    for(tmp=0; tmp<8;tmp++)
    {
        padIcons[tmp].iconData[0] = 192;
        for(tmp2=1;tmp2<64;tmp2++)
            padIcons[tmp].iconData[tmp2] = 0;
    }

    padIcons[0].iconpic.pic_ptr = padIcons[0].iconData;
    padIcons[0].iconpic.x = 5; // * 8 
    padIcons[0].iconpic.y = 50;
    padIcons[0].iconpic.width = 3; // * 8 
    padIcons[0].iconpic.height = 21;

    padIcons[1].iconpic.pic_ptr = padIcons[1].iconData;
    padIcons[1].iconpic.x = 12; // * 8 
    padIcons[1].iconpic.y = 50;
    padIcons[1].iconpic.width = 3; // * 8 
    padIcons[1].iconpic.height = 21;

    padIcons[2].iconpic.pic_ptr = padIcons[2].iconData;
    padIcons[2].iconpic.x = 19; // * 8 
    padIcons[2].iconpic.y = 50;
    padIcons[2].iconpic.width = 3; // * 8 
    padIcons[2].iconpic.height = 21;

    padIcons[3].iconpic.pic_ptr = padIcons[3].iconData;
    padIcons[3].iconpic.x = 26; // * 8 
    padIcons[3].iconpic.y = 50;
    padIcons[3].iconpic.width = 3; // * 8 
    padIcons[3].iconpic.height = 21;

//
    padIcons[4].iconpic.pic_ptr = padIcons[4].iconData;
    padIcons[4].iconpic.x = 5; // * 8 
    padIcons[4].iconpic.y = 90;
    padIcons[4].iconpic.width = 3; // * 8 
    padIcons[4].iconpic.height = 21;

    padIcons[5].iconpic.pic_ptr = padIcons[5].iconData;
    padIcons[5].iconpic.x = 12; // * 8 
    padIcons[5].iconpic.y = 90;
    padIcons[5].iconpic.width = 3; // * 8 
    padIcons[5].iconpic.height = 21;

    padIcons[6].iconpic.pic_ptr = padIcons[6].iconData;
    padIcons[6].iconpic.x = 19; // * 8 
    padIcons[6].iconpic.y = 90;
    padIcons[6].iconpic.width = 3; // * 8 
    padIcons[6].iconpic.height = 21;

    padIcons[7].iconpic.pic_ptr = padIcons[7].iconData;
    padIcons[7].iconpic.x = 26; // * 8 
    padIcons[7].iconpic.y = 90;
    padIcons[7].iconpic.width = 3; // * 8 
    padIcons[7].iconpic.height = 21;

    // set positions
    for(tmp=0;tmp<8;tmp++)
    {
        padIcons[tmp].window.top   = padIcons[tmp].iconpic.y;
        padIcons[tmp].window.bot   = (padIcons[tmp].iconpic.y + padIcons[tmp].iconpic.height) - 1;
        padIcons[tmp].window.left  = padIcons[tmp].iconpic.x*8;
        padIcons[tmp].window.right = (padIcons[tmp].iconpic.x*8 + padIcons[tmp].iconpic.width*8) - 1;
    }
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
            padIcons[idx].iconData[tmp+1] = 0;
    }        

}

void selectFileIcon(unsigned char iconnumber)
{
    // reverse the icon image
    InitDrawWindow(&padIcons[iconnumber].window);
    InvertRectangle();

    padIcons[iconnumber].selected = 1;

    numSelected++;

    // update selected pad header
    updateNumSelected();
}

void selectAllFileIcons()
{
    unsigned char tmp = 0;

    //unselect all
    for(tmp=0; tmp<8;tmp++)
    {
        if(padIcons[tmp].selected == 0 && padIcons[tmp].filename[0] != 0)
        {
            selectFileIcon(tmp);
            numSelected++;
        }
    }
    
    updateNumSelected();
}

void unselectFileIcon(unsigned char iconnumber)
{
    // reverse the icon image
    InitDrawWindow(&padIcons[iconnumber].window);
    InvertRectangle();

    padIcons[iconnumber].selected = 0;

    numSelected--;

    // update selected pad header
    updateNumSelected();
}

void unselectAllFileIcons()
{
    unsigned char tmp = 0;

    //unselect all
    for(tmp=0; tmp<8;tmp++)
    {
        if(padIcons[tmp].selected == 1)
            unselectFileIcon(tmp);
    }

    numSelected = 0;
    updateNumSelected();
}

void unselectAllFileIconsExcept(unsigned char iconnumber)
{
    unsigned char tmp = 0;

    //unselect others
    for(tmp=0; tmp<8;tmp++)
    {
        if(tmp != iconnumber && padIcons[tmp].selected == 1)
        {
            unselectFileIcon(tmp);
            break;
        }
    }

    numSelected = 1;
    updateNumSelected();
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
    unselectAllFileIcons();

    curPage = 1;
    changeDevice(8);
}

void iconHandlerDrvB()
{
    unselectAllFileIcons();

    curPage = 1;
    changeDevice(9);
}

void iconHandlerDrvC()
{
    unselectAllFileIcons();

    curPage = 1;
    changeDevice(10);
}

void iconHandlerDrvD()
{
    unselectAllFileIcons();

    curPage = 1;
     changeDevice(11);
}


void iconHandlerRunApp(unsigned char iconnumber)
{
    unselectAllFileIcons();
    
    FindFile(padIcons[iconnumber].filename);
    loadFileHandle = &dirEntryBuf;

    if(loadFileHandle->type == DESK_ACC || loadFileHandle->type == APPLICATION || loadFileHandle->type == AUTO_EXEC)
    {
        GetFile(0,padIcons[iconnumber].filename,0,0,0);
        drawScreen();
    }
    else
        DlgBoxOk("This file can't be opened", "by the deskTop.");
}

signed char clickPagerCheck()
{
    unsigned char tmp = 0;

    // did user click paging tabs?
    for(tmp=0; tmp < 14; tmp++)
    {
        if(mouseYPos > 126 && mouseYPos< 142)
        {
            if((mouseYPos == (127 + tmp)) && ((mouseXPos > (8+tmp)) && (mouseXPos < 24))) { 
                return 1;
            };
            
            if((mouseYPos == 127 + tmp) && (mouseXPos > 8 && mouseXPos < (10 + tmp))) { 
                return -1;
            };
        }
    }

    return 0;
}

signed char clickFileIconCheck()
{
    unsigned char tmp = 0;

    for(tmp=0; tmp<8;tmp++)
    {
        if(IsMseInRegion(&padIcons[tmp].window) && padIcons[tmp].filename[0] != 0)
            return tmp;
    } 

    return -1;
}

unsigned char dblClickFileIconCheck()
{
    // setting dblClickCount counts down each irq to zero
    // 30 cycles to perform a double click
    dblClickCount = 30;

    while (dblClickCount != 0)
    {
        // if mouse button released...
        if(mouseData == 128)
        {
            while (dblClickCount != 0)
            {
                // and then clicked again...
                if(mouseData == 0)
                {
                    return TRUE;
                }     
            }
        }
    }

    return FALSE;
}

void iconBeginDrag(unsigned char iconnumber)
{
    if(numSelected > 1)
        DrawSprite(1, multiFileIcon+1);
    else
        DrawSprite(1, padIcons[iconnumber].iconData+1);
    
    location.x = mouseXPos-12;
    location.y = mouseYPos-10;
    PosSprite(1, &location);
    EnablSprite(1);
    dragMode = 1;
}

void iconEndDrag() 
{
    dragMode = 0;
    DisablSprite(1);


}

