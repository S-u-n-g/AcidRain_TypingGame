#include "main.h"
#include "game.h"
#include "util.h"

int main() {
	init();
	while (1) {
		titleDraw(); // 시작 화면
		int choice = menuDraw();	// 메인 메뉴
		bool option[3] = { false };		// 옵션 선택 배열 초기화

		switch (choice)
		{
		case 0:
			play(optionDraw(option)); // 게임의 주 함수 호출 (게임 시작)
			break;
		case 1:
			infoDraw(); // // 게임 설명 함수 호출
			break;
		case 2:
			return 0; // 게임 종료
			break;
		default: // 그외 입력 무시
			break;
		}
		system("cls");
	}
	return 0;
}