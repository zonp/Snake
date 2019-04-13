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
    PIXEL other_attr;

    struct unit_attribute *prefix;
    struct unit_attribute *next;
} unit_attr;

/*
 * 前进方向
 */
enum DIRECT {
    DIRECT_BREAK = 10000,
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
} snake;

void show_snake();
void going();

void init_snake()
{
    snake.direct = DIRECT_BREAK;
    snake.direct = 0;
    snake.body = NULL;
}

void show_snake()
{
    if (snake.body == NULL)
    {
        unit_attr *head = (unit_attr *) malloc(sizeof(unit_attr));
        head->is_head = true;
        head->abscissa = 1;
        head->ordinate = 1;
        head->bg_color = COLOR_RED;
        head->fg_color = COLOR_YELLOW;
        head->other_attr.ch_p = BODY_UNIT | A_BOLD | A_BLINK | COLOR_PAIR(SNAKE_PAIR);
        /* 蛇尾的坐标 */
        head->prefix = NULL;
        head->next = NULL;

        snake.body = head;
    }
    // todo
    changePixel(snake.body->ordinate, snake.body->abscissa, snake.body->other_attr);
}

/*
 * 前进
 */
void going(int keyCode)
{
    mvwprintw(map.map_win, map.row+3, 20, "\tkey is : %o", keyCode);
    wrefresh(map.map_win);

    /*
     * 如果没有改变方向，继续向前
     */
    if (keyCode == ERR && snake.direct != DIRECT_BREAK)
    {
        keyCode = snake.direct;
    }

    switch (keyCode)
    {
        case KEY_UP:
        case DIRECT_UP:
        case 'w':
        case 'W':
            if (snake.direct != DIRECT_DOWN)
            {
                snake.direct = DIRECT_UP;
                snake.body->ordinate -= 1;
            }
            break;
        case KEY_DOWN:
        case DIRECT_DOWN:
        case 's':
        case 'S':
            if (snake.direct != DIRECT_UP)
            {
                snake.direct = DIRECT_DOWN;
                snake.body->ordinate += 1;
            }
            break;
        case KEY_LEFT:
        case DIRECT_LEFT:
        case 'a':
        case 'A':
            if (snake.direct != DIRECT_RIGHT)
            {
                snake.direct = DIRECT_LEFT;
                snake.body->abscissa -= 1;
            }
            break;
        case KEY_RIGHT:
        case DIRECT_RIGHT:
        case 'd':
        case 'D':
            if (snake.direct != DIRECT_LEFT)
            {
                snake.direct = DIRECT_RIGHT;
                snake.body->abscissa += 1;
            }
            break;
//        case KEY_ENTER:
//            start();
//            break;
//        case KEY_EXIT:
//        case 0336:
//            exit_game();
//            break;
        default:
            break;
    }

    /* 没有开始 */
    if (snake.direct == DIRECT_BREAK)
    {
        return;
    }

    /* 查看地图，当前位置是否有食物 */
    int y = snake.body->ordinate;
    int x = snake.body->abscissa;
    /* 也可以通过 mvwinch(win, y, x) 获取坐标位置的chtype 判断 判 **/
    //mvwprintw(map.map_win, map.row+4, 20, "\tch is : %c", mvwinch(map.map_sub_win, y, x));
    //wrefresh(map.map_win);

    //if (((*(*(map.pixel+y)+x)).ch_p & A_CHARTEXT) == FOOD_UNIT)
    //{
    // 把蛇头移动到新的位置
    //changePixel(snake.body->ordinate, snake.body->abscissa, snake.body->other_attr);
    //}
    /* 蛇头的移动 */

    /* 蛇尾的移动 */

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
    hello_world();
    getch();
    init_snake();
    show_snake();

    getch();
    /* 初始化食物　**/
    initFood();
    halfdelay(1);
    /*
     * 刷新一次，前进一次，如果食物没有达到最大值，添加一个食物
     */
    int keyCode = 0;
    do
    {
        if (food.count<MAX_FOOD)
        {
            food.show();
        }
        keyCode = getch();
        going(keyCode);

        if (keyCode == ERR)
        {
            continue;
        }
    }
    while (keyCode != 'q' && keyCode != '0');

    clearMap();
    return 0;
}
