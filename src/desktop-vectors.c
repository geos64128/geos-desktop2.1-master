#include "desktop-vectors.h"

void hook_into_system(void) {
    oldOtherPressVector = otherPressVec;
    otherPressVec = newOtherPressVectorHandler;

    oldIntTopVector = intTopVector;
    intTopVector = newIntTopVectorHandler;
}

void remove_hook(void) {
    otherPressVec = oldOtherPressVector;
    intTopVector = oldIntTopVector;
}

void newOtherPressVectorHandler(void) 
{
    unsigned char pgNext = 0;
    unsigned char pgPrev = 0;
    unsigned char tmp = 0;
    unsigned char selectedIcon = 99;

    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseXPos,  190, 160);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseYPos,  190, 190);

    // if mouse down, check region
    if(mouseData < 128)
    {    
        // file icon selected?
        for(tmp=0; tmp<8;tmp++)
        {
            if(IsMseInRegion(&fileIconWindows[tmp]))
            {
                InitDrawWindow(&fileIconWindows[tmp]);
                InvertRectangle();
                PutString("icon", 190, 80);
                selectedIcon = tmp;
            }
        }   
        
        // pager icon selected?
        if (selectedIcon == 99)
        {
            // paging
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
        }

        if (pgNext == 1)
            PutString("pgNext", 190, 240);

        if (pgPrev == 1)
            PutString("pgPrev", 190, 240);

        if (pgNext == 0 && pgPrev == 0)
            PutString("no click", 190, 240);
    }

    oldOtherPressVector();
}


void newIntTopVectorHandler(void) {
        
        // update time        
        oldIntTopVector();
}




