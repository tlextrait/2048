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
  int goal;     // goal number (default: 2048)
  int maxTile; 	// lagest tile on the board now
  int grid[MATRIX_SIZE][MATRIX_SIZE];
  int* possibleRandTiles;
  int* valueColors;
  int countPossibleRandTiles;
  // util
  void addRandomTile();
  bool isValidCoordinates(int x, int y);
  bool isCellEmpty(int x, int y);
  int getCell(int x, int y);
  void setCell(int x, int y, int val);
  void setCellEmpty(int x, int y);
  bool isFull();
  // display methods
  void displayHeaderHR();
  void displayHeader();
  void displayFooter();
  void displayBoardHR();
  void displayBoard();
public:
  Board();
  void init();
  void display();
  // moves
  bool isValidMoveKey(int keyCode);
  void doMove(int keyCode);
  bool moveUp();
  bool moveRight();
  bool moveDown();
  bool moveLeft();
  // state
  bool isGameFinished();
  bool isGameOver();
  bool isGameWon();
};

void init_rand();
int getRand(int min, int max);
