#ifndef BATTLE_VISUALS_H
#define BATTLE_VISUALS_H
#include <libdragon.h>
/* Original pixel-silhouette stand-ins. Each starter has a distinct shape. */
static void battle_rect(int x0,int y0,int x1,int y1,color_t color) {
    rdpq_set_mode_fill(color);
    rdpq_fill_rectangle(x0,y0,x1,y1);
}
static void battle_creature(int x,int y,int type,int back) {
    const color_t green=RGBA32(76,165,102,255);
    const color_t orange=RGBA32(230,123,61,255);
    const color_t blue=RGBA32(80,144,211,255);
    const color_t rock=RGBA32(140,133,129,255);
    battle_rect(x-27,y+25,x+28,y+30,RGBA32(83,108,99,255));
    if(type==0) { /* Bulbasaur: squat body and large back bulb. */
        battle_rect(x-20,y+1,x+21,y+23,green);
        battle_rect(x-14,y-12,x+7,y+6,RGBA32(66,124,85,255));
        battle_rect(x-8,y-21,x+2,y-8,RGBA32(84,157,94,255));
        battle_rect(x-19,y+18,x-12,y+26,green);
        battle_rect(x+13,y+18,x+20,y+26,green);
    } else if(type==1) { /* Charmander: upright body, tail and flame. */
        battle_rect(x-11,y-6,x+14,y+22,orange);
        battle_rect(x-9,y-23,x+11,y-5,orange);
        battle_rect(x+13,y+12,x+27,y+17,orange);
        battle_rect(x+24,y+1,x+32,y+14,RGBA32(249,192,59,255));
        battle_rect(x+26,y-5,x+30,y+4,RGBA32(237,90,47,255));
        battle_rect(x-10,y+19,x-3,y+28,orange);
        battle_rect(x+7,y+19,x+14,y+28,orange);
    } else if(type==2) { /* Squirtle: blue head, limbs and brown shell. */
        battle_rect(x-17,y+1,x+18,y+23,RGBA32(154,111,75,255));
        battle_rect(x-10,y-20,x+11,y+2,blue);
        battle_rect(x-24,y+9,x-15,y+19,blue);
        battle_rect(x+17,y+9,x+25,y+19,blue);
        battle_rect(x-15,y+20,x-6,y+28,blue);
        battle_rect(x+7,y+20,x+16,y+28,blue);
    } else { /* Brock's first rock-type opponent. */
        battle_rect(x-22,y+4,x+21,y+24,rock);
        battle_rect(x-11,y-14,x+13,y+7,RGBA32(167,159,147,255));
        battle_rect(x-27,y+13,x-17,y+23,rock);
        battle_rect(x+18,y+13,x+28,y+23,rock);
    }
    if(!back)battle_rect(x+3,y-10,x+6,y-7,RGBA32(30,35,44,255));
    rdpq_set_mode_standard();
}
#endif
