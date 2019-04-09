//
// Created by nelsonsun on 19-3-18.
//

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include <assert.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* 地图大小是否固定 **/
#define FIXED true
/* 地图宽(列)高(行) */
#define MAP_ROW 35
#define MAP_COL 80
/* 地图背景和前景颜色 **/
#define MAP_BG_COLOR 44
#define MAP_FG_COLOR 32

// 定义显示地图的指针函数的类型
typedef void (SHOW)();

typedef union
{
    char c_p;
    int i_p;
}  PIXEL;

/* 地图结构体变量Map **/
typedef struct {
    /* 行 **/
    unsigned int row;
    unsigned int col;
    // 顶点坐标
    unsigned int topX;
    unsigned int leftY;
    SHOW *show;
    // 所有的像素点
    PIXEL **pixel;
    /* 判断地图是否已经被初始化 **/
    bool exist;
} MAP;
/* 定义全局地图 **/
MAP map;

/* 初始化地图属性 **/
void initMap();

/*
 * 改变指定位置的像素点的值
 * @param x
 * @param y
 * @param pixel
 */
void changePixel(int x, int y, PIXEL pixel);

/* 输出像素点 **/
void outputPixel();

/* 地图方法 **/
void show_map();

/* 地图中输入ｈｅｌｌｏ　ｗｏｒｌｄ **/
void hello_world();

/* 清理地图 **/
void clearMap();

#endif //SNAKE_MAP_H
