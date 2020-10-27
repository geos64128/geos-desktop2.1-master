#ifndef _desktop_vectors_
#define _desktop_vectors_

#define mouseXPos PEEK(0x3A)
#define mouseYPos PEEK(0x3C)

void_func oldOtherPressVector;
void_func oldIntTopVector;

void hook_into_system(void);
void remove_hook(void);
void newOtherPressVectorHandler(void);
void newIntTopVectorHandler(void);

#endif