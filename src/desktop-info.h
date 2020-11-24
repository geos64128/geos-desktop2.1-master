#ifndef _desktopinfo_
#define _desktopinfo_

struct window infoFrame = {43, 179, 71, 240};
struct window infoBackground = {44,178,72, 239};

void info_draw();
void info_initIconTable();
void info_update(unsigned char *filename);
void on_infoClose();

#endif