#ifndef PROGRESSION_H
#define PROGRESSION_H
enum { AREA_PALLET, AREA_LAB, AREA_RIVAL, AREA_ROUTE1, AREA_VIRIDIAN, AREA_FOREST, AREA_PEWTER, AREA_GYM, AREA_ROUTE3, AREA_MOON };
typedef struct { int starter, rival_defeated, boulder_badge, potions, encounters; } game_progress_t;
static int next_area(int area,const game_progress_t *p) {
 if(area==AREA_PALLET)return AREA_LAB;
 if(area==AREA_LAB)return AREA_RIVAL;
 if(area==AREA_RIVAL)return p->rival_defeated?AREA_ROUTE1:AREA_RIVAL;
 if(area==AREA_PEWTER||area==AREA_GYM)return p->boulder_badge?AREA_ROUTE3:AREA_GYM;
 if(area==AREA_ROUTE3)return p->boulder_badge?AREA_MOON:AREA_ROUTE3;
 return area<AREA_MOON?area+1:AREA_MOON;
}
#endif
