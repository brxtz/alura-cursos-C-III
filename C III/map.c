#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void copy_map(MAP* goal, MAP* origin)
{
    goal->lines = origin->lines;
    goal->columns = origin->columns;

    alloc_map(goal);
    for(int i = 0; i < origin->lines; i++)
    {
        strcpy(goal->matrix[i], origin->matrix[i]);
    }

}

void moving(MAP* m, int originx, int originy, int goalx, int goaly)
{
    char player = m->matrix[originx][originy];
    m->matrix[goalx][goaly] = player;
    m->matrix[originx][originy] = EMPTY;
}

int its_valid(MAP* m, int x, int y)
{
    if(x >= m->lines)
    {
        return;
    }
    if(y >= m->columns)
    {
        return;
    }

    return 1;
}

int its_empty(MAP* m, int x, int y)
{
    if(m->matrix[x][y] = EMPTY)
    {
        return;
    }
}

int its_wall(MAP* m, int x, int y)
{
    return m->matrix[x][y] == HORIZONTAL_WALL ||
    m->matrix[x][y] == VERTICAL_WALL;
}

int its_character(MAP* m, char character, int x, int y)
{
    return m->matrix[x][y] == character;
}

int can_walk(MAP* m, char character, int x, int y)
{
    return its_valid(&m, x, y) && !its_wall(&m, x, y) && its_character(m, character, x, y);
}

int find_map(MAP* m, POSITION* p, char c)
{
    for(int i = 0; i < m->lines; i++)
    {
        for(int j = 0; j < m->columns; j++)
        {
            if(m->matrix[i][j] == c)
            {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

void alloc_map(MAP* m)
{
    m->matrix = malloc(sizeof(char*) * m->lines); //memory allocation - number of lines times the size of a char
    for(int i = 0; i < m->lines; i++)
    {
        m->matrix[i] = malloc(sizeof(char) * (m->columns +1)); //memory allocation - nubertimes of collumns + 1 times the size of a char
    }
}

void read_map(MAP* m){
    FILE* f;
    f = fopen("map.txt", "r");
    if(f == 0)
    {
        printf("Error on the map reading");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->lines), &(m->columns)); //first line of the file map.txt is dedicated for the map dimensions "lines columns"

    alloc_map(m);

    for(int i = 0; i < 5; i++) //for loop that will read through the map lines
    {
        fscanf(f, "%s", m->matrix[i]);
    }

    fclose(f);
}

void free_map(MAP* m)
{
    for(int i = 0; i < m->lines; i++)
    {
        free(m->matrix[i]); //freeing memory used
    }
    free(m->matrix);
}

void print_map(MAP* m)
{
    for(int i = 0; i < m->lines; i++)
    {
        printf("%s\n", m->matrix[i]);
    }
}