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
    struct winsize w;
    /*获取控制台的长宽*/
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    map.row = w.ws_row<MAP_ROW && !FIXED ? w.ws_row : MAP_ROW;
    map.col = w.ws_col<MAP_COL && !FIXED ? w.ws_col : MAP_COL;
    map.topX = 0;
    map.leftY = 0;

    /* 断言判断窗口大小是否合适  **/
    assert(map.row>5 && map.col>5);
    /* 为每个像素点分配内存 **/
    map.pixel = (PIXEL **) calloc(map.row, sizeof(PIXEL *));
    for (int i = 0; i<map.row; ++i)
    {
        *(map.pixel+i) = (PIXEL *) calloc(map.col, sizeof(PIXEL));
    }
    map.show = show_map;


    system("clear");
    printf("\033[s");

    /* 隐藏光标*/
//    printf("\033[?25l");
    /*设置背景颜色*/

    printf("\033[1;%dm", MAP_BG_COLOR);
    /*　设置前景颜色　*/
    printf("\033[%d;1m", MAP_FG_COLOR);
    /*清屏*/
    //printf("\033[2J");
    system("clear");


    map.exist = true;
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

    /* 显示光标*/
    printf("\033[?25h");
    /* 闭所有属性 */
    printf("\033[0m");
    /*清屏*/
    printf("\033[2J");
    system("clear");
}

/* 输出像素点 **/
void outputPixel()
{
    for (int j = 0; j<map.row; ++j)
    {
        for (int k = 0; k<map.col; ++k)
        {
            PIXEL c = *(*(map.pixel+j)+k);
            if (c.c_p == '\0')
            {
                printf(" ");
            }
            else
            {
                printf("%c", c.c_p);
            }
        }
        printf("\n");
    }
    printf("\033[u");
}

/*
 * 改变指定位置的像素点的值
 * @param x
 * @param y
 * @param pixel
 */
void changePixel(int x, int y, PIXEL pixel)
{
    /* 依次在制订位置写入字符  **/
    //printf("\033[2J");
    //printf("\033[s");
    //printf("\033[u");
    printf("\033[%d;%df", x, y);
    printf("%c", pixel.c_p);
    *(*(map.pixel+x)+y) = pixel;
    sleep(1);
}


/* 绘制地图 **/
void show_map()
{
    /* 输出所有的像素 **/
    outputPixel();
    /* 输出地图的行数和列数 **/
    printf("\n");
    printf("row:%d : ", map.row);
    printf("col:%d : ", map.col);
    printf("\n");
}

void hello_world()
{
    char *str = "hello world!";
    size_t len = strlen(str);
    /* 文字开始输出行数，ｘ坐标 **/
    int x = map.row/2;
    /* 文字开始输出列数，y坐标 **/
    int y = map.col*2/5;
    /* 依次在制订位置写入字符  **/
    for (int n = 0; n<len && map.col>len+x; n++)
    {
        changePixel(x, y+n, (PIXEL) str[n]);
    }
}