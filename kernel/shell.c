#include "type.h"
#include "const.h"
#include "protect.h"
#include "memory.h"
#include "string.h"
#include "proc.h"
#include "global.h"
#include "keyboard.h"
/*
PUBLIC void run_0() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("1\n", RED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (in_byte(KB_CMD) & 1) {
            u8 scan_code = in_byte(KB_DATA);
            if (scan_code == 28) flag = 0;
        }
    }
}
PUBLIC void run_1() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("2\n", RED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (in_byte(KB_CMD) & 1) {
            u8 scan_code = in_byte(KB_DATA);
            if (scan_code == 28) flag = 0;
        }
    }
}
PUBLIC void run_2() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("3\n", RED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (in_byte(KB_CMD) & 1) {
            u8 scan_code = in_byte(KB_DATA);
            if (scan_code == 28) flag = 0;
        }
    }
}
PUBLIC void run_3() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("4\n", RED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (in_byte(KB_CMD) & 1) {
            u8 scan_code = in_byte(KB_DATA);
            if (scan_code == 28) flag = 0;
        }
    }
}
PUBLIC void shell() {
    print("\nMinux >> ", WHITE);
    char    output[2];
    output[1] = '\0';
    char    com[1000];
    int i;
    i = 0;
    while (1) {
        if (in_byte(KB_CMD) & 1) {
            output[0] = 0;
            u8 scan_code = in_byte(KB_DATA);
            u8 make = (scan_code & FLAG_BREAK ? 0 : 1);
            if (make && scan_code != 28) {
                output[0] = keymap[(scan_code & 0x7F) * MAP_COLS];
                print(output, WHITE);
                com[i] = output[0];
                i++;
            }
            if (scan_code == 28) {
                if (com[0] == 'i' && com[1] == 'n' && com[2] == 'f' && com[3] == 'o') {
                    print("\nDisk Format: ", WHITE);
                    print("FAT12\n", RED);
                    print("Disk Volume: " , WHITE);
                    print("1.44M\n", RED);
                    print("File:\n", WHITE);
                    print("\\Kernel.bin    7364byte\n", WHITE);
                    print("\\Loader.bin    5509byte\n", WHITE);
                    print("\\test.txt      20byte\n", WHITE);
                }
                for (int j = 0; j < i; j++) {
                    if (com[j] == '1') run_0();
                    if (com[j] == '2') run_1();
                    if (com[j] == '3') run_2();
                    if (com[j] == '4') run_3();
                }
                i = 0;
                print("\nMinux >> ", WHITE);
            }

        }
    }
}
*/
