#ifndef BATTLE_RULES_H
#define BATTLE_RULES_H
/* Simplified deterministic battle stats for the early playable demo. */
typedef struct { int hp; int attack; int defense; } battle_stats_t;
static battle_stats_t starter_stats(int starter) {
    static const battle_stats_t stats[3] = {{26,6,5},{23,8,3},{28,5,7}};
    return stats[(starter >= 0 && starter < 3) ? starter : 0];
}
static battle_stats_t enemy_stats(int gym) {
    battle_stats_t rival = {18,5,3};
    battle_stats_t brock = {30,7,6};
    return gym ? brock : rival;
}
static int battle_damage(int attack, int defense) {
    int amount = attack - defense / 2;
    return amount > 1 ? amount : 1;
}
#endif
