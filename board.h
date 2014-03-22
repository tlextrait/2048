/**
 * board.h
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#define MATRIX_SIZE 4
#define DEFAULT_GOAL 2048

class Board{
private:
  int goal;       // goal number (default: 2048)
  int grid[MATRIX_SIZE][MATRIX_SIZE];
public:
  Board();
  void display();
};

void init_rand();
