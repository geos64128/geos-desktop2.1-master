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
    unsigned char pgNext = 0;
    unsigned char pgPrev = 0;
    unsigned char tmp = 0;
    unsigned char tmp2 = 0;
    unsigned char typeSelected = 0;

    // if mouse down, check region
    if(mouseData == 0)
    {
        // did user click paging tabs?
        for(tmp=0; tmp < 14; tmp++)
        {
            if(mouseYPos > 126 && mouseYPos< 142)
            {
                if((mouseYPos == (127 + tmp)) && ((mouseXPos > (8+tmp)) && (mouseXPos < 24))) { 
                    pgNext = 1;
                    break;
                };
                
                if((mouseYPos == 127 + tmp) && (mouseXPos > 8 && mouseXPos < (10 + tmp))) { 
                    pgPrev = 1;
                    break;
                };
            }
        }

        if (pgNext == 1)
        {
            clearAllFileIcons();
            curPage++;
            updateDirectory();
        } 
        else if (pgPrev == 1)
        {
            clearAllFileIcons();
            curPage--;
            updateDirectory();
        } 
        else 
        {
            // file icon selected?
            for(tmp=0; tmp<8;tmp++)
            {
                if(IsMseInRegion(&fileIconWindows[tmp]) && fileIconNames[tmp][0] != 0)
                {
                    unselectAllFileIcons();
                    selectFileIcon(tmp);
                    
                    numSelected=1;

                    // update selected pad header
                    PutString("  ", 39,64);
                    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 64);

                    // check for double click
                    // $8515 counts down from the applied value to zero every interrupt
                    dblClickCount = 30; //POKE(0x8515, 30);
                    while (dblClickCount != 0) //(PEEK(0x8515) != 0)
                    {
                        if(mouseData == 128)
                        {
                            while (dblClickCount != 0) //(PEEK(0x8515) != 0)
                            {
                                if(mouseData == 0)
                                {
                                    numSelected = 0;
                                    PutString("  ", 39,64);
                                    PutDecimal(SET_LEFTJUST + SET_SURPRESS, numSelected,  39, 64);

                                    unselectAllFileIcons();
                                    
                                    FindFile(fileIconNames[tmp]);
                                    loadFileHandle = &dirEntryBuf;

                                    if(loadFileHandle->type == DESK_ACC || loadFileHandle->type == APPLICATION
                                    || loadFileHandle->type == AUTO_EXEC)
                                    {
                                        GetFile(0,fileIconNames[tmp],0,0,0);
                                    }
                                    else
                                    {
                                        DlgBoxOk("This file can't be opened", "by the deskTop.");
                                    }
                                    
                                    
                                }
                                    
                            }

                        }
                        
                    }
                }
            }
        }
    }   
    
    oldOtherPressVector();
}


void newAppMainHandler(void) {
        
        if(system_date.s_minutes != lastMinute)
        {
            updateClock();
            lastMinute = system_date.s_minutes;
        }
                 
        oldAppMain();
}




