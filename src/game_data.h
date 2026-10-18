#ifndef GAME_DATA_H
#define GAME_DATA_H
typedef struct { const char *name; int max_hp; int power; int defense; } species_t;
static const species_t species[] = {
    {"BULBASAUR",27,7,4}, {"CHARMANDER",23,9,2}, {"SQUIRTLE",29,6,5},
    {"PIDGEY",16,5,2}, {"RATTATA",18,6,2}, {"GEODUDE",23,7,5}, {"ONIX",35,8,6}
};
enum { BULBASAUR, CHARMANDER, SQUIRTLE, PIDGEY, RATTATA, GEODUDE, ONIX };
static int rival_species(int starter) { return (starter + 1) % 3; }
static int clamp_hp(int hp) { return hp < 0 ? 0 : hp; }
#endif
