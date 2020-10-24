#ifndef _desktop_vectors_
#define _desktop_vectors_

#define mouseXPos PEEK(0x3A)
#define mouseYPos PEEK(0x3C)

void_func oldMouseVector;
void_func oldIntTopVector;

void hook_into_system(void);
void remove_hook(void);
void newMouseVectorHandler(void);
void newIntTopVectorHandler(void);

#endif