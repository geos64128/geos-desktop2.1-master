#ifndef _desktop_vectors_
#define _desktop_vectors_

#define mouseXPos PEEK(0x3A)
#define mouseYPos PEEK(0x3C)

void_func oldOtherPressVector;
void_func oldAppMain;

unsigned char lastMinute = 99;
unsigned char mousereleased = 0;
unsigned char cbmKeyPressed = FALSE;

void hook_into_system(void);
void remove_hook(void);
void newOtherPressVectorHandler(void);
void newAppMainHandler(void);

unsigned char isCBMKeyPressed();

#endif