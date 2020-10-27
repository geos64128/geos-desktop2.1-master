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

    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseYPos,  190, 160);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseXPos,  190, 190);

    // if mouse down, check to see if pointing at the next or prev pager
    if(mouseData < 128)
    {
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




