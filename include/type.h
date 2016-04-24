#ifndef _TYPE_H_
#define _TYPE_H_

typedef unsigned int        u32;
typedef unsigned short      u16;
typedef unsigned char       u8;
typedef void (*int_handler)  ();
typedef void (*irq_handler)  (int irq);
typedef void* system_call;

typedef struct BPB_info
{
  u8 ignore1[9];
  u16 Bytes_per_sector;
  u8 Sector_per_cluster;
  u16 Number_of_reserved_sectors;
  u8 Number_of_FATs;
  u16 Maximum_number_of_root_dir_entries;
  u16 Total_sector_count;
  u8 ignore2;
  u16 Sectors_per_FAT;
  u16 Sectors_per_track;
  u16 Number_of_heads;
  u8 ignore3[4];
  u32 Total_sector_count_for_FAT32;
  u8 ignore4[2];
  u8 Boot_signature;
  u32 Volume_id;
  u8 Volume_label[11];
  u8 File_system_type[8];
}BPB_info;

typedef struct Root_dir_info
{
  char name[8];
  char format[3];
  char state;
  u8 ignore1[2];
  u16 time;
  //u8 ignore3[2];
  u16 date;
  u8 ignore2[10];
  u32 size;
  u8 ignore3[32]
}Root_dir_info;

#endif /* _TYPE_H_ */
