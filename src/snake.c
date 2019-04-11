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

#include "Config.h.in"

/* implemented */

void write_log()
{
    FILE *fd = fopen("test.log", "ab+");
    fputs(log_msg, fd);
    fclose(fd);
}

int main(int argc, char *argv[])
{
//    if (argc<2)
//    {
//        fprintf(stdout, "%s Version %d.%d\n",
//                argv[0],
//        SNAKE_VERSION_MAJOR,
//        SNAKE_VERSION_MINOR);
//        fprintf(stdout, "Usage: %s number\n", argv[0]);
//        return 1;
//    }
    /* 初始化地图 **/
    initMap();
    /* 显示地图 **/
    map.show();
    hello_world();
    wrefresh(map.map_sub_win);
    getch();

    /* 初始化食物　**/
    initFood();
    halfdelay(1);
    int r;
    for (int m = 0; m<MAX_FOOD; ++m)
    {
        food.show();
        r = getch();

        if (r != ERR)
        {
            break;
        }
    }

    getch();
    clearMap();
    return 0;
}
