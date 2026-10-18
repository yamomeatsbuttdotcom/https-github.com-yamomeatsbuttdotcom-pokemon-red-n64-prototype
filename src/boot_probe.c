#include <libdragon.h>

/* Minimal hardware/emulator smoke test, independent of world rendering. */
int main(void) {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    while (1) {
        surface_t *frame = display_get();
        rdpq_attach(frame, NULL);
        rdpq_clear(RGBA32(20, 100, 50, 255));
        rdpq_detach_show();
    }
}
