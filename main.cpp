#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

enum Direction { UP, RIGHT, DOWN, LEFT, UNDEFINED };

enum GameStatus { CONTINUE, FAIL, SUCCESS};

Direction getUserInput() {
	int trick = _getch();
	int char_code = _getch();
	if (char_code == KEY_UP) {
		return UP;
	} else if (char_code == KEY_DOWN) {
		return DOWN;
	} else if (char_code == KEY_LEFT) {
		return LEFT;
	} else if (char_code == KEY_RIGHT) {
		return RIGHT;
	} else {
		return UNDEFINED;
	} 
}

void printSymbols(char s, int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << setw( 3 ) << s;
	}
	cout << endl;
}

class GameBoard {
	public:
		GameBoard(int w=4, int h=4) {
			width = w;
			height = h;
			
			board = new int*[h];
			for (int i = 0; i < height; i++) {
				board[i] = new int[w];
			}
			
			zeroBoard();
			
			gameStatus = CONTINUE;
		}
		
		void start() {
			setup();
			showBoard();
			startGameLoop();
		}
		
	private:
		int width;
		int height;
		int **board;
		
		GameStatus gameStatus;
		
		static const int INIT_VALUE = 2;
		
		Direction dir;
		
		void zeroBoard() {
			for (int row = 0; row < height; row++) {
				for (int column = 0; column < width; column++) {
					board[row][column] = 0;
				}
			}
		}
		
		vector<int> getFreeZones() {
			vector<int> free;
			for (int row = 0; row < height; row++) {
				for (int column = 0; column < width; column++) {
					if (board[row][column] == 0) {
						free.push_back(row * width + column);
					}
				}
			}
			return free;
		}
		
		void setValue(int pos, int value) {
			if (pos == -1)
				return;
			
			int h = pos / height;
			int w = pos % width;
			
			board[h][w] = value; 
		}
		
		int getRandPlace() {
			srand(time( 0 ));
			vector<int> places = getFreeZones();
			if (places.size() == 0) {
				gameStatus = FAIL;
				return -1;
			}
			int where = rand() % places.size();
			return where;
		}
		
		void setup() {
			int place = getRandPlace();
			setValue(place, INIT_VALUE);
			place = getRandPlace();
			setValue(place, INIT_VALUE);
		}
		
		void showBoard() {
			printSymbols('\n', 1);
			for (int row = 0; row < height; row++) {
				for (int column = 0; column < width; column++) {
					cout << setw( 5 ) << board[row][column];
				}
				if (row != height-1) cout << "\n\n\n";
			}
			printSymbols('\n', 1);
		}
		
		void processInput(Direction d) {
			if (d != UNDEFINED) {
				dir = d;
				if (d == DOWN) moveDown();
				else if (d == UP) moveUp();
				else if (d == RIGHT) moveRigth();
				else moveLeft();
			}
			else {
				cout << "Use arrows to move numbers" << endl;
				return;
			}
		}
		
		void moveDown() {
			int j;
			for (int column = 0; column < width; column++) {
				for (int row = height-1; row >= 0; row--) {
					if (board[row][column] != 0) {
						j = row;
						while (j < height-1) {
							if (board[j+1][column] == 0) {
								board[j+1][column] = board[j][column];
								board[j][column] = 0;
								j++;
							}
							else {
								if (board[j+1][column] == board[j][column]) {
									board[j+1][column] += board[j][column];
									board[j][column] = 0;
								}
								break;
							}
						}
					}
				}
			}
		}
		
		void moveUp() {
			int j;
			for (int column = 0; column < width; column++) {
				for (int row = 0; row < height; row++) {
					if (board[row][column] != 0) {
						j = row;
						while (j > 0) {
							if (board[j-1][column] == 0) {
								board[j-1][column] = board[j][column];
								board[j][column] = 0;
								j--;
							}
							else {
								if (board[j-1][column] == board[j][column]) {
									board[j-1][column] += board[j][column];
									board[j][column] = 0;
								}
								break;
							}
						}
					}
				}
			}
		}
		
		void moveRigth() {
			int j;
			for (int row = 0; row < height; row++) {
				for (int column = width-1; column >= 0; column--) {
					if (board[row][column] != 0) {
						j = column;
						while (j < width-1) {
							if (board[row][j+1] == 0) {
								board[row][j+1] = board[row][j];
								board[row][j] = 0;
								j++;
							}
							else {
								if (board[row][j] == board[row][j+1]) {
									board[row][j+1] += board[row][j];
									board[row][j] = 0;
								}
								break;
							}
						}
					}
				}
			}
		}
		
		void moveLeft() {
			int j;
			for (int row = 0; row < height; row++) {
				for (int column = 0; column < width; column++) {
					if (board[row][column] != 0) {
						j = column;
						while (j > 0) {
							if (board[row][j-1] == 0) {
								board[row][j-1] = board[row][j];
								board[row][j] = 0;
								j--;
							}
							else {
								if (board[row][j] == board[row][j-1]) {
									board[row][j-1] += board[row][j];
									board[row][j] = 0;
								}
								break;
							}
						}
					}
				}
			}
		}
		
		void startGameLoop() {
			while (gameStatus != FAIL || gameStatus != SUCCESS) {
				processInput(getUserInput());
				setValue(getRandPlace(), INIT_VALUE);
				showBoard();
			}
		}
};

int main(int argc, char** argv) {
	GameBoard myBoard;
	myBoard.start();
	return 0;
}
