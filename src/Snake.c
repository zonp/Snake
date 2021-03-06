//
// Created by nelsonsun on 19-3-18.
//
#include "Snake.h"
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

void snake_break(char *str)
{
    clearMap();
    delete_body();
    perror(str);
    exit(1);
}

void init_snake()
{
    snake.direct = DIRECT_BREAK;
    snake.direct = 0;
    snake.header = NULL;
    snake.last = NULL;
    snake.coordinate_y = 0;
    snake.coordinate_x = 0;
    snake.header_attr.ch_p = BODY_UNIT | A_BOLD | A_BLINK | COLOR_PAIR(7);
}

void show_snake()
{
    if (snake.header == NULL)
    {
        unit_attr *head = new_body(snake.coordinate_y, snake.coordinate_x);
        head->is_head = true;
        snake.header = head;
    }
    // todo
    changePixel(snake.header->ordinate, snake.header->abscissa, snake.header_attr);
}

void move_snake()
{
    /* 新的坐标的值 */
    char coordinate_value = (*(map.pixel+snake.coordinate_y)+snake.coordinate_x)->ch_p;
    unit_attr *header = snake.header;
    unit_attr *second = header->next;

    /* 添加蛇单元 */
    unit_attr *new_unit = new_body(header->ordinate, header->abscissa);
    header->next = new_unit;
    new_unit->next = second;
    changePixel(new_unit->ordinate, new_unit->abscissa, new_unit->other_attr);

    /* 保存最后一个单元 */
    snake.last = snake.last == NULL || snake.last->is_head ? new_unit : snake.last;

    /* 同步蛇头坐标 */
    header->ordinate = snake.coordinate_y;
    header->abscissa = snake.coordinate_x;
    /* 蛇头的移动 */
    changePixel(header->ordinate, header->abscissa, snake.header_attr);

    /* 有食物，不移动蛇尾，直接在蛇头后面添加一节新的 */
    //10110
    //10110
    unsigned char test = FOOD_UNIT;
    if (coordinate_value == FOOD_UNIT)
    {
        /* 食物减1 */
        --food.count;
        return;
    }

    /* 找到最后两个单元 */
    unit_attr *second_to_last = header;
    unit_attr *last = second_to_last->next;
    for (int i = 0; last->next != NULL && i<100000; ++i)
    {
        second_to_last = last;
        last = second_to_last->next;
    }

    if (last != snake.last)
    {
        sprintf(log_msg, "坐标错误\n%p\n%p", last, snake.last);
        snake_break(log_msg);
    }
    /* 把倒数第二个作为最后一个 */
    snake.last = second_to_last;
    snake.last->next = NULL;

    /* 蛇尾的移动: 把蛇尾移动到蛇头后面的位置 */
    /* todo 解决蛇身断裂的bug */
    unit_attr *body = header;
    while (body != NULL)
    {
        if (body->ordinate == last->ordinate && body->abscissa == last->abscissa)
        {
            break;
        }

        body = body->next;
    }
    if (body == NULL || body == last)
    {
        changePixel(last->ordinate, last->abscissa, map.floor_unit);
    }

    // 释放内存
    free(last);
    return;
}
unit_attr *new_body(MAP_SIZE y, MAP_SIZE x)
{
    unit_attr *body_unit = (unit_attr *) malloc(sizeof(unit_attr));
    body_unit->is_head = false;
    body_unit->ordinate = y;
    body_unit->abscissa = x;
    body_unit->other_attr.ch_p = BODY_UNIT | COLOR_PAIR(SNAKE_PAIR) | A_BOLD;
    body_unit->next = NULL;

    return body_unit;
}

void *delete_body()
{
    snake.last->next = NULL;
    while (snake.header != NULL)
    {
        unit_attr *p_next = snake.header->next;
        free(snake.header);
        snake.header = p_next;
    }
    return NULL;
}
/*
 * 前进
 */
void going(int keyCode)
{
    /*
     * 如果没有改变方向，继续向前
     */
    if (keyCode == ERR)
    {
        keyCode = snake.direct;
    }
    else
    {
        /* 输出当前输入的key */
        mvwprintw(map.map_win, map.row+3, 15, "keyCode : %3c, %3d", keyCode, keyCode);
        wrefresh(map.map_win);
    }
    /* 判断方向和坐标 */
    switch (keyCode)
    {
        case KEY_UP:
        case DIRECT_UP:
        case 'w':
        case 'W':
            if (snake.direct != DIRECT_DOWN)
            {
                snake.direct = DIRECT_UP;
                snake.coordinate_y -= 1;
            }
            break;
        case KEY_DOWN:
        case DIRECT_DOWN:
        case 's':
        case 'S':
            if (snake.direct != DIRECT_UP)
            {
                snake.direct = DIRECT_DOWN;
                snake.coordinate_y += 1;
            }
            break;
        case KEY_LEFT:
        case DIRECT_LEFT:
        case 'a':
        case 'A':
            if (snake.direct != DIRECT_RIGHT)
            {
                snake.direct = DIRECT_LEFT;
                snake.coordinate_x -= 1;
            }
            break;
        case KEY_RIGHT:
        case DIRECT_RIGHT:
        case 'd':
        case 'D':
            if (snake.direct != DIRECT_LEFT)
            {
                snake.direct = DIRECT_RIGHT;
                snake.coordinate_x += 1;
            }
            break;
//        case KEY_ENTER:
//            start();
//            break;
//        case KEY_EXIT:
//        case 0336:
//            exit_game();
//            break;
        case 't':
            snake.direct = DIRECT_BREAK;
            break;
        default:
            break;
    }
    /* 没有开始 */
    if (snake.direct == DIRECT_BREAK)
    {
        return;
    }

    /* 查看地图，当前位置是否有食物 */
    /* 也可以通过 mvwinch(win, y, x) 获取坐标位置的chtype 判断 判 **/
    chtype ch = mvwinch(map.map_sub_win, snake.coordinate_y, snake.coordinate_x);
    mvwprintw(map.map_win, map.row+4, 15, "inch : '%c' %d", FOOD_UNIT, ch & A_CHARTEXT);
    mvwprintw(map.map_win, map.row+3, 40, "coordinate Y=%d , %d", snake.coordinate_y, snake.header->ordinate);
    mvwprintw(map.map_win, map.row+4, 40, "coordinate X=%d , %d", snake.coordinate_x, snake.header->abscissa);
    wrefresh(map.map_win);

    /* 判断是走出坐标范围 */
    if (snake.coordinate_y>=map.row || snake.coordinate_y<0)
    {
        snake_break("纵坐标超出地图范围");
    }
    if (snake.coordinate_x>=map.col || snake.coordinate_x<0)
    {
        snake_break("横坐标超出地图范围");
    }

    move_snake();
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
    //getch();
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

    snake_break("Game Over!");
    return 0;
}
