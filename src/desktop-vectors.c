#include "desktop-vectors.h"

void hook_into_system(void) {
    oldOtherPressVector = otherPressVec;
    otherPressVec = newOtherPressVectorHandler;

    oldAppMain = appMain;
    appMain = newAppMainHandler;
}

void remove_hook(void) {
    otherPressVec = oldOtherPressVector;
    appMain = oldAppMain;
}

void newOtherPressVectorHandler(void) 
{
    signed char selected = -1;
    unsigned char tmp = 0;
    unsigned char tmp2 = 0;
    unsigned char typeSelected = 0;
    signed char pager = 0;
    

    // if mouse down...
    if(mouseData == 0)
    {
        // did user click paging tabs?
        pager = clickPagerCheck();

        if (pager != 0)
        {
            clearAllFileIcons();
            curPage = curPage + pager;
            curPage = (curPage == 0 ? maxPage : curPage);
            curPage = (curPage > maxPage ? 1 : curPage);
            updateDirectory();
            return;
        } 

        // did user click a file icon?
        selected = clickFileIconCheck();

        if(selected != -1)
        {
            // if icon is already selected, start drag operation
            if (fileIconSelected[selected] == 1)
            {
                if(dragMode == 0)
                    iconBeginDrag(selected);
                else
                    iconEndDrag();
            }
            else
            {
                // select the icon
                if(cbmKeyPressed == TRUE)
                {
                    selectFileIcon(selected);
                }
                else
                {
                    unselectAllFileIcons();
                    selectFileIcon(selected);

                    // check for double click
                    if(dblClickFileIconCheck() == TRUE)
                    {
                        iconHandlerRunApp(selected);
                        changeDevice(curDrive);
                    }
                }
            }
                
        }        
        else
        {
            iconEndDrag();
            unselectAllFileIcons();
        }
    }   
    
    oldOtherPressVector();
}


void newAppMainHandler(void) {
        
        unsigned char x = 0;

        if(system_date.s_minutes != lastMinute)
        {
            updateClock();
            lastMinute = system_date.s_minutes;
        }

        if(dragMode == 1)
        {
            //PutDecimal(SET_LEFTJUST + SET_SURPRESS, x,  190, 100);

            if (x == 223)
                iconEndDrag();
            else
            {
                for(x=0;x<8;x++)
                {
                    if(fileIconSelected[x] == 1)
                    {
                        location.x = mouseXPos-12;
                        location.y = mouseYPos-10;
                        PosSprite(1, &location);
                    }
                }                   
            }         
        } 

        if (mouseData != 0)
        {
            // set flag if cbm key is pressed

            // disable interrupts, switch IO in
            asm("php");
            asm("sei");
            asm("lda $01");
            asm("pha");
            asm("lda #$35");
            asm("sta $01");

            asm("lda #$7f"); // col 7 (%011111111)
            asm("sta $dc00");
            asm("lda $dc01");
            asm("and #$20"); // mask row 5 (%00100000)

            x = __A__;
            
            // restore GEOS kernal
            asm("pla");
            asm("sta $01");
            asm("plp");

            cbmKeyPressed = (x == 0 ? TRUE : FALSE);

            //PutDecimal(SET_LEFTJUST + SET_SURPRESS, cbmKeyPressed,  190, 100);
            
        }

        oldAppMain();
}




