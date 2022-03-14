#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <sys/select.h>
#include <time.h>
 
#define SRC_WIDTH 70
#define SRC_HEIGHT 20
 
WINDOW *g_mainwin;
int g_oldcur, g_score = 0, g_width, g_height;
 
typedef struct
{
    int x;
    int y;
} pos;
 
pos fruit;
 
bool *spaces;
 
 
// queue stuff
struct s_node
{
    pos *position;
    struct s_node *prev;
    struct s_node *next;
} *front = NULL,*back =NULL;
 
typedef struct s_node node;
 
pos * peek(){
    return front == NULL ? NULL : front->position;
}
 
node * dequeue(){
    node *oldfront = front;
    front = front->next;
    return oldfront;
}
 
//queue a position at the back
void enqueue(pos position)
{
    pos *newpos = (pos *)malloc(sizeof(position));
    node *newnode = (node *)malloc(sizeof(node));
 
    newpos->x = position.x;
    newpos->y = position.y;
    newnode->next = newnode->prev = NULL;
    newnode->position = newpos;
    if(front == NULL && back ==NULL)
        front = back = newnode;
    else
    {
        back->next = newnode;
        newnode->prev = back;
        back = newnode;
    }
}
 
//end queue stuff
 
//start snake stuff
void snake_write_text(int y,int x,char *str)
{
    mvwaddstr(g_mainwin, y, x, str);
}
 
//draw the borders
void snake_draw_board()
{
    int i;
    for (i = 0; i < g_height;i++){
        snake_write_text(i, 0, "|");
        snake_write_text(i, g_width - 1, "|");
    }
    for (i = 0; i < g_width;i++)
    {
        snake_write_text(0, i, "-");
        snake_write_text(g_height, i, "-");
    }
    snake_write_text(g_height + 1, 2, "Score:");
}
 
//resets the terminal window and clears up the mem
void snake_game_over()
{
    free(spaces);
    while (front)
    {
        node *n = front;
        front = front->next;
        free(n->position);
        n->position = NULL;
        free(n);
        n = NULL;
    }
 
    endwin();
    exit(0);
}
 
//当前位置是否在界限里面
bool snake_in_bounds(pos position)
{
    return position.y < g_height && position.y > 0 && position.x < g_width - 1 && position.x > 0;
}
 
//2d坐标映射1d
int snake_cooridinate_to_index(pos position)
{
    return g_width * position.y + position.x;
}
 
//1d映射对应的坐标
pos snake_index_to_coordinate(int index)
{
    int x = index % g_width;
    int y = index / g_width;
    return (pos){x, y};
}
 
//随机出现水果
void snake_draw_fruit()
{
    attrset(COLOR_PAIR(3));
    int idx;
    do{
        idx = rand() % (g_width * g_height);
        fruit = snake_index_to_coordinate(idx);
    } while (spaces[idx] || !snake_in_bounds(fruit));
    attron(A_REVERSE);
    snake_write_text(fruit.y, fruit.x, " ");
    attroff(A_REVERSE);
}
 
//handles moving the snake for each iteration
bool snake_move_player(pos head)
{
    attrset(COLOR_PAIR(1));
 
    //check if we ran into ourself
    int idx = snake_cooridinate_to_index(head);
    if(spaces[idx]){
        pos te = {2, 2};
        snake_game_over();
    }
        
    spaces[idx] = true;
    enqueue(head);
 
    //check if we're eating the fruit
    if(head.x == fruit.x && head.y == fruit.y)
    {
        snake_draw_fruit();
        g_score += 10;
    }else{
 
        node *tail = dequeue();
        pos tem = *(tail->position);
        spaces[snake_cooridinate_to_index(tem)] = false;
        
        snake_write_text(tem.y, tem.x, " ");
        //if(tail->position != NULL)
        free(tail->position);
        tail->position = NULL;
        free(tail);
        tail = NULL;
    }
    attron(A_REVERSE);
    snake_write_text(head.y, head.x, " ");
    attroff(A_REVERSE);
 
    char buffer[25];
    sprintf(buffer, "%d", g_score);
    attrset(COLOR_PAIR(2));
    snake_write_text(g_height+1,9,buffer);
}
 
void check_move_pos(pos *t_head,pos *head){
    pos temp;
    node t_node = *back;
    if (&t_node == NULL)
        return ;
    else
    {   
        
        if(t_node.prev != NULL){
            if((t_node.prev)->position != NULL){
                temp = *((t_node.prev)->position);
                if(t_head->x == head->x){ //x方向
                    if(temp.x == head->x && temp.y == head->y){
                        if(t_head->y > temp.y)
                            head->y += 2;
                        else
                            head->y -= 2;
                    }
                }else if(t_head->y == head->y) { //y方向
                    if(temp.x == head->x && temp.y == head->y){
                        if(t_head->x > temp.x)
                            head->x += 2;
                        else
                            head->x -= 2;
                    }
                }  
                }
             
        }
    }
}
 
int main(int argc,char *argv[])
{
    int key = KEY_RIGHT;
    if((g_mainwin = initscr()) == NULL)
    {
        perror("error initialising ncursess");
        exit(EXIT_FAILURE);
    }
 
    srand(time(NULL));
    noecho();
    curs_set(2);
    halfdelay(1);
    keypad(g_mainwin, TRUE);
    g_oldcur = curs_set(0);
 
    start_color( );
    init_pair( 1, COLOR_RED,     COLOR_BLACK );
    init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
    init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
    init_pair( 5, COLOR_CYAN,    COLOR_BLACK );
    init_pair( 6, COLOR_MAGENTA, COLOR_BLACK );
    init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
    getmaxyx( g_mainwin, g_height, g_width );
    
    g_width  = g_width  < SRC_WIDTH  ? g_width  : SRC_WIDTH;
    g_height = g_height < SRC_HEIGHT ? g_height : SRC_HEIGHT; 
    
    // Set up the 2D array of all spaces
    spaces = (bool*) malloc( sizeof( bool ) * g_height * g_width );
 
    snake_draw_board( );
    snake_draw_fruit( );
    pos head = { 5,5 };
    enqueue( head );
    
    // Event loop
    while( 1 )
    {
        pos t_head = head;
        int in = getch();
        if( in != ERR )
            key = in;
        switch (key)
        {
            case KEY_DOWN:
            case 'k':
            case 'K':
                head.y++;
                break;
            case KEY_RIGHT:
            case 'l':
            case 'L':
                head.x++;
                break;
            case KEY_UP:
            case 'j':
            case 'J':
                head.y--;
                break;
            case KEY_LEFT:
            case 'h':
            case 'H':
                head.x--;
                break;
            }
            //禁止反向
            check_move_pos(&t_head, &head);
            if (!snake_in_bounds(head))
                snake_game_over();
            else
                snake_move_player(head);
        
            
    }
    snake_game_over();
}
