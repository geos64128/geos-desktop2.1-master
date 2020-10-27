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
    myicontab->tab[6].proc_ptr = (unsigned)  iconHandler;

    // file icons
    fileIcon[0].pic_ptr = 0;
    fileIcon[0].x = 5; // * 8 
    fileIcon[0].y = 50;
    fileIcon[0].width = 3; // * 8 
    fileIcon[0].heigth = 21;

    fileIcon[1].pic_ptr = 0;
    fileIcon[1].x = 12; // * 8 
    fileIcon[1].y = 50;
    fileIcon[1].width = 3; // * 8 
    fileIcon[1].heigth = 21;

    fileIcon[2].pic_ptr = 0;
    fileIcon[2].x = 19; // * 8 
    fileIcon[2].y = 50;
    fileIcon[2].width = 3; // * 8 
    fileIcon[2].heigth = 21;

    fileIcon[3].pic_ptr = 0;
    fileIcon[3].x = 26; // * 8 
    fileIcon[3].y = 50;
    fileIcon[3].width = 3; // * 8 
    fileIcon[3].heigth = 21;
//
    fileIcon[4].pic_ptr = 0;
    fileIcon[4].x = 5; // * 8 
    fileIcon[4].y = 90;
    fileIcon[4].width = 3; // * 8 
    fileIcon[4].heigth = 21;

    fileIcon[5].pic_ptr = 0;
    fileIcon[5].x = 12; // * 8 
    fileIcon[5].y = 90;
    fileIcon[5].width = 3; // * 8 
    fileIcon[5].heigth = 21;
 
    fileIcon[6].pic_ptr = 0;
    fileIcon[6].x = 19; // * 8 
    fileIcon[6].y = 90;
    fileIcon[6].width = 3; // * 8 
    fileIcon[6].heigth = 21;

    fileIcon[7].pic_ptr = 0;
    fileIcon[7].x = 26; // * 8 
    fileIcon[7].y = 90;
    fileIcon[7].width = 3; // * 8 
    fileIcon[7].heigth = 21;
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

void updateFileIcon(unsigned char iconnumber, char *icon_pic)
{
    fileIcon[iconnumber].pic_ptr = icon_pic;
    BitmapUp(&fileIcon[iconnumber]);
}

void iconHandler() 
{
    remove_hook();
    ToBASIC();
}

void iconHandlerDrvA()
{
    changeDevice(8);
}

void iconHandlerDrvB()
{
    changeDevice(9);
}

void iconHandlerDrvC()
{
    changeDevice(10);
}


void iconHandlerDrvD()
{
     changeDevice(11);
}


void iconHandlerRunApp()
{

}