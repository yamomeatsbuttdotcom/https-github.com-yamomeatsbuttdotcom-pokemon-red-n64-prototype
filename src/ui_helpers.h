#ifndef UI_HELPERS_H
#define UI_HELPERS_H
#include <libdragon.h>
/* Consistent N64 UI accent bars and stat meters. */
static void ui_meter(int x,int y,int width,int value,int maximum,color_t color) {
    if (maximum < 1) maximum = 1;
    if (value < 0) value = 0;
    if (value > maximum) value = maximum;
    rdpq_set_mode_fill(RGBA32(30,39,55,255));
    rdpq_fill_rectangle(x,y,x+width,y+7);
    rdpq_set_mode_fill(color);
    rdpq_fill_rectangle(x+1,y+1,x+1+(width-2)*value/maximum,y+6);
    rdpq_set_mode_standard();
}
#endif
