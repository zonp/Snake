#include "Map.h"
#include "Food.h"

#include <curses.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void *delete_body();

void snake_break(char *str);

/*
 * 蛇节属性
 * 蛇节属性
 */
struct unit_attribute {
    /* 是否是蛇头 */
    bool is_head;
    /* 纵坐标 */
    MAP_SIZE ordinate;
    /* 横坐标 */
    MAP_SIZE abscissa;

    /* 其他属性 */
    PIXEL other_attr;

    struct unit_attribute *next;
};

typedef struct unit_attribute unit_attr;
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
    /* 蛇头的坐标 */
    MAP_SIZE coordinate_y;
    MAP_SIZE coordinate_x;
    /* 蛇的蛇头 链表 */
    unit_attr *header;
    unit_attr *last;
    PIXEL header_attr;
} snake;
void show_snake();

unit_attr *new_body(MAP_SIZE y, MAP_SIZE x);


