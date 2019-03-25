//
// Created by nelsonsun on 19-3-18.
//


#include "Map.h"

/** 初始化地图属性 **/
void initMap()
{
    if (map.exist == true)
    {
        return;
    }
    struct winsize w;
    /*获取控制台的长宽*/
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    map.row = w.ws_row<MAP_ROW ? w.ws_row : MAP_ROW;
    map.col = w.ws_col<MAP_COL ? w.ws_col : MAP_COL;
    map.topX = 0;
    map.topY = 0;

    /** 断言判断窗口大小是否合适 todo 如何避免 clion 调用时，　ｒｏｗ和ｃｏｌ为０的状况 **/
    assert(map.row>5 && map.col>5);
    /** 为每个像素点分配内存 **/
    map.pixel = (char **) calloc(map.row, sizeof(char *));
    for (int i = 0; i<map.row; ++i)
    {
        *(map.pixel+i) = (char *) calloc(map.col, sizeof(char));
    }
    map.show = show_map;

    /* 隐藏光标*/
    printf("\033[?25l");
    /*设置背景颜色*/
    printf("%c[1;%dm", 0x1b, MAP_BG_COLOR);
    /*　设置前景颜色　*/
    printf("%c[%d;1m", 0x1b, MAP_FG_COLOR);
    /*清屏*/
    system("clear");
    map.exist = true;
}
/** 清理地图 **/
void clearMap()
{
    // 如果地图不存在，直接返回
    if (map.exist != true || map.pixel == NULL)
    {
        return;
    }
    /* 回收像素内存 */
    /** https://www.imooc.com/wenda/detail/521776 **/
    for (int i = 0; i<map.row; ++i)
    {
        free(*(map.pixel+i));
        *(map.pixel+i) = NULL;
    }
    free(map.pixel);
    map.pixel = NULL;
    map.exist = false;

    /* 显示光标*/
    printf("%c[?25h", 0x1b);
    /* 闭所有属性 */
    printf("\033[0m");
    /*清屏*/
    printf("\033[2J");
    system("clear");
}

/** 输出像素点 **/
void outputPixel()
{
    for (int j = 0; j<map.row; ++j)
    {
        for (int k = 0; k<map.col; ++k)
        {
            char c = *(*(map.pixel+j)+k);
            if (c == '\0')
            {
                printf(" ");
            }
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");
    }
}
/** 绘制地图 **/
void show_map()
{
    char *str = "hello world!";
    size_t len = strlen(str);
    /** 文字开始输出行数，ｘ坐标 **/
    int x = map.row*2/5;
    /** 文字开始输出列数，y坐标 **/
    int y = map.col/2;
    /**  字符输出起点x坐标 **/
    char **start = map.pixel+x;
    /** 依次在制订位置写入字符  **/
    for (int n = 0; n<len && map.row>len+x; n++)
    {
        *(*(start+n)+y) = str[n];
    }
    /** 输出所有的像素 **/
    outputPixel();
    /** 输出地图的行数和列数 **/
    printf("\n");
    printf("row:%d : ", map.row);
    printf("col:%d : ", map.col);
    printf("\n");

    sleep(1);
}