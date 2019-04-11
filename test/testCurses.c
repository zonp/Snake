#include <assert.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>

void new_win()
{
    char str[200] = {0};
    WINDOW *my_win, *my_sub_win;
    my_win = newwin(22, 82, 20, 10);
    my_sub_win = subwin(my_win, 20, 80, 21, 11);

    wborder(my_win, '+', '+', '+', '+', 0, 0, 0, 0);
    // box(my_win, '*', '*');
    if (has_colors() && can_change_color())
    {
        strcpy(str, "can change color \n");

        /** 初始化 **/
        start_color();
        char tmp[50];
        sprintf(tmp, "COLORS: %d\nCOLOR_PAIRS: %d\n", COLORS, COLOR_PAIRS);
        strcat(str, tmp);
        init_color(2, 500, 0, 500);
        init_pair(1, 7, 2);
        init_pair(2, COLOR_CYAN, 2);

        assert(COLOR_PAIR(11)>0);
        sprintf(tmp, "COLOR_PAIR(11): %X\n", COLOR_PAIR(7));
        strcat(str, tmp);
        wbkgd(my_sub_win, COLOR_PAIR(2));
        wattrset(my_sub_win, COLOR_PAIR(1));
    }
    else
    {
        strcat(str, "can not change color \n");
    }
//    //box(my_sub_win, 0, 0);
    wmove(my_sub_win, 5, 0);
    strcat(str, "this is new window \n");

    waddstr(my_sub_win, str);

    wmove(my_sub_win, my_sub_win->_maxx-my_sub_win->_begx-1, 0);
    wrefresh(my_win);
    wrefresh(my_sub_win);
    wgetch(my_sub_win);

    wclear(my_sub_win);
    wclear(my_win);
}

int main()
{
    initscr(); /** 开启curses **/
    clear();
    curs_set(2);
    move(10, 30);
    addstr("hello world");
    move(LINES-1, 0);
    refresh();

    new_win();

    getch();
    endwin();  /* 暂停curses会话 */
    return 0;
}



void initial()
{
    initscr();                  //开启curses模式
    clear();                    // 清除一个窗口
    move(10, 20);               // 窗口位置光标功能
    addstr("hello,world");      // 添加一串多字节字符，无需再显示到窗口并前进光标
    curs_set(1);                // 设置光标是否可见
    cbreak();                   //开启cbreak模式,除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
    nonl();                     //用来决定当输入资料时, 按下 RETURN 键是否被对应为 NEWLINE 字元
    noecho();                   //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
    intrflush(stdscr, false);   // 启用或禁用中断刷新
    keypad(stdscr, true);       //当开启 keypad 後, 可以使用键盘上的一些特殊字元, 如上下左右>等方向键
    move(LINES-1, 0);           // 把光标移动到最后一行
    refresh();                  //将做清除萤幕的工作
    getch();                    // 从终端获取单字节字符
    endwin();
}
