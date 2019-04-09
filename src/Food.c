/*
 * Created by nelsonsun on 19-3-28.
 */

#include "Map.h"
#include "Food.h"
#include <time.h>

/* 初始化食物属性 **/
void initFood()
{
    if (food.initialized == true)
    {
        return;
    }
    /* 设置大小 **/
    food.height = 1;
    food.width = 1;
    /* 设置默认位置 **/
    food.topX = 0;
    food.leftY = 0;
    /* 设置默认背景和前景颜色 **/
    food.bgColor = MAP_FG_COLOR;
    food.fgColor = MAP_BG_COLOR;
    /* 加载展示食物的方法　 **/
    food.show = showFood;
    //
    srand((unsigned) time(NULL));
    /* 初始化成功 **/
    food.initialized = true;
}

/*
 * 显示食物
 */
void showFood()
{
    food.topX = (u_int) rand()%map.row;
    food.leftY = (u_int) rand()%map.col;
    PIXEL fp;
    fp.c_p = '0';
    changePixel(food.topX, food.leftY, fp);
    map.show();
}