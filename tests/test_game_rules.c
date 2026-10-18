#include <assert.h>
#include "../src/game_rules.h"
#include "../src/battle_rules.h"
#include "../src/encounters.h"
#include "../src/world_collision.h"
#include "../src/progression.h"
int main(void) {
    assert(game_next_place(PALLET,0)==LAB);
    assert(game_next_place(PEWTER,0)==BROCK);
    assert(game_next_place(PEWTER,1)==ROUTE3);
    assert(game_next_place(ROUTE3,1)==MOON);
    assert(game_next_place(ROUTE3,0)==ROUTE3);
    assert(game_is_world(FOREST));
    assert(!game_is_world(-1));
    assert(!game_is_world(99));
    assert(game_next_place(-1,0)==PALLET);
    assert(!game_is_world(BROCK));
    assert(starter_stats(1).attack>starter_stats(2).attack);
    assert(battle_damage(1,100)==1);
    assert(area_encounter(FOREST,0).level==4);
    assert(area_encounter(FOREST,65).level==5);
    assert(area_encounter(ROUTE3,65).level==5);
    assert(area_encounter(ROUTE1,-1).level==3);
    assert(world_blocked(PALLET,-6,-3));
    assert(world_blocked(PALLET,11,0));
    assert(world_blocked(PALLET,0,-11));
    assert(!world_blocked(ROUTE1,0,-8));
    assert(!world_blocked(FOREST,0,-8));
    assert(!world_blocked(PALLET,0,5));
    assert(world_blocked(FOREST,-8,-9));
    game_progress_t progress = {0};
    assert(next_area(AREA_PEWTER,&progress)==AREA_GYM);
    progress.boulder_badge=1;
    assert(next_area(AREA_PEWTER,&progress)==AREA_ROUTE3);
    assert(next_area(AREA_ROUTE3,&progress)==AREA_MOON);
    return 0;
}
