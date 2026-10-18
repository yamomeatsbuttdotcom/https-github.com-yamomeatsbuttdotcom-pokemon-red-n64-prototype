#ifndef LAB_VISUALS_H
#define LAB_VISUALS_H
#include <libdragon.h>
/* Stylized Oak's Lab selection interior, authored with RDP rectangles. */
static void lab_draw(int selection) {
 rdpq_set_mode_fill(RGBA32(192,175,144,255));
 rdpq_fill_rectangle(0,50,320,180);
 rdpq_set_mode_fill(RGBA32(105,131,157,255));
 rdpq_fill_rectangle(16,63,304,96);
 rdpq_set_mode_fill(RGBA32(119,79,48,255));
 rdpq_fill_rectangle(36,129,284,161);
 for(int i=0;i<3;i++){
   int x=77+i*82;
   rdpq_set_mode_fill(i==selection?RGBA32(242,208,87,255):RGBA32(184,187,191,255));
   rdpq_fill_rectangle(x-25,120,x+25,130);
   rdpq_set_mode_fill(RGBA32(221,65,64,255));
   rdpq_fill_rectangle(x-9,108,x+9,121);
   rdpq_set_mode_fill(RGBA32(238,237,227,255));
   rdpq_fill_rectangle(x-9,113,x+9,117);
 }
 rdpq_set_mode_standard();
}
#endif
