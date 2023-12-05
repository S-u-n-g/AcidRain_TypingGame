#include "util.h"

void init() {
	// 콘솔 제목 변경
	system("title RAIN");
	// 콘솔 커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y) {	// 커서 위치 이동 함수
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int randQuarter() {	// 0, 25, 50, 75 의 값을 랜덤으로 생성하는 함수 (문자열 내려올 때 화면 분할에 사용)
	int value;
	srand((unsigned)time(NULL));
	value = (rand() % 4) * 25;
	return value;
}

int keyControl() {	// 방향키 이동 적용 함수
	int temp = _getch();

	if (temp == '72' || temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == '75' || temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == '80' || temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == '77' || temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ' || temp == '13') {
		return SUBMIT;
	}
}

void titleDraw() {	// 게임 제목 출력 함수
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::cout << "               *****         *        *      *   *  " << std::endl;
	std::cout << "               *    *       * *              **  *  " << std::endl;
	std::cout << "               *****       *****      *      * * *  " << std::endl;
	std::cout << "               *    *     *     *     *      *  **  " << std::endl;
	std::cout << "               *     *   *       *    *      *   *  " << std::endl;
}

int menuDraw() {	// 게임 시작, 설명, 종료 선택 옵션 함수
	int x = 27;
	int y = 12;
	gotoxy(x - 2, y);
	std::cout << "> 게 임 시 작 ";
	gotoxy(x, y + 1);
	std::cout << "게 임 설 명 ";
	gotoxy(x, y + 2);
	std::cout << "   종 료    ";

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 12) {
				gotoxy(x - 2, y);
				std::cout << " ";
				gotoxy(x - 2, --y);
				std::cout << ">";
			}
			break;
		}

		case DOWN: {
			if (y < 14) {
				gotoxy(x - 2, y);
				std::cout << " ";
				gotoxy(x - 2, ++y);
				std::cout << ">";
			}
			break;
		}

		case SUBMIT: {
			return y - 12;
		}
		}
	}
}

bool* optionDraw(bool* option) {	// 옵션을 화면에 띄우고 사용자 입력을 받는 함수
	int x = 1;
	int y = 1;
	char op1, op2, op3;
	

	system("cls");
	gotoxy(x, y);
	std::cout << "옵션을 선택하세요 (중복 선택 가능)";

	gotoxy(x, y + 2);
	std::cout << "1.  Alphabet (y/n) ";
	std::cin >> op1;
	if (op1 == 'y' or op1 == 'Y') {		// 입력 값이 y나 Y 일 경우 option 배열의 해당 인덱스 true로 변환
		option[0] = true;
	}

	gotoxy(x, y + 3);
	std::cout << "2.  숫자 (y/n) ";
	std::cin >> op2;
	if (op2 == 'y' or op2 == 'Y') {		// 입력 값이 y나 Y 일 경우 option 배열의 해당 인덱스 true로 변환
		option[1] = true;
	}

	gotoxy(x, y + 4);
	std::cout << "3.  특수문자 (y/n) ";
	std::cin >> op3;
	if (op3 == 'y' or op3 == 'Y') {		// 입력 값이 y나 Y 일 경우 option 배열의 해당 인덱스 true로 변환
		option[2] = true;
	}

	return option;		// option 배열 반환
}

void infoDraw() {	// 게임 설명 출력 함수
	system("cls");
	std::cout << std::endl << "개발자: 안성민" << std::endl;
	std::cout << "이 게임은 타자연습을 목적으로 만들어진 게임이다." << std::endl;
	std::cout << "[게임 방법]" << std::endl;
	std::cout << "- 사용자는 옵션을 선택해서 단어 스타일을 정한다. (복수 선택 가능)" << std::endl;
	std::cout << "- 게임이 시작되면 단어 비가 떨어진다." << std::endl;
	std::cout << "- 떨어지는 단어를 땅에 닿기 전에 입력해야 한다." << std::endl;
	std::cout << "- 단어를 입력하지 못하고 단어가 바닥에 닿으면 게임이 종료된다." << std::endl;

	while (1) {
		if (keyControl() == SUBMIT) {	// 엔터 키로 탈출
			break;
		}
	}
}

int randSpeed() {	// 문자열 하강 속도 랜덤 조정 (300~700 ms)
	int speed;
	srand((unsigned)time(NULL));
	speed = rand() % 4 + 5;
	return speed;
}

