#ifndef WORLD3D_H
#define WORLD3D_H
#include <libdragon.h>

/* First genuine 3D geometry pass: isometric projection of world-space cuboids.
   Geometry is rendered as N64 RDP filled triangles, not flat screen rectangles. */
typedef struct { float x, y; } screen_point_t;
static screen_point_t iso_project(float x, float y, float z, float camx, float camz) {
    screen_point_t p = {
        160.0f + (x - camx - z + camz) * 8.0f,
        115.0f + (x - camx + z - camz) * 3.8f - y * 9.0f
    };
    return p;
}
static void iso_quad(screen_point_t a, screen_point_t b, screen_point_t c, screen_point_t d, color_t color) {
    float va[2] = {a.x,a.y}, vb[2] = {b.x,b.y};
    float vc[2] = {c.x,c.y}, vd[2] = {d.x,d.y};
    rdpq_set_prim_color(color);
    rdpq_triangle(&TRIFMT_FILL, va, vb, vc);
    rdpq_triangle(&TRIFMT_FILL, va, vc, vd);
}
static void iso_box(float x,float y,float z,float w,float h,float d,
                    float cx,float cz,color_t top,color_t front,color_t side) {
    screen_point_t a=iso_project(x,y+h,z,cx,cz);
    screen_point_t b=iso_project(x+w,y+h,z,cx,cz);
    screen_point_t c=iso_project(x+w,y+h,z+d,cx,cz);
    screen_point_t e=iso_project(x,y+h,z+d,cx,cz);
    screen_point_t f=iso_project(x+w,y,z,cx,cz);
    screen_point_t g=iso_project(x+w,y,z+d,cx,cz);
    screen_point_t i=iso_project(x,y,z+d,cx,cz);
    iso_quad(b,c,g,f,front);
    iso_quad(e,c,g,i,side);
    iso_quad(a,b,c,e,top);
}
static void world3d_draw(int scene, float cx, float cz) {
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    /* World-space grassy platform and raised road. */
    iso_box(-12,-1,-12,24,1,24,cx,cz,
            RGBA32(69,153,76,255),RGBA32(46,100,49,255),RGBA32(36,83,43,255));
    iso_box(-2,0,-12,4,0.05f,24,cx,cz,
            RGBA32(199,176,118,255),RGBA32(153,127,85,255),RGBA32(158,132,89,255));
    /* Landmark geometry varies between towns, forests and gym. */
    if (scene == 5) {
        iso_box(-8,0,-6,2,4,2,cx,cz,RGBA32(36,105,47,255),RGBA32(26,82,36,255),RGBA32(30,90,40,255));
        iso_box(6,0,3,2,5,2,cx,cz,RGBA32(39,117,50,255),RGBA32(29,88,37,255),RGBA32(33,95,41,255));
    } else {
        iso_box(-9,0,-5,6,4,5,cx,cz,
                RGBA32(187,71,64,255),RGBA32(234,210,167,255),RGBA32(187,165,137,255));
        iso_box(5,0,4,4,3,4,cx,cz,
                RGBA32(71,112,178,255),RGBA32(218,210,176,255),RGBA32(171,170,146,255));
    }
    /* Player represented by stacked 3D blocks until a mesh is added. */
    iso_box(cx,0,cz,0.9f,1.6f,0.9f,cx,cz,
            RGBA32(40,81,190,255),RGBA32(37,71,164,255),RGBA32(30,55,128,255));
    iso_box(cx,1.6f,cz,0.9f,0.75f,0.9f,cx,cz,
            RGBA32(56,60,69,255),RGBA32(233,190,147,255),RGBA32(201,160,122,255));
}
#endif
