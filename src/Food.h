/*
 * Created by nelsonsun on 19-3-28.
 */

#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#define MAX_FOOD 500

typedef struct {
    /* 判断是否已经初始化 **/
    bool initialized;
    u_int8_t height;
    u_int8_t width;
    /*  距离地图的纵坐标和横坐标 **/
    MAP_SIZE ordinate;
    MAP_SIZE abscissa;
    /* 背景和前景颜色**/
    u_int8_t bgColor;
    u_int8_t fgColor;
    /* 食物的数量 */
    unsigned count;
    /* 显示方法 **/
    FUN_POINTER *show;
} FOOD;

FOOD food;

void initFood();
/*  显示食物, 给地图中指定位置写入食物对象 **/
void showFood();

#endif //SNAKE_FOOD_H
