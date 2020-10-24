#include "desktop-vectors.h"

void hook_into_system(void) {
    oldMouseVector = mouseVector;
    mouseVector = newMouseVectorHandler;

    oldIntTopVector = intTopVector;
    intTopVector = newIntTopVectorHandler;
}

void remove_hook(void) {
    mouseVector = oldMouseVector;
    intTopVector = oldIntTopVector;
}

void newMouseVectorHandler(void) 
{
    unsigned char pgNext = 0;
    unsigned char pgPrev = 0;
    unsigned char tmp = 0;

    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseYPos,  190, 160);
    PutDecimal(SET_LEFTJUST + SET_SURPRESS, mouseXPos,  190, 190);

    if(mouseData < 128)
    {
        for(tmp=0; tmp < 14; tmp++)
        {
            if(mouseYPos > 126 && mouseYPos< 142)
            {
                if((mouseYPos == (127 + tmp)) && ((mouseXPos > (8+tmp)) && (mouseXPos < 24))) { 
                    pgNext = 1;
                };
            }
        }
    }

    if (pgNext == 1)
    {
        changeDevice(CUR_DEVICE);
        
        StartMouseMode();
        mouseVector = newMouseVectorHandler;
    }

    oldMouseVector();
}


void newIntTopVectorHandler(void) {
        
        // update time        
        oldIntTopVector();
}




