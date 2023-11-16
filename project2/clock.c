#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/eventfd.h>

int main()
{
    int color_index;
    bool running = true;
    int h, w, ch, y, x, ny, nx;
    time_t t;
    char s[64];
    const char* space = "                              ";
    int len = strlen(space);
    initscr();
    raw(); //enter raw mode
    keypad(stdscr, TRUE); //enable capturing special keystrokes
    noecho(); // don't show the typed character on the screen
    curs_set(0); // hide the cursor

    struct pollfd poll_fds[1];
    poll_fds[0].fd = STDIN_FILENO;
    poll_fds[0].events = POLLIN;


    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    color_index = 0;
    nx=ny=x=y=0;
    while (running) {
        wmove(stdscr, y, x);
        wprintw (stdscr, "%.*s", len, space);
        t = time(0);
        strftime(s, sizeof(s), "%c", localtime(&t));
        len = strlen(s);
        getmaxyx(stdscr,h,w);
        if (ny<0) ny = 0;
        if (ny>=h) ny = h-1;
        if (nx+len>=w) nx = w - len;
        if (nx<0) nx = 0;
        attron(COLOR_PAIR(color_index+1) );
        wmove(stdscr, ny, nx);
        waddstr (stdscr, s);
        wrefresh(stdscr);
        attroff(COLOR_PAIR(color_index+1) );
        color_index = (color_index+1)%7;
        y = ny;
        x = nx;
        if ( poll(poll_fds, 1, 1000) < 0 ) {
            perror("Error \n");
            continue;
        }
        if (poll_fds[0].revents & POLLIN) {
            ch = getch();
            switch(ch) {
                case KEY_UP: 
                    ny = y-1;
                    break;
                case KEY_DOWN: 
                    ny = y+1;
                    break;
                case KEY_LEFT: 
                    nx = x-1;
                    break;
                case KEY_RIGHT: 
                    nx = x+1;
                    break;
                case 'q':
                case 'Q':
                    running = false;
                    break;
                default: ;
            }
        }

    }
    wrefresh(stdscr);
    endwin();
    return 0;
}
