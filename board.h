/**
 * board.h
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

/*
GAME RULES
*/
#define MATRIX_SIZE 4
#define DEFAULT_GOAL 2048
#define STARTING_TILE_COUNT 2

/*
BOARD OBJECT
*/
class Board{
private:
  int goal;       // goal number (default: 2048)
  int grid[MATRIX_SIZE][MATRIX_SIZE];
  int* possibleRandTiles;
  int countPossibleRandTiles;
  void addRandomTile();
  bool isCellEmpty(int x, int y);
public:
  Board();
  void display();
  void moveUp();
  void moveRight();
  void moveDown();
  void moveLeft();
  bool isGameOver();
};

void init_rand();
int getRand(int min, int max);
