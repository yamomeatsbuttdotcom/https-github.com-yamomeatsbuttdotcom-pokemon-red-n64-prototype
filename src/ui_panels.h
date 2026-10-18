#ifndef UI_PANELS_H
#define UI_PANELS_H
#include <libdragon.h>
static void ui_panel(int x0,int y0,int x1,int y1){
 rdpq_set_mode_fill(RGBA32(19,39,79,255));rdpq_fill_rectangle(x0,y0,x1,y1);
 rdpq_set_mode_fill(RGBA32(225,231,237,255));
 rdpq_fill_rectangle(x0,y0,x1,y0+2);rdpq_fill_rectangle(x0,y1-2,x1,y1);
 rdpq_fill_rectangle(x0,y0,x0+2,y1);rdpq_fill_rectangle(x1-2,y0,x1,y1);
 rdpq_set_mode_standard();
}
static void ui_hp_bar(int x,int y,int hp,int max_hp){
 int fill=max_hp?hp*70/max_hp:0;if(fill<0)fill=0;if(fill>70)fill=70;
 rdpq_set_mode_fill(RGBA32(35,38,48,255));rdpq_fill_rectangle(x,y,x+72,y+9);
 rdpq_set_mode_fill(hp*3>max_hp?RGBA32(67,188,89,255):RGBA32(224,151,55,255));
 rdpq_fill_rectangle(x+1,y+1,x+1+fill,y+8);rdpq_set_mode_standard();
}
#endif
