#ifndef WORLD_COLLISION_H
#define WORLD_COLLISION_H
/* Geometry-aligned collision checks for world-space obstacles. */
static int collision_box(float x,float z,float bx,float bz,float w,float d,float margin) {
 return x>bx-margin && x<bx+w+margin && z>bz-margin && z<bz+d+margin;
}
static int world_blocked(int scene,float x,float z) {
 if (scene==0 || scene==4 || scene==6) {
   if (collision_box(x,z,-9,-5,6,5,0.45f)) return 1;
   if (collision_box(x,z,5,4,4,4,0.45f)) return 1;
   if (scene==4 && collision_box(x,z,5,-7,4,4,0.45f)) return 1;
 }
 if (scene==5) {
   for(int i=0;i<5;i++){
     float tz=-9.0f+i*4.0f,tx=(i&1)?6.0f:-8.0f;
     if(collision_box(x,z,tx-1.0f,tz-1.0f,3.0f,3.0f,0.35f))return 1;
   }
 }
 if(scene==3 || scene==8) {
   for(int i=0;i<4;i++){
     float tz=-8.0f+i*5.0f;
     if(collision_box(x,z,-7,tz,2,2,0.3f))return 1;
     if(collision_box(x,z,6,tz+2,2,2,0.3f))return 1;
   }
   if(scene==8 && collision_box(x,z,7,-7,3,3,0.3f))return 1;
 }
 return 0;
}
#endif
