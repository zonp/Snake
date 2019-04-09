//
// Created by nelsonsun on 19-3-18.
//

#include <curses.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Map.h"
#include "Food.h"

#include <graphite2/Types.h>
#include <termios.h>
#include <term.h>

/* implemented */


int main()
{
    /* 初始化地图 **/
    initMap();
    /* 显示地图 **/
    map.show();
    hello_world();

    /* 初始化食物　**/
    initFood();
    for (int m = 0; m<MAX_FOOD; ++m)
    {
        food.show();
        usleep(1000);
    }

    sleep(3);
    clearMap();
    return 0;
}
