#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
 

void move(char direction);
int ended();

int its_direction(char direction);

int where_ghost_moves(int presentx, int presenty, int* goalx, int* goaly);

void explode_pill();
void explode_pill2(int x, int y, int sumx, int sumy, int qty);