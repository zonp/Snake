#include <assert.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>

void new_win()
{
    char str[200] = {0};
    WINDOW *my_win, *my_sub_win;
    my_win = newwin(22, 32, 20, 10);
    my_sub_win = subwin(my_win, 20, 30, 21, 11);
    box(my_win, '|', '-');
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
