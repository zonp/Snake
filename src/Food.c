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

    food.count = 0;
    /* 设置大小 **/
    food.height = 1;
    food.width = 1;
    /* 设置默认位置 **/
    food.ordinate = 0;
    food.abscissa = 0;
    /* 设置默认背景和前景颜色 **/
    food.bgColor = COLOR_RED;
    food.fgColor = COLOR_RED;
    init_pair('f', food.fgColor, food.bgColor);
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
    food.ordinate = (u_int) rand()%map.col;
    food.abscissa = (u_int) rand()%map.row;
    PIXEL fp;
    fp.ch_p = FOOD_UNIT | COLOR_PAIR(FOOD_PAIR);
    if (changePixel(food.abscissa, food.ordinate, fp) == OK)
    {
        /* 食物数量加一 */
        food.count += 1;
    }
}