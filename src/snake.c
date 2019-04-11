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

/*
 * 蛇的方法
 *
 * show()
 * move()
 * changeDirect()
 */

/*
 * 蛇节属性
 * 蛇节属性
 */
typedef struct unit_attribute {
    /* 是否是蛇头 */
    bool is_head;
    /* 纵坐标 */
    MAP_SIZE ordinate;
    /* 横坐标 */
    MAP_SIZE abscissa;
    /* 颜色对 */
    u_int8_t bg_color;
    u_int8_t fg_color;

    /* 其他属性 */
    chtype other_attr;

    struct unit_attribute *prefix;
    struct unit_attribute *next;
} unit_attr;

/*
 * 前进方向
 */
enum DIRECT {
    DIRECT_BREAK,
    DIRECT_UP,
    DIRECT_DOWN,
    DIRECT_LEFT,
    DIRECT_RIGHT
};

struct {
    enum DIRECT direct;
    u_int8_t length;
    /* 蛇的身体 链表 */
    unit_attr *body;

    /* 显示方法 */
    SHOW *show;
} snake;

void show_snake();

void init_snake()
{
    snake.direct = DIRECT_BREAK;
    snake.direct = 0;
    snake.body = NULL;
    snake.show = show_snake;
}

void show_snake()
{
    if (snake.body == NULL)
    {
        unit_attr *head = (unit_attr *) malloc(sizeof(unit_attr));
        head->is_head = true;
        head->abscissa = 1;
        head->ordinate = 1;
        head->bg_color = MAP_FG_COLOR;
        head->fg_color = MAP_BG_COLOR;
        head->other_attr = 'o' | A_BOLD | A_BLINK;
        head->prefix = NULL;
        head->next = NULL;

        snake.body = head;
    }
    // todo
   // changePixel(snake.body->ordinate, snake.body->abscissa, )
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
