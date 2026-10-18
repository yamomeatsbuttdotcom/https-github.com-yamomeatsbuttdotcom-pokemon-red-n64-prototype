#include <libdragon.h>
#include <stdio.h>
#include "world3d.h"

/* Playable navigation mockup. Scenes and battles are placeholders. */
static const char *scenes[] = {
    "PALLET TOWN", "OAK'S LAB", "RIVAL BATTLE", "ROUTE 1",
    "VIRIDIAN CITY", "VIRIDIAN FOREST", "PEWTER CITY",
    "BROCK'S GYM", "ROUTE 3", "MT. MOON"
};
static const char *starters[] = {"BULBASAUR", "CHARMANDER", "SQUIRTLE"};
#define NUM_SCENES 10

int main(void) {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    joypad_init();
    rdpq_text_register_font(1, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_VAR));
    int scene = 0, starter = 0;
    int px = 154, py = 130;
    int wins = 0;
    while (1) {
        joypad_poll();
        joypad_buttons_t pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        if (pressed.start) { scene = 0; starter = 0; px = 154; py = 130; wins = 0; }
        joypad_buttons_t held = joypad_get_buttons_held(JOYPAD_PORT_1);
        if (scene != 1) {
            if (held.d_left) px -= 2;
            if (held.d_right) px += 2;
            if (held.d_up) py -= 2;
            if (held.d_down) py += 2;
        }
        if (px < 12) px = 12;
        if (px > 300) px = 300;
        if (py < 92) py = 92;
        if (py > 166) py = 166;
        if (scene == 1 && pressed.d_left) starter = (starter + 2) % 3;
        if (scene == 1 && pressed.d_right) starter = (starter + 1) % 3;
        if (pressed.a && scene < NUM_SCENES - 1) {
            if (scene == 2 || scene == 7) wins++;
            scene++;
            px = 154;
            py = 130;
        }
        if (pressed.b && scene > 0) scene--;

        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);
        rdpq_clear((color_t){15, 28, 52, 255});
        if (scene != 1 && scene != 2 && scene != 7 && scene != 9) {
            float camx = (px - 154) * 0.06f;
            float camz = (py - 130) * 0.06f;
            world3d_draw(scene, camx, camz);
        }
        rdpq_text_print(NULL, 1, 16, 24, "PALLET TO MT. MOON");
        rdpq_text_print(NULL, 1, 16, 56, scenes[scene]);
        if (scene == 0)
            rdpq_text_print(NULL, 1, 16, 76, "Your adventure begins.");
        else if (scene == 1) {
            rdpq_text_print(NULL, 1, 16, 88, "Choose your starter:");
            rdpq_text_print(NULL, 1, 16, 112, starters[starter]);
            rdpq_text_print(NULL, 1, 16, 136, "D-Pad: Change starter");
        } else if (scene == 2)
            rdpq_text_print(NULL, 1, 16, 88, "Rival battle (placeholder)");
        else if (scene == 7)
            rdpq_text_print(NULL, 1, 16, 88, "Brock battle (placeholder)");
        else if (scene == 9) {
            rdpq_text_print(NULL, 1, 16, 88, "Cave blocked. Demo ends.");
            if (wins == 2)
                rdpq_text_print(NULL, 1, 16, 112, "Rival + Brock cleared!");
        }
        else
            rdpq_text_print(NULL, 1, 16, 76, "Explore onward!");
        rdpq_text_print(NULL, 1, 16, 190, "A: Next   B: Back");
        rdpq_text_print(NULL, 1, 16, 207, "D-Pad: Move / Choose");
        rdpq_text_print(NULL, 1, 16, 225, "START: Restart");
        rdpq_detach_show();
    }
}
