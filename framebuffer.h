#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <linux/input.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define LCD_DEV_PATH    "/dev/fb0"
#define TS_DEV_PATH     "/dev/input/event0"
#define MMAP_LENGTH     800*480*4

#define GAME_NUM_0      "./imgs/p_0.bmp"
#define GAME_NUM_2      "./imgs/p_2.bmp"
#define GAME_NUM_4      "./imgs/p_4.bmp"
#define GAME_NUM_8      "./imgs/p_8.bmp"
#define GAME_NUM_16     "./imgs/p_16.bmp"
#define GAME_NUM_32     "./imgs/p_32.bmp"
#define GAME_NUM_64     "./imgs/p_64.bmp"
#define GAME_NUM_128    "./imgs/p_128.bmp"
#define GAME_NUM_256    "./imgs/p_256.bmp"
#define GAME_NUM_512    "./imgs/p_512.bmp"
#define GAME_NUM_1024   "./imgs/p_1024.bmp"
#define GAME_NUM_2048   "./imgs/p_2048.bmp"

#define GAME_NUM_PIX    100

#define UI_GAME_PIC_PATH   "./imgs/v1_0/game.bmp"
#define UI_PICT_L_PIC_PATH  "./imgs/v1_0/left.bmp"

typedef struct 
{
    int ts_x;
    int ts_y;
    int flag_press;
    int flag_game;
}ts_info_t;

typedef struct
{
    struct input_event touch;
}pjt_event_t;

typedef struct 
{
    int lcd;
    int *lcd_mmap;
    int ts;
    pjt_event_t event;
    ts_info_t ts_info;
}intel_pjt_t;

int init_fb();
int close_fb();
int Display_Pic(char * pic_path, int dis_x, int dis_y);
int Get_ts_info();

#endif
