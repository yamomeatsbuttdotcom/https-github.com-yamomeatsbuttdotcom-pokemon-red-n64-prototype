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
/* Readable landmark details inspired by the approved N64 visual reference.
   All decoration is authored as small world-space polygon meshes. */
static void iso_house_details(float x,float z,float w,float d,float h,
                              float cx,float cz,color_t roof) {
    /* Eaves, chimney, front door, and blue glass window panels. */
    iso_box(x-0.3f,h,z-0.3f,w+0.6f,0.65f,d+0.6f,cx,cz,
            roof,roof,RGBA32(103,61,62,255));
    iso_box(x+w*0.20f,0,z+d,1.1f,2.1f,0.10f,cx,cz,
            RGBA32(72,56,45,255),RGBA32(89,66,49,255),RGBA32(62,46,37,255));
    iso_box(x+w*0.64f,2.0f,z+d,1.0f,1.05f,0.12f,cx,cz,
            RGBA32(111,170,211,255),RGBA32(105,172,217,255),RGBA32(70,117,168,255));
    iso_box(x+w*0.74f,h+0.65f,z+0.5f,0.7f,0.8f,0.7f,cx,cz,
            RGBA32(132,117,104,255),RGBA32(153,138,124,255),RGBA32(113,98,89,255));
}
static void iso_flower(float x,float z,float cx,float cz) {
    iso_box(x,0,z,0.45f,0.25f,0.45f,cx,cz,
            RGBA32(240,194,66,255),RGBA32(219,156,51,255),RGBA32(198,143,49,255));
}
static void world3d_draw(int scene, float px, float pz, float cx, float cz) {
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    /* World-space grassy platform and raised road. */
    iso_box(-12,-1,-12,24,1,24,cx,cz,
            RGBA32(69,153,76,255),RGBA32(46,100,49,255),RGBA32(36,83,43,255));
    iso_box(-2,0,-12,4,0.05f,24,cx,cz,
            RGBA32(199,176,118,255),RGBA32(153,127,85,255),RGBA32(158,132,89,255));
    /* Each chapter gets its own landmark geometry. */
    if (scene == 5) { /* Viridian Forest: staggered trees */
        for (int i=0; i<5; i++) {
            float tz = -9.0f + i*4.0f;
            float tx = (i&1) ? 6.0f : -8.0f;
            iso_box(tx,0,tz,1.0f,3.0f,1.0f,cx,cz,
                    RGBA32(111,79,45,255),RGBA32(101,69,39,255),RGBA32(79,54,34,255));
            iso_box(tx-1.0f,3.0f,tz-1.0f,3.0f,2.5f,3.0f,cx,cz,
                    RGBA32(43,131,53,255),RGBA32(33,99,44,255),RGBA32(29,84,39,255));
        }
    } else if (scene == 6) { /* Pewter: stone gym */
        iso_box(-9,0,-6,7,5,6,cx,cz,
                RGBA32(116,126,132,255),RGBA32(172,170,155,255),RGBA32(134,137,136,255));
        iso_box(-6,0,0,2,2,0.5f,cx,cz,
                RGBA32(79,79,89,255),RGBA32(64,65,75,255),RGBA32(59,61,71,255));
        iso_box(6,0,3,3,2,3,cx,cz,
                RGBA32(113,109,102,255),RGBA32(152,146,131,255),RGBA32(122,117,107,255));
    } else if (scene == 3 || scene == 8) { /* Route 1 and Route 3 */
        for (int i=0;i<4;i++) {
            float tz = -8.0f + i*5.0f;
            iso_box(-7,0,tz,2,1.0f,2,cx,cz,
                    RGBA32(42,130,52,255),RGBA32(32,100,42,255),RGBA32(28,88,38,255));
            iso_box(6,0,tz+2,2,1.0f,2,cx,cz,
                    RGBA32(42,130,52,255),RGBA32(32,100,42,255),RGBA32(28,88,38,255));
        }
        if (scene == 8)
            iso_box(7,0,-7,3,3,3,cx,cz,
                    RGBA32(133,119,101,255),RGBA32(112,100,87,255),RGBA32(95,86,77,255));
    } else if (scene == 4) { /* Viridian City */
        iso_box(-9,0,-5,6,4,5,cx,cz,
                RGBA32(189,69,73,255),RGBA32(228,211,182,255),RGBA32(188,167,146,255));
        iso_box(5,0,4,4,3,4,cx,cz,
                RGBA32(74,112,181,255),RGBA32(218,210,176,255),RGBA32(171,170,146,255));
        iso_box(5,0,-7,4,4,4,cx,cz,
                RGBA32(209,80,87,255),RGBA32(229,218,199,255),RGBA32(181,175,155,255));
    } else { /* Pallet Town */
        iso_box(-9,0,-5,6,4,5,cx,cz,
                RGBA32(187,71,64,255),RGBA32(234,210,167,255),RGBA32(187,165,137,255));
        iso_box(5,0,4,4,3,4,cx,cz,
                RGBA32(71,112,178,255),RGBA32(218,210,176,255),RGBA32(171,170,146,255));
    }
    /* Roofs and window details for houses and city landmarks. */
    if (scene == 0 || scene == 4) {
        iso_house_details(-9,-5,6,5,4,cx,cz,RGBA32(188,66,59,255));
        iso_house_details(5,4,4,4,3,cx,cz,RGBA32(72,115,189,255));
    }
    if (scene == 4)
        iso_house_details(5,-7,4,4,4,cx,cz,RGBA32(204,72,82,255));
    /* Bright wildflowers on the edge of the path. */
    if (scene == 0 || scene == 3 || scene == 4 || scene == 8) {
        for (int i=0;i<4;i++) {
            iso_flower(-3.2f, -8.0f + i*5.0f,cx,cz);
            iso_flower(3.1f, -6.0f + i*4.0f,cx,cz);
        }
    }
    /* Trainer: separate boots, legs, red jacket, arms, face, cap and backpack.
       The parts are small cuboid meshes, intended for low-poly N64 styling. */
    const color_t denim = RGBA32(45,76,156,255);
    const color_t skin = RGBA32(235,184,137,255);
    const color_t red = RGBA32(207,50,51,255);
    const color_t yellow = RGBA32(220,177,61,255);
    iso_box(px-0.10f,0,pz+0.05f,0.42f,0.30f,0.36f,cx,cz,
            RGBA32(71,56,49,255),RGBA32(62,49,42,255),RGBA32(55,44,40,255));
    iso_box(px+0.48f,0,pz+0.05f,0.42f,0.30f,0.36f,cx,cz,
            RGBA32(71,56,49,255),RGBA32(62,49,42,255),RGBA32(55,44,40,255));
    iso_box(px,0.28f,pz,0.36f,0.78f,0.55f,cx,cz,denim,denim,RGBA32(37,61,130,255));
    iso_box(px+0.52f,0.28f,pz,0.36f,0.78f,0.55f,cx,cz,denim,denim,RGBA32(37,61,130,255));
    iso_box(px-0.02f,1.05f,pz-0.04f,0.95f,0.95f,0.65f,cx,cz,
            red,red,RGBA32(153,36,39,255));
    iso_box(px-0.31f,1.09f,pz,0.28f,0.84f,0.46f,cx,cz,
            red,red,RGBA32(148,34,37,255));
    iso_box(px+0.94f,1.09f,pz,0.28f,0.84f,0.46f,cx,cz,
            red,red,RGBA32(148,34,37,255));
    iso_box(px-0.30f,1.01f,pz,0.26f,0.23f,0.45f,cx,cz,skin,skin,skin);
    iso_box(px+0.94f,1.01f,pz,0.26f,0.23f,0.45f,cx,cz,skin,skin,skin);
    iso_box(px+0.06f,1.96f,pz,0.78f,0.80f,0.68f,cx,cz,
            skin,skin,RGBA32(199,145,105,255));
    iso_box(px,2.64f,pz-0.06f,0.93f,0.29f,0.83f,cx,cz,
            red,red,RGBA32(143,33,39,255));
    iso_box(px-0.10f,2.64f,pz+0.64f,1.13f,0.12f,0.37f,cx,cz,
            red,red,RGBA32(143,33,39,255));
    iso_box(px+0.12f,1.15f,pz-0.43f,0.67f,0.78f,0.43f,cx,cz,
            yellow,yellow,RGBA32(166,122,37,255));
}
#endif
