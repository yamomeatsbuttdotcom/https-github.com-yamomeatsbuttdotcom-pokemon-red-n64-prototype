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
#include "battle_visuals.h"
#include "lab_visuals.h"
#include "end_visuals.h"
#include "encounters.h"

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
    int battle_choice = 0, potions = 3, special_pp = 5;
    int show_hint = 0, walk_steps = 0, area_steps = 0;
    int wild_active = 0, wild_hp = 0, wild_max_hp = 0, wild_wins = 0;
    int last_wild_result = 0, result_frames = 0;
    int trainer_message = 0;
    encounter_t wild_foe = {"PIDGEY", 3, 11};
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
            battle_choice = 0; potions = 3; special_pp = 5; show_hint = 0; walk_steps = 0; area_steps = 0; wild_active = 0; wild_wins = 0; last_wild_result = 0; result_frames = 0; trainer_message = 0;
            reset_position(&x, &z);
            camera_snap(&cam, x, z);
        }
        if (!p.start && game_is_world(place) && !wild_active) {
            if (p.b) show_hint = !show_hint;
            if ((place == VIRIDIAN || place == PEWTER) && p.c_up) {
                hp = starter_stats(starter).hp;
                special_pp = 5;
                last_wild_result = 4; result_frames = 120;
            }
            float nx = x, nz = z;
            if (h.d_left) nx -= 0.15f;
            if (h.d_right) nx += 0.15f;
            if (h.d_up) nz -= 0.15f;
            if (h.d_down) nz += 0.15f;
            if (nx < -10) nx = -10;
            if (nx > 10) nx = 10;
            if (nz < -10) nz = -10;
            if (nz > 10) nz = 10;
            if (!world_blocked(place, nx, nz)) {
                if (nx != x || nz != z) {
                    walk_steps++;
                    area_steps++;
                    if ((place == ROUTE1 || place == FOREST || place == ROUTE3)
                        && area_steps >= 65) {
                        area_steps = 0;
                        wild_foe = area_encounter(place, walk_steps);
                        wild_hp = wild_foe.hp; wild_max_hp = wild_hp;
                        wild_active = 1;
                        battle_choice = 0; battle_turn = 0;
                    }
                }
                x = nx; z = nz;
            }
            /* Walk to the north end of the path, then interact to advance. */
            if (!wild_active && p.a && z < -7.0f) {
                place = game_next_place(place, badge);
                area_steps = 0;
                reset_position(&x, &z);
                camera_snap(&cam, x, z);
                if (game_is_battle(place)) {
                    if (hp < 1) hp = starter_stats(starter).hp;
                    enemy_hp = enemy_stats(place == BROCK).hp;
                    battle_turn = 0; battle_finished = 0; battle_choice = 0; special_pp = 5; trainer_message = 0;
                }
            }
        } else if (!p.start && wild_active) {
            if (p.b) {
                wild_active = 0;
                last_wild_result = 2; result_frames = 90;
            } else if (p.a) {
                wild_hp -= battle_damage(starter_stats(starter).attack, 2);
                if (wild_hp <= 0) {
                    wild_hp = 0;
                    wild_active = 0;
                    wild_wins++;
                    last_wild_result = 1; result_frames = 90;
                } else {
                    hp -= battle_damage(4 + wild_foe.level / 2,
                                        starter_stats(starter).defense);
                    if (hp <= 0) {
                        hp = starter_stats(starter).hp;
                        wild_active = 0;
                        last_wild_result = 3; result_frames = 120;
                        reset_position(&x, &z);
                        camera_snap(&cam, x, z);
                    }
                }
            }
        } else if (!p.start && place == 1) {
            if (p.d_left) starter = (starter + 2) % 3;
            if (p.d_right) starter = (starter + 1) % 3;
            if (p.a) {
                place = RIVAL; hp = starter_stats(starter).hp; enemy_hp = enemy_stats(0).hp;
                battle_turn = 0; battle_finished = 0; battle_choice = 0; special_pp = 5;
            }
        } else if (!p.start && game_is_battle(place)) {
            if (!battle_finished) {
                if (p.d_left || p.d_up) battle_choice = (battle_choice + 2) % 3;
                if (p.d_right || p.d_down) battle_choice = (battle_choice + 1) % 3;
            }
            if (p.a) {
                if (battle_finished) {
                    if (hp > 0) {
                        if (place == RIVAL) rival_won = 1;
                        if (place == BROCK) badge = 1;
                        place++; reset_position(&x, &z); camera_snap(&cam, x, z);
                    } else {
                        hp = starter_stats(starter).hp;
                        enemy_hp = enemy_stats(place == BROCK).hp;
                        battle_finished = 0; battle_turn = 0; battle_choice = 0; special_pp = 5;
                    }
                } else {
                    int used_turn = 1;
                    if (battle_choice == 2) {
                        if (potions > 0 && hp < starter_stats(starter).hp) {
                            hp += 12;
                            if (hp > starter_stats(starter).hp) hp = starter_stats(starter).hp;
                            potions--;
                            trainer_message = 3;
                        } else { used_turn = 0; trainer_message = 4; }
                    } else {
                        int damage = battle_damage(starter_stats(starter).attack,
                                                   enemy_stats(place == BROCK).defense);
                        if (battle_choice == 1) {
                            if (special_pp > 0) { damage += 2; special_pp--; trainer_message = 2; }
                            else { used_turn = 0; trainer_message = 5; }
                        }
                        if (used_turn) {
                            enemy_hp -= damage;
                            if (battle_choice == 0) trainer_message = 1;
                        }
                        if (enemy_hp <= 0) { enemy_hp = 0; battle_finished = 1; }
                    }
                    if (used_turn) {
                        battle_turn++;
                        if (!battle_finished) {
                            hp -= battle_damage(enemy_stats(place == BROCK).attack,
                                                starter_stats(starter).defense);
                            if (hp <= 0) { hp = 0; battle_finished = 1; }
                        }
                    }
                }
            }
        }
        if (result_frames > 0) result_frames--;
        camera_follow(&cam,x,z);
        surface_t *disp = display_get();
        rdpq_attach(disp, NULL);
        rdpq_clear(RGBA32(23, 38, 62, 255));
        if (game_is_world(place) && !wild_active) world3d_draw(place, x, z, cam.x, cam.z);
        rdpq_set_mode_standard();
        if (place == 1) lab_draw(starter);
        if (place == 9) moon_gate_draw();
        rdpq_text_print(NULL, 1, 12, 18, "PALLET TO MT. MOON");
        rdpq_text_print(NULL, 1, 12, 37, places[place]);
        if (wild_active) {
            battle_creature(75,91,starter,1);
            battle_wild_creature(251,80,wild_foe.name);
            snprintf(line,sizeof(line),"WILD %s Lv.%d",wild_foe.name,wild_foe.level);
            rdpq_text_print(NULL,1,12,65,line);
            snprintf(line,sizeof(line),"YOUR HP %d / %d",hp,starter_stats(starter).hp);
            rdpq_text_print(NULL,1,12,121,line);
            ui_meter(12,137,138,hp,starter_stats(starter).hp,RGBA32(84,205,94,255));
            ui_meter(166,137,138,wild_hp,wild_max_hp,RGBA32(220,117,72,255));
            snprintf(line,sizeof(line),"FOE HP %d / %d",wild_hp,wild_max_hp);
            rdpq_text_print(NULL,1,166,121,line);
            rdpq_text_print(NULL,1,12,161,"A: ATTACK  B: RUN");
        } else if (game_is_world(place)) {
            rdpq_text_print(NULL, 1, 12, 58, area_greeting[place]);
            if (place == 6 && !badge)
                rdpq_text_print(NULL, 1, 12, 75, "Find Brock's gym!");
            if (place == VIRIDIAN || place == PEWTER)
                rdpq_text_print(NULL, 1, 12, 176, "C-UP: HEAL TEAM");
            if (place == 8 && badge)
                rdpq_text_print(NULL, 1, 12, 75, "Mt. Moon is just ahead.");
            if (show_hint) rdpq_text_print(NULL, 1, 12, 92, area_hint[place]);
            rdpq_text_print(NULL, 1, 12, 192, "D-Pad: Walk");
            rdpq_text_print(NULL, 1, 12, 207, "North + A: Next  B: Hint");
            if (result_frames > 0) {
                const char *outcomes[] = {"", "WILD POKEMON DEFEATED!", "GOT AWAY SAFELY!", "FAINTED! RESTORED HP.", "TEAM RESTED AT POKE CENTER!"};
                rdpq_text_print(NULL, 1, 12, 111, outcomes[last_wild_result]);
            }
            snprintf(line, sizeof(line), "WILD WINS: %d", wild_wins);
            rdpq_text_print(NULL, 1, 204, 58, line);
        } else if (place == 1) {
            rdpq_text_print(NULL, 1, 12, 82, "Professor: Choose a partner!");
            rdpq_text_print(NULL, 1, 12, 109, starters[starter]);
            rdpq_text_print(NULL, 1, 12, 192, "LEFT/RIGHT: Choose");
            rdpq_text_print(NULL, 1, 12, 207, "A: Confirm");
        } else if (game_is_battle(place)) {
            battle_creature(75,91,starter,1);
            battle_creature(251,80,place==7?3:(starter+1)%3,0);
            rdpq_text_print(NULL, 1, 12, 65, opponents[place == 2 ? 0 : 1]);
            snprintf(line, sizeof(line), "YOUR %s HP: %d", starters[starter], hp);
            rdpq_text_print(NULL, 1, 12, 121, line);
            snprintf(line, sizeof(line), "FOE HP: %d", enemy_hp);
            rdpq_text_print(NULL, 1, 166, 121, line);
            ui_meter(12, 137, 138, hp, starter_stats(starter).hp, RGBA32(84,205,94,255));
            ui_meter(166, 137, 138, enemy_hp, enemy_stats(place == BROCK).hp, RGBA32(220,117,72,255));
            if (battle_finished)
                rdpq_text_print(NULL, 1, 12, 160, hp ? "YOU WIN! A: CONTINUE" : "FAINTED! A: RETRY");
            else
            {
                const char *actions[] = {"ATTACK", "SPECIAL", "POTION"};
                snprintf(line, sizeof(line), "< %s >  A: SELECT", actions[battle_choice]);
                rdpq_text_print(NULL, 1, 12, 160, line);
                snprintf(line, sizeof(line), "POTION %d  SPECIAL PP %d", potions, special_pp);
                rdpq_text_print(NULL, 1, 12, 177, line);
                const char *battle_messages[] = {"CHOOSE YOUR MOVE", "A SOLID HIT!", "SPECIAL ATTACK!", "POTION RESTORED HP!", "CANNOT USE POTION", "NO SPECIAL PP LEFT"};
                rdpq_text_print(NULL, 1, 12, 194, battle_messages[trainer_message]);
            }
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
