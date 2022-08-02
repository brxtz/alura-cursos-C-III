#define HERO '@'
#define GHOST 'G'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'
#define BOMB 'b'

struct map 
{
    char** matrix;
    int lines;
    int columns;
};

typedef struct map MAP;

struct position 
{
     int x;
     int y;
};

typedef struct position POSITION;

void free_map(MAP* m);
void read_map(MAP* m);
void alloc_map(MAP* m);
int find_map(MAP* m, POSITION* p, char c);

int its_valid(MAP* m, int x, int y);
int its_empty(MAP* m, int x, int y);
int its_wall(MAP* m, int x, int y);
int its_character(MAP* m, char character, int x, int y);

int can_walk(MAP* m, char character, int x, int y);

void moving(MAP* m, int originx, int originy, int goalx, int goaly);

void copy_map(MAP* goal, MAP* origin);