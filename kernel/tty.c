#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "memory.h"
#include "proc.h"
#include "global.h"
#include "keyboard.h"

extern bpb_ptr;
void int_33();
void int_34();
void int_35();
void int_36();

void print_pbp() {
    BPB_info* bpb = 0x7c00; //7c00h
    print("\nBytes per sector: ", WHITE);
    print_int((u32)bpb->Bytes_per_sector, LIGHTRED);
    print("\nSector per cluster: ", WHITE);
    print_int((u32)bpb->Sector_per_cluster, LIGHTRED);
    print("\nNumber of reserved sectors: ", WHITE);
    print_int((u32)bpb->Number_of_reserved_sectors, LIGHTRED);
    print("\nNumber of FATs: ", WHITE);
    print_int((u32)bpb->Number_of_FATs, LIGHTRED);
    print("\nMaximum number of root dir entries: ", WHITE);
    print_int((u32)bpb->Maximum_number_of_root_dir_entries, LIGHTRED);
    print("\nTotal sector count: ", WHITE);
    print_int((u32)bpb->Total_sector_count, LIGHTRED);
    print("\nSectors per FAT: ", WHITE);
    print_int((u32)bpb->Sectors_per_FAT, LIGHTRED);
    print("\nSectors per track: ", WHITE);
    print_int((u32)bpb->Sectors_per_track, LIGHTRED);
    print("\nNumber of heads: ", WHITE);
    print_int((u32)bpb->Number_of_heads, LIGHTRED);
    print("\nBoot signature: ", WHITE);
    print_int((u32)bpb->Boot_signature, LIGHTRED);
    print("\nVolume id: ", WHITE);
    print_int((u32)bpb->Volume_id, LIGHTRED);
}

void print_root_dir() {
    Root_dir_info* root = 0x7c00 + 9760;
    int t = 0;
    print("\n\n", WHITE);
    print("FILENAME        |   CREATED TIME\n\n", WHITE);
    while (1) {
        if ((root->name)[0] == 0) break;
        print("\\", WHITE);
        char * str = root->name;
        print_fixed(str, LIGHTRED, 11, 15);
        print("|   ", WHITE);
        u16 time = root->time;
        u16 date = root->date;
        int sec = (time & 0x1f) * 2;
        int min = (time & 0x3e0) >> 5;
        int hour = (time & 0xf800) >> 11;

        int day = (date & 0x1f);
        int mon = (date & 0x1E0) >> 5;
        int year = (1980 + ((date & 0xfe00) >> 9));

        print_int(hour, WHITE);
        print(":", WHITE);
        print_int(min, WHITE);
        print(":", WHITE);
        print_int(sec, WHITE);
        print("  ", WHITE);
        print_int(year, WHITE);
        print("/", WHITE);
        print_int(mon, WHITE);
        print("/", WHITE);
        print_int(day, WHITE);
        print("\n", WHITE);

        root += 1;
    }
    print("\n", WHITE);
}
PUBLIC void run_0() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("1\n", LIGHTRED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (keyboard_read() == 28) break;
    }
}
PUBLIC void run_1() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("2\n", LIGHTRED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (keyboard_read() == 28) break;
    }
}
PUBLIC void run_2() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("3\n", LIGHTRED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (keyboard_read() == 28) break;
    }
}
PUBLIC void run_3() {
    int flag = 1;
    print("\nRuning Program ", WHITE);
    print("4\n", LIGHTRED);
    print("Press Enter to continue\n", WHITE);
    while (flag) {
        if (keyboard_read() == 28) break;
    }
}
PUBLIC void tty() {
    print("\nCurtain OS >> ", WHITE);
    char    output[2];
    output[1] = '\0';
    char    com[1000];
    int i;
    i = 0;
    while (1) {
        u8 key = keyboard_read();
        if (key == 0) continue;
        if (key == 28) {
            if (com[0] == 'i' && com[1] == 'n' && com[2] == 'f' && com[3] == 'o')
                print_pbp();
            if (com[0] == 'i' && com[1] == 'n' && com[2] == 't') {
                if (com[4] == '3') int_33();
                if (com[4] == '4') int_34();
                if (com[4] == '5') int_35();
                if (com[4] == '6') int_36();
            }
            if (com[0] > '0' && com[0] < '5') {
                for (int j = 0; j < i; j++) {
                    if (com[j] == '1') run_0();
                    if (com[j] == '2') run_1();
                    if (com[j] == '3') run_2();
                    if (com[j] == '4') run_3();
                }
            }
            if (com[0] == 'd' && com[1] == 'i' && com[2] == 'r')
                print_root_dir();
            i = 0;
            print("\nCurtain OS >> ", WHITE);
        }
        else {
            output[0] = key;
            print(output, WHITE);
            com[i++] = key;
        }
    }
}
