#ifndef END_VISUALS_H
#define END_VISUALS_H
#include <libdragon.h>
static void moon_gate_draw(void) {
 rdpq_set_mode_fill(RGBA32(105,128,157,255));
 rdpq_fill_rectangle(0,49,320,184);
 rdpq_set_mode_fill(RGBA32(113,104,94,255));
 rdpq_fill_rectangle(34,76,286,185);
 rdpq_set_mode_fill(RGBA32(67,65,74,255));
 rdpq_fill_rectangle(102,100,218,185);
 rdpq_set_mode_fill(RGBA32(164,136,100,255));
 rdpq_fill_rectangle(81,134,239,150);
 rdpq_fill_rectangle(81,162,239,178);
 rdpq_set_mode_fill(RGBA32(188,158,119,255));
 rdpq_fill_rectangle(106,120,124,184);
 rdpq_fill_rectangle(196,120,214,184);
 rdpq_set_mode_standard();
}
#endif
