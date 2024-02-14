#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void add();
void del();
void selfBite();
void Print(char* sleif);

int head = 1;
int tail = 0;
int snake_size = 1;

int size_x;
int size_y;    

int* snake_x;
int* snake_y;

int x = 15;
int y = 15;

const int max_size = 10;

int main()
{
    char* temp = "H";
    char* apple = "O";
    char* sleif = "-";

    initscr();

    int apple_x = 10;
    int apple_y = 10;

    getmaxyx(stdscr, size_y, size_x);

    int* res = (int*) malloc((max_size) * sizeof(int));
    int* res1 = (int*) malloc((max_size) * sizeof(int));
    snake_x = res;
    snake_y = res1; 

    srand(time(NULL));

    int dy = 0;
    int dx = 0;

    halfdelay(4);

    while (1)
    {
        mvaddstr(y, x, temp);

        Print(sleif);

        mvaddstr(apple_y, apple_x, apple);

        int code = getch();

        if (code == 119) // w
        { 
            //--y;
            dy = -1;
            dx = 0;

        }
        else if (code == 97) // a
        {
            //--x;
            dx = -1;
	        dy = 0;
        }
        else if (code == 115) // s
        {
            //++y;
            dy = 1;
	        dx = 0;
        }
        else if (code == 100) // d
        {
            //++x;
            dx = 1;
	        dy = 0;
        }

        x = x + dx;
	    y = y + dy;

        if (x == apple_x && y == apple_y)
        {
            apple_x = rand() % size_x;
            apple_y = rand() % size_y;
        }
	    else
	    {
	        del();
	    }

        if (y <= 0)
        {
            y = size_y - 1;
        }
        else if (x <= 0)
        {
            x = size_x - 1;
        }
        else if (y >= size_y - 1)
        {
            y = 0;
        }
        else if (x >= size_x - 1)
        {
            x = 0;
        }

	    selfBite();

	    add();
	
        erase();
    }

    endwin();
}

void Print(char* sleif)
{
    if (tail > head)
        {
            for (int i = tail; i < (max_size); ++i)
            {
                mvaddstr(*(snake_y + i), *(snake_x + i), sleif);
            }

            for (int i = 0; i < head; ++i)
            {
                mvaddstr(*(snake_y + i), *(snake_x + i), sleif);
            }
        }
        else
        {
            for (int i = tail; i < head; ++i)
            {
                mvaddstr(*(snake_y + i), *(snake_x + i), sleif);
            } 
        }
}

void add()
{
    if (head < max_size) 
    {
        snake_y[head] = y;
        snake_x[head] = x;
        head = (head + 1) % (max_size);
    } 
}

void del()
{
    if (head != tail) 
    {
        tail = (tail + 1) % (max_size);
    } 
}

void selfBite()
{
    if (tail > head)
    {
        snake_size = tail - head;
        for (int i = tail; i < (max_size); ++i)
        {
	        if (*(snake_y + i) == y && *(snake_x + i) == x)
	        { 
	            endwin();
	            exit(0);
	        }
        }

        for (int i = 0; i < head; ++i)
        {
            if (*(snake_y + i) == y && *(snake_x + i) == x)
            {
                endwin();
                exit(0);
            }
        }
    }
    else
    {
        snake_size = head - tail;

        for (int i = tail; i < head; ++i)
        {
	        if (*(snake_y + i) == y && *(snake_x + i) == x)
	        { 
	            endwin();
	            exit(0);
	        }
        }
    }
}




