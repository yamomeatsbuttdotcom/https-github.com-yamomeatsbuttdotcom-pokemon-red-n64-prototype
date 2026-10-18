#include <libdragon.h>
#include <stdio.h>

/*
 * Early narrative interaction prototype.
 * Console-only: NOT the planned 3D adventure or battle engine.
 */
typedef enum {
    SCENE_PALLET, SCENE_LAB, SCENE_RIVAL, SCENE_ROUTE1,
    SCENE_VIRIDIAN, SCENE_FOREST, SCENE_PEWTER,
    SCENE_BROCK, SCENE_ROUTE3, SCENE_MT_MOON
} scene_t;

static const char *scene_names[] = {
    "PALLET TOWN", "PROF. OAK'S LAB", "RIVAL CHALLENGE",
    "ROUTE 1", "VIRIDIAN CITY", "VIRIDIAN FOREST",
    "PEWTER CITY", "BROCK'S GYM", "ROUTE 3", "MT. MOON"
};
static const char *starter_names[] = {"BULBASAUR", "CHARMANDER", "SQUIRTLE"};

static void show_scene(scene_t scene, int starter) {
    console_clear();
    printf("PALLET TO MT. MOON\n");
    printf("--------------------------\n");
    printf("%s\n\n", scene_names[scene]);
    if (scene == SCENE_PALLET) {
        printf("Your adventure begins!\n");
        printf("Press A to visit Oak's Lab.\n");
    } else if (scene == SCENE_LAB) {
        printf("Choose your first partner:\n");
        printf("D-PAD LEFT/RIGHT changes\n");
        printf("A confirms your choice.\n\n");
        printf("> %s\n", starter_names[starter]);
    } else if (scene == SCENE_RIVAL) {
        printf("Your rival challenges you!\n");
        printf("A: Continue (battle stub)\n");
    } else if (scene == SCENE_BROCK) {
        printf("BROCK: Pewter Gym Leader\n");
        printf("A: Win demo battle (stub)\n");
    } else if (scene == SCENE_MT_MOON) {
        printf("The cave entrance is blocked.\n");
        printf("END OF PROTOTYPE ROUTE.\n");
        printf("START: Restart adventure.\n");
    } else {
        printf("A: Travel onward\n");
        printf("B: Return to Pallet Town\n");
    }
}

int main(void) {
    scene_t scene = SCENE_PALLET;
    int starter = 0;
    console_init();
    controller_init();
    show_scene(scene, starter);
    while (1) {
        controller_scan();
        struct controller_data keys = get_keys_down();
        if (keys.c[0].start) {
            scene = SCENE_PALLET;
            starter = 0;
            show_scene(scene, starter);
        } else if (scene == SCENE_LAB && (keys.c[0].left || keys.c[0].right)) {
            starter = (starter + (keys.c[0].right ? 1 : 2)) % 3;
            show_scene(scene, starter);
        } else if (keys.c[0].a && scene != SCENE_MT_MOON) {
            scene = (scene_t)(scene + 1);
            show_scene(scene, starter);
        } else if (keys.c[0].b && scene != SCENE_PALLET) {
            scene = SCENE_PALLET;
            show_scene(scene, starter);
        }
    }
    return 0;
}
