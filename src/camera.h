#ifndef CAMERA_H
#define CAMERA_H
typedef struct {float x,z;} camera_t;
static void camera_follow(camera_t *c,float x,float z){c->x+=(x-c->x)*0.12f;c->z+=(z-c->z)*0.12f;}
static void camera_snap(camera_t *c,float x,float z){c->x=x;c->z=z;}
#endif
