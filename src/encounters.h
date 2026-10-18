#ifndef ENCOUNTERS_H
#define ENCOUNTERS_H
/* Deterministic encounters for an N64 prototype; no random dependency. */
typedef struct { const char *name; int level; int hp; } encounter_t;
static encounter_t area_encounter(int scene, int step) {
    static const encounter_t route1[] = {{"PIDGEY",3,11},{"RATTATA",4,13}};
    static const encounter_t forest[] = {{"CATERPIE",4,12},{"WEEDLE",5,14}};
    static const encounter_t route3[] = {{"SPEAROW",6,17},{"JIGGLYPUFF",5,16}};
    int idx = (step / 32) % 2;
    if (scene == 5) return forest[idx];
    if (scene == 8) return route3[idx];
    return route1[idx];
}
#endif
