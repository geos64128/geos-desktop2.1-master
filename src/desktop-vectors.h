#ifndef _desktop_vectors_
#define _desktop_vectors_

#include <geos/gstruct.h>
#include <geos/ggraph.h>
#include <geos/gsym.h>
#include <geos/gsprite.h>
#include <peekpoke.h>
#include "desktop-icons.h"

#define mouseXPos PEEK(0x3A)
#define mouseYPos PEEK(0x3C)

extern void updateClock();
extern void updateDirectory();
extern unsigned numSelected;
extern unsigned char curPage;

void hook_into_system(void);
void remove_hook(void);
void newOtherPressVectorHandler(void);
void newAppMainHandler(void);

#endif