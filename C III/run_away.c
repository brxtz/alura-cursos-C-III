#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "run_away.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int has_pill = 0;

int where_ghost_moves(int presentx, int presenty, int* goalx, int* goaly)
{
    int options [4][2] = {
        {presentx, presenty + 1},
        {presentx + 1, presenty},
        {presentx, presenty - 1},
        {presentx - 1, presenty}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        int position = rand() % 4;
        if(can_walk(&m, GHOST, options[position][0], options[position][1]))
        {
            *goalx = options[position][0];
            *goaly = options[position][1];

            return 1;
        }
    }
    return 0;
}

void ghosts() 
{
    MAP copy;
    copy_map(&copy, &m);
    for(int i = 0; m.lines; i++)
    {
        for(int j = 0; m.columns; j++)
        {
            if(copy.matrix[i][j] == GHOST)
            {
                if(its_valid(&m, i, j+1)  && its_empty(&m, i, j+1))
                {
                    moving(&m, i, j, i, j+1);
                }
            }
        }
    }

    free(&copy);
}


int ended()
{
    POSITION pos;
    int won = !find_map(&m, &pos, HERO);
    int lost = !find_map(&m, &pos, GHOST);
    return won || lost;
}

int its_direction(char direction) 
{
    return direction == 'w' || 
    direction == 'a' || 
    direction == 's' || 
    direction == 'd';
    
}

void move(char direction)
{
    if(!its_direction(direction))
    {
        return;
    } 

    int nextx = hero.x;
    int nexty = hero.y;

    switch(direction)
    {
        case LEFT:
            m.matrix[hero.x][hero.y-1] = "@"; //move left
            hero.y--;
        case UP:
            m.matrix[hero.x-1][hero.y] = '@'; //move up
            hero.x--;
            break;
        case DOWN:
            m.matrix[hero.x+1][hero.y] = '@'; //move down
            hero.x++;
            break;
        case RIGHT:
            m.matrix[hero.x][hero.y+1] = '@'; //move right
            hero.y++;
            break;
    }

    if(!can_walk(&m, HERO, nextx, nexty))
    {
        return;
    }

    if(its_character(&m, PILL, nextx, nexty))
    {
        has_pill = 1;
    }

    moving(&m, hero.x, hero.y, nextx, nexty);
    hero.x = nextx;
    hero.y = nexty;
}

void explode_pill()
{
    explode_pill2(hero.x, hero.y, 0, 1, 3); //explode to the left
    explode_pill2(hero.x, hero.y, 0, -1, 3); //explode to the right
    explode_pill2(hero.x, hero.y, 1, 0, 3); //explode up
    explode_pill2(hero.x, hero.y, -1, 0, 3); //explode down
}

void explode_pill2(int x, int y, int sumx, int sumy, int qty)
{
    if(qty == 0)return;
    
    int newx = x + sumx;
    int newy = y + sumy;

    if(!its_valid(&m, newx, newy))return;
    if(its_wall(&m, newx, newy))return;
    
    m.matrix[x][y+1] = EMPTY;
    explode_pillw(newx, newy, sumx, sumy, qty - 1); //recursive function
}

int main()
{
    read_map(&m);
    find_map(&m, &hero, HERO);
    
    do{
        printf("Has pill: %s\n", (has_pill ? "YES" : "NO"));
        print_map(&m);

        char command;
        scanf(" %c", &command);
        move(command);
        if(command == BOMB)
        {
            explode_pill();
        }
    }while(!ended());


    free_map(&m);   
}
    