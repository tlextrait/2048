/**
 * screen.h
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

class Screen{
private:
	bool initialized;
	bool destroyed;
	void initialize();
	void destroy();
public:
	Screen();
	~Screen();
	static void clear();
};

void init_curses();
void end_curses();

int getKeyPress();
