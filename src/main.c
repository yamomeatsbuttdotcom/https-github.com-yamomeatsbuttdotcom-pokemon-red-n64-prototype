#include <libdragon.h>
#include <stdio.h>
#include "world3d.h"
#include "camera.h"
#include "scene_dialogue.h"
#include "ui_panels.h"
#include "game_rules.h"
#include "battle_rules.h"
#include "ui_helpers.h"
#include "world_collision.h"

/* Small original N64 adventure prototype, Pallet Town through Mt. Moon. */
static const char *places[] = {
    "PALLET TOWN", "OAK'S LAB", "RIVAL BATTLE", "ROUTE 1",
    "VIRIDIAN CITY", "VIRIDIAN FOREST", "PEWTER CITY",
    "BROCK'S GYM", "ROUTE 3", "MT. MOON GATE"
};
static const char *starters[] = {"BULBASAUR", "CHARMANDER", "SQUIRTLE"};
static const char *opponents[] = {"RIVAL", "BROCK"};

static void reset_position(float *x, float *z) { *x = 0; *z = 8; }

int main(void) {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    joypad_init();
    rdpq_text_register_font(1, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_VAR));
    int place = 0, starter = 0, hp = 26, enemy_hp = 0;
    int badge = 0, rival_won = 0, battle_turn = 0, battle_finished = 0;
    float x = 0, z = 8;
    camera_t cam = {0,8};
    char line[64];
    while (1) {
        joypad_poll();
        joypad_buttons_t p = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        joypad_buttons_t h = joypad_get_buttons_held(JOYPAD_PORT_1);
        if (p.start) {
            place = 0; starter = 0; hp = starter_stats(0).hp; enemy_hp = 0;
            badge = 0; rival_won = 0; battle_turn = 0; battle_finished = 0;
            reset_position(&x, &z);
            camera_snap(&cam, x, z);
        }
        if (game_is_world(place)) {
            float nx = x, nz = z;
            if (h.d_left) nx -= 0.15f;
            if (h.d_right) nx += 0.15f;
            if (h.d_up) nz -= 0.15f;
            if (h.d_down) nz += 0.15f;
            if (nx < -10) nx = -10;
            if (nx > 10) nx = 10;
            if (nz < -10) nz = -10;
            if (nz > 10) nz = 10;
            if (!world_blocked(place, nx, nz)) { x = nx; z = nz; }
            /* Walk to the north end of the path, then interact to advance. */
            if (p.a && z < -7.0f) {
                place = game_next_place(place, badge);
                reset_position(&x, &z);
                camera_snap(&cam, x, z);
                if (game_is_battle(place)) {
                    hp = starter_stats(starter).hp; enemy_hp = enemy_stats(place == BROCK).hp;
                    battle_turn = 0; battle_finished = 0;
                }
            }
        } else if (place == 1) {
            if (p.d_left) starter = (starter + 2) % 3;
            if (p.d_right) starter = (starter + 1) % 3;
            if (p.a) {
                place = RIVAL; hp = starter_stats(starter).hp; enemy_hp = enemy_stats(0).hp;
                battle_turn = 0; battle_finished = 0;
            }
        } else if (game_is_battle(place)) {
            if (p.a) {
                if (battle_finished) {
                    if (hp > 0) {
                        if (place == 2) rival_won = 1;
                        if (place == 7) badge = 1;
                        place++; reset_position(&x, &z); camera_snap(&cam, x, z);
                    } else {
                        hp = starter_stats(starter).hp; enemy_hp = enemy_stats(place == BROCK).hp;
                        battle_finished = 0; battle_turn = 0;
                    }
                } else {
                    enemy_hp -= battle_damage(starter_stats(starter).attack, enemy_stats(place == BROCK).defense);
                    battle_turn++;
                    if (enemy_hp <= 0) { enemy_hp = 0; battle_finished = 1; }
                    else {
                        hp -= battle_damage(enemy_stats(place == BROCK).attack, starter_stats(starter).defense);
                        if (hp <= 0) { hp = 0; battle_finished = 1; }
                    }
                }
            }
        }
        camera_follow(&cam,x,z);
        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);
        rdpq_clear(RGBA32(23, 38, 62, 255));
        if (game_is_world(place)) world3d_draw(place, cam.x, cam.z);
        rdpq_text_print(NULL, 1, 12, 18, "PALLET TO MT. MOON");
        rdpq_text_print(NULL, 1, 12, 37, places[place]);
        if (game_is_world(place)) {
            rdpq_text_print(NULL, 1, 12, 58, area_greeting[place]);
            if (place == 6 && !badge)
                rdpq_text_print(NULL, 1, 12, 75, "Find Brock's gym!");
            if (place == 8 && !badge)
                rdpq_text_print(NULL, 1, 12, 75, "Badge required.");
            ui_panel(8,178,312,216);
            rdpq_text_print(NULL, 1, 12, 192, "D-Pad: Walk");
            rdpq_text_print(NULL, 1, 12, 207, "North gate + A: Continue");
        } else if (place == 1) {
            rdpq_text_print(NULL, 1, 12, 82, "Professor: Choose a partner!");
            rdpq_text_print(NULL, 1, 12, 109, starters[starter]);
            rdpq_text_print(NULL, 1, 12, 192, "LEFT/RIGHT: Choose");
            rdpq_text_print(NULL, 1, 12, 207, "A: Confirm");
        } else if (game_is_battle(place)) {
            rdpq_text_print(NULL, 1, 12, 79, opponents[place == 2 ? 0 : 1]);
            snprintf(line, sizeof(line), "YOUR %s HP: %d", starters[starter], hp);
            rdpq_text_print(NULL, 1, 12, 105, line);
            snprintf(line, sizeof(line), "FOE HP: %d", enemy_hp);
            rdpq_text_print(NULL, 1, 12, 128, line);
            ui_meter(12, 137, 138, hp, starter_stats(starter).hp, RGBA32(84,205,94,255));
            ui_meter(166, 137, 138, enemy_hp, enemy_stats(place == BROCK).hp, RGBA32(220,117,72,255));
            ui_hp_bar(205,99,hp,24);
            ui_hp_bar(205,122,enemy_hp,place==2?18:30);
            if (battle_finished)
                rdpq_text_print(NULL, 1, 12, 160, hp ? "YOU WIN! A: CONTINUE" : "FAINTED! A: RETRY");
            else
                rdpq_text_print(NULL, 1, 12, 160, "A: ATTACK");
        } else {
            rdpq_text_print(NULL, 1, 12, 95, "MT. MOON ENTRANCE BLOCKED");
            rdpq_text_print(NULL, 1, 12, 119, "END OF PROTOTYPE");
            if (badge && rival_won)
                rdpq_text_print(NULL, 1, 12, 145, "RIVAL BEATEN / BADGE WON");
        }
        rdpq_text_print(NULL, 1, 12, 227, "START: NEW GAME");
        rdpq_detach_show();
    }
}
