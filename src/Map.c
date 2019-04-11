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
    struct winsize w;
    /*获取控制台的长宽*/
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
    {
        perror("获取控制台的属性失败");
        exit(1);
    }
    map.row = w.ws_row<MAP_ROW && !FIXED ? w.ws_row : MAP_ROW;
    map.col = w.ws_col<MAP_COL && !FIXED ? w.ws_col : MAP_COL;

    map.ordinate = 3;
    map.abscissa = 3;

    /* 断言判断窗口大小是否合适  **/
    assert(map.row>10 && map.col>10);
    /* 为每个像素点分配内存 **/
    map.pixel = (PIXEL **) calloc(map.row, sizeof(PIXEL *));
    for (int i = 0; i<map.row; ++i)
    {
        *(map.pixel+i) = (PIXEL *) calloc(map.col, sizeof(PIXEL));
    }
    map.show = show_map;

    initscr();                  //开启curses模式
    cbreak();                   //开启cbreak模式,除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
    noecho();                   //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
    clear();                    // 清除一个窗口
    curs_set(0);                // 设置光标是否可见
    keypad(stdscr, true);       //当开启 keypad 後, 可以使用键盘上的一些特殊字元, 如上下左右>等方向键

    /* 初始化地图窗口 **/
    map.map_win = newwin(map.row+7, map.col+2, map.ordinate-1, map.abscissa-1);
    map.map_sub_win = subwin(map.map_win, map.row, map.col, map.ordinate, map.abscissa);

    /* 设置地图颜色 */
    map_color();
    /* 设置地图边框 */
    //box(map.map_win, '|', '*');

    wborder(map.map_win, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwhline(map.map_win, map.map_sub_win->_maxy+2, 1, '*', map.map_sub_win->_maxx + 1);
    /* 用空格填充所有的空白 */
    werase(map.map_sub_win);

    //waddnstr(map.map_sub_win, "hello world", -1);
    wrefresh(stdscr);
    wrefresh(map.map_win);
    wrefresh(map.map_sub_win);

    map.exist = true;
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
        return;
    }

    start_color();
    init_color(2, 500, 0, 500);

    init_pair(1, MAP_FG_COLOR, MAP_BG_COLOR);
    init_pair(2, COLOR_GREEN, MAP_BG_COLOR);
    init_pair(3, COLOR_YELLOW, MAP_BG_COLOR);
    init_pair(4, COLOR_BLUE, MAP_BG_COLOR);
    init_pair(5, COLOR_MAGENTA, MAP_BG_COLOR);
    init_pair(6, COLOR_CYAN, MAP_BG_COLOR);

    init_pair(7, COLOR_WHITE, 2);
    wbkgd(map.map_sub_win, COLOR_PAIR(1));
    //wattrset(map.map_sub_win, COLOR_PAIR(3));
    wattron(map.map_sub_win, COLOR_PAIR(1) | A_BOLD);
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
    curs_set(1);                // 设置光标是否可见
    wclear(map.map_sub_win);
    delwin(map.map_sub_win);

    wclear(map.map_win);
    delwin(map.map_win);
    endwin();
}

/* 输出像素点 **/
void outputPixel()
{
    for (int j = 0; j<map.row; ++j)
    {
        for (int k = 0; k<map.col; ++k)
        {
            PIXEL c = *(*(map.pixel+j)+k);
            if (c.c_p != '\0')
            {
                mvwprintw(map.map_sub_win, j, k, "%c", c.c_p);
            }
        }
    }

    wrefresh(map.map_sub_win);
}

/*
 * 改变指定位置的像素点的值
 * @param y
 * @param x
 * @param pixel
 */
void changePixel(MAP_SIZE y, MAP_SIZE x, PIXEL pixel)
{
    *(*(map.pixel+y)+x) = pixel;
    mvwprintw(map.map_sub_win, y, x, "%c", pixel.c_p);
}

/* 绘制地图 **/
void show_map()
{
    /* 输出所有的像素 **/
    outputPixel();
    /* 输出地图的行数和列数 **/
    mvwprintw(map.map_win, map.row+3, 1, "\trow: %d", map.row);
    mvwprintw(map.map_win, map.row+4, 1, "\tcol: %d", map.col);

    wrefresh(map.map_win);
}

void hello_world()
{
    char *str = "hello world!";
    size_t len = strlen(str);
    /* 文字开始输出行数，y坐标 **/
    int y = map.row/2;
    /* 文字开始输出列数，x坐标 **/
    int x = map.col*2/5;
    /* 依次在制订位置写入字符  **/
    for (int n = 0; n<len && map.col>len+x; n++)
    {
        changePixel(y, x+n, (PIXEL) str[n]);
    }
}