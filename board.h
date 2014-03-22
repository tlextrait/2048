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
#define CELL_SIZE 4

/*
BOARD OBJECT
*/
class Board{
private:
  int goal;       // goal number (default: 2048)
  int grid[MATRIX_SIZE][MATRIX_SIZE];
  int* possibleRandTiles;
  int countPossibleRandTiles;
  // util
  void addRandomTile();
  bool isCellEmpty(int x, int y);
  // display methods
  void displayHeaderHR();
  void displayHeader();
  void displayFooter();
  void displayBoardHR();
  void displayBoard();
public:
  Board();
  void display();
  // moves
  void moveUp();
  void moveRight();
  void moveDown();
  void moveLeft();
  // state
  bool isGameOver();
};

void init_rand();
int getRand(int min, int max);
