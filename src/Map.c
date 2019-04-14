//
// Created by nelsonsun on 19-3-18.
//


#include "Map.h"

/* 初始化地图属性 **/
void initMap()
{
    if (map.exist == true)
    {
        return;
    }
    map.map_win = NULL;
    map.row = LINES<MAP_ROW && !FIXED ? LINES : MAP_ROW;
    map.col = COLS<MAP_COL && !FIXED ? COLS : MAP_COL;

    map.ordinate = 3;
    map.abscissa = 3;
    map.floor_unit.ch_p = FLOOR_UNIT | COLOR_PAIR(MAP_PAIR);

    /* 断言判断窗口大小是否合适  **/
    assert(map.row>10 && map.col>10);
    /* 为每个像素点分配内存 **/
    map.pixel = (PIXEL **) calloc(map.row, sizeof(PIXEL *));
    for (int i = 0; i<map.row; ++i)
    {
        /* calloc 分配的内存自动用 \0 填充 */
        *(map.pixel+i) = (PIXEL *) calloc(map.col, sizeof(PIXEL));
    }

    initscr();                  //开启curses模式
    cbreak();                   //开启cbreak模式,除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
    noecho();                   //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
    nonl();                     // 不解析换行
    curs_set(0);                // 设置光标是否可见
    keypad(stdscr, true);       //当开启 keypad 後, 可以使用键盘上的一些特殊字元, 如上下左右>等方向键
    clear();                    // 清除一个窗口

    /* 初始化地图窗口 **/
    map.map_win = newwin(map.row+7, map.col+2, map.ordinate-1, map.abscissa-1);
    map.map_sub_win = subwin(map.map_win, map.row, map.col, map.ordinate, map.abscissa);

    /* 初始化颜色 */
    map_color();

    /* 设置地图边框 */
    wattron(map.map_win, COLOR_PAIR(MAP_PAIR) | A_REVERSE);
    wborder(map.map_win, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwhline(map.map_win, map.map_sub_win->_maxy+2, 1, '*', map.map_sub_win->_maxx+1);
    wattroff(map.map_win, COLOR_PAIR(MAP_PAIR) | A_REVERSE);

    /* 填充所有的空白 */
    wattron(map.map_sub_win, COLOR_PAIR(MAP_PAIR));
    for (int j = 0; j<LINES; ++j)
    {
        mvwhline(map.map_sub_win, j, 0, FLOOR_UNIT, COLS);
    }
    wattroff(map.map_sub_win, COLOR_PAIR(MAP_PAIR));
    /* 刷新地图 */
    refresh();

    map.exist = true;

    /* 输出地图的行数和列数 **/
    mvwprintw(map.map_win, map.row+3, 1, "  row: %d", map.row);
    mvwprintw(map.map_win, map.row+4, 1, "  col: %d", map.col);
    wrefresh(map.map_win);
}

/*
 *  设置地图颜色
 */
void map_color()
{
    if (DEBUG)
    {
        sprintf(log_msg, "has_colors:  %d\n", has_colors()), write_log();
        sprintf(log_msg, "can_change_color:  %d\n", can_change_color()), write_log();
    }
    /* 判断是否支持颜色，如果不支持，直接返回 */
    if (!(has_colors() && can_change_color()))
    {
        clearMap();
        perror("color is not supported");
        exit(1);
    }

    start_color();
    init_color(2, 1000, 0, 500);
    init_pair(MAP_PAIR, MAP_FG_COLOR, MAP_BG_COLOR);
    init_pair(SNAKE_PAIR, COLOR_RED, MAP_FG_COLOR);
    init_pair(FOOD_PAIR, COLOR_WHITE, MAP_BG_COLOR);
    init_pair(4, COLOR_BLUE, MAP_BG_COLOR);
    init_pair(5, COLOR_MAGENTA, MAP_BG_COLOR);
    init_pair(6, COLOR_CYAN, MAP_BG_COLOR);
    init_pair(7, COLOR_WHITE, 2);
}

/* 清理地图 **/
void clearMap()
{
    // 如果地图不存在，直接返回
    if (map.exist != true || map.pixel == NULL)
    {
        return;
    }
    /* 回收像素内存 */
    /* https://www.imooc.com/wenda/detail/521776 **/
    for (int i = 0; i<map.row; ++i)
    {
        free(*(map.pixel+i));
        *(map.pixel+i) = NULL;
    }
    free(map.pixel);
    map.pixel = NULL;
    map.exist = false;

    refresh();                  //将做清除萤幕的工作
    nocbreak();                   //开启cbreak模式,除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
    echo();                   //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
    nl();
    keypad(stdscr, false);
    curs_set(1);                // 设置光标是否可见
    clear();

    standend();
    delwin(map.map_sub_win);
    delwin(map.map_win);
    endwin();
}

/*
 * 改变指定位置的像素点的值
 * @param y
 * @param x
 * @param pixel
 */
int changePixel(MAP_SIZE y, MAP_SIZE x, PIXEL pixel)
{
    *(*(map.pixel+y)+x) = pixel;
    int rs = mvwaddch(map.map_sub_win, y, x, pixel.ch_p);
    wrefresh(map.map_sub_win);

    return rs;
}

void hello_world()
{
    char *str = "hello world!";
    PIXEL hw;
    size_t len = strlen(str);
    /* 文字开始输出行数，y坐标 **/
    int y = map.row/2;
    /* 文字开始输出列数，x坐标 **/
    int x = map.col*2/5;
    /* 依次在制订位置写入字符  **/
    for (int n = 0; n<len && map.col>len+x; n++)
    {
        hw.ch_p = str[n] | A_BLINK | COLOR_PAIR(FOOD_PAIR);
        changePixel(y, x+n, hw);
    }
}