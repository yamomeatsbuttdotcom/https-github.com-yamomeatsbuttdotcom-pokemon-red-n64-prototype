#ifndef BATTLE_VISUALS_H
#define BATTLE_VISUALS_H
#include <libdragon.h>
/* Simple geometric creatures: colored silhouettes, no extracted game assets. */
static void battle_creature(int x,int y,int type,int back) {
 color_t body = type==0?RGBA32(74,158,94,255):type==1?RGBA32(219,113,57,255):RGBA32(74,135,201,255);
 if(type>=3)body=RGBA32(133,133,143,255);
 rdpq_set_mode_fill(RGBA32(94,108,91,255));
 rdpq_fill_rectangle(x-22,y+25,x+26,y+30);
 rdpq_set_mode_fill(body);
 rdpq_fill_rectangle(x-14,y-5,x+14,y+23);
 rdpq_fill_rectangle(x-9,y-15,x+8,y-3);
 rdpq_fill_rectangle(x-21,y+5,x-13,y+20);
 rdpq_fill_rectangle(x+13,y+5,x+21,y+20);
 rdpq_set_mode_fill(RGBA32(236,222,192,255));
 rdpq_fill_rectangle(x+(back?-7:3),y-8,x+(back?-4:6),y-5);
 rdpq_set_mode_standard();
}
#endif
