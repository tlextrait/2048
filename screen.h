/**
 * 2048.h
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#define MATRIX_SIZE 4

class Board{
private:
  int goal;       // goal number (default: 2048)
  int grid[MATRIX_SIZE][MATRIX_SIZE];
public:
  Board();
  void display();
};
