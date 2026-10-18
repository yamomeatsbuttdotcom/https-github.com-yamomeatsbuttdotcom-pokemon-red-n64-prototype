#ifndef WORLD_SIGNS_H
#define WORLD_SIGNS_H
#include "world3d.h"
static void world_sign(float x,float z,float cx,float cz){
 iso_box(x,0,z,0.4f,1.8f,0.4f,cx,cz,RGBA32(119,85,52,255),RGBA32(105,71,43,255),RGBA32(89,62,38,255));
 iso_box(x-0.6f,1.7f,z-0.2f,1.6f,1.0f,0.6f,cx,cz,RGBA32(202,173,102,255),RGBA32(186,151,86,255),RGBA32(153,120,69,255));
}
#endif
