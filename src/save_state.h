#ifndef SAVE_STATE_H
#define SAVE_STATE_H
/* Volatile checkpoint data; persistent saving not yet implemented. */
typedef struct {int area,starter,hp,rival_defeated,badge,potions;} checkpoint_t;
static checkpoint_t checkpoint_make(int a,int s,int h,int r,int b,int p){checkpoint_t c={a,s,h,r,b,p};return c;}
#endif
