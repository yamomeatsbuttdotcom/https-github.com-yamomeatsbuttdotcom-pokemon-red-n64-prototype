#ifndef GAME_RULES_H
#define GAME_RULES_H
/* Centralized game progression rules; pure C, independently testable. */
enum { PALLET=0, LAB=1, RIVAL=2, ROUTE1=3, VIRIDIAN=4, FOREST=5, PEWTER=6, BROCK=7, ROUTE3=8, MOON=9 };
static int game_is_battle(int place) { return place == RIVAL || place == BROCK; }
static int game_is_world(int place) { return place >= PALLET && place <= ROUTE3 && place != LAB && !game_is_battle(place); }
static int game_next_place(int place, int badge) {
    if (place == PALLET) return LAB;
    if (place == PEWTER) return badge ? ROUTE3 : BROCK;
    if (place == ROUTE3) return badge ? MOON : ROUTE3;
    if (place < PALLET) return PALLET;
    if (place >= MOON) return MOON;
    return place + 1;
}
#endif
