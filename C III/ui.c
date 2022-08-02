#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ui.h"

char wall_art[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char ghost_art[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char hero_art[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pill_art[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char empty_art[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void print_parts(char art[4][7], int parts)
{
    printf("%s", art[parts]);
}

void print_map(MAP* m)
{
    for(int i = 0; i < m->lines; i++)
    {
        for(int parts = 0; parts < 4; parts++)
        {
            for(int j = 0; j < m->columns; j++)
            {
                switch(m->matrix[i][j])
                {
                    case GHOST:
                        print_parts(ghost_art, parts);
                        break;
                    case HERO:
                        print_parts(hero_art, parts);
                        break;
                    case PILL:
                        print_parts(pill_art, parts);
                        break;
                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        print_parts(wall_art, parts);
                        break;
                    case EMPTY:
                        print_parts(empty_art, parts);
                        break;
                }
            }
        }

        printf("%s\n", m->matrix[i]);
    }
}

#endif _MAP_H_