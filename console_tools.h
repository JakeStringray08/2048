#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int getUserInput() {
	int trick = _getch();
	int char_code = _getch();
	return char_code;
}
