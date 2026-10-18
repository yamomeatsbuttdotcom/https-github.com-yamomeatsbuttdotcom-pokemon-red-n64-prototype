#include <assert.h>
#include "../src/game_rules.h"
#include "../src/battle_rules.h"
#include "../src/encounters.h"
int main(void) {
    assert(game_next_place(PALLET,0)==LAB);
    assert(game_next_place(PEWTER,0)==BROCK);
    assert(game_next_place(PEWTER,1)==ROUTE3);
    assert(game_next_place(ROUTE3,1)==MOON);
    assert(game_next_place(ROUTE3,0)==ROUTE3);
    assert(game_is_world(FOREST));
    assert(!game_is_world(BROCK));
    assert(starter_stats(1).attack>starter_stats(2).attack);
    assert(battle_damage(1,100)==1);
    assert(area_encounter(FOREST,0).level==4);
    return 0;
}
