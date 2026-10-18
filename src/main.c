#include <libdragon.h>
#include <stdio.h>

int main(void) {
    console_init();
    controller_init();
    printf("PALLET TO MT. MOON\n");
    printf("N64 BOOT TEST\n\n");
    printf("Press START or D-pad.\n");
    while (1) {
        controller_scan();
        struct controller_data keys = get_keys_down();
        if (keys.c[0].start) printf("START pressed!\n");
        if (keys.c[0].up) printf("UP\n");
        if (keys.c[0].down) printf("DOWN\n");
        if (keys.c[0].left) printf("LEFT\n");
        if (keys.c[0].right) printf("RIGHT\n");
    }
    return 0;
}
