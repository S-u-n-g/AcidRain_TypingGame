#include "game.h"
#include "util.h"
#include <string>

class StringDecorator {	// 문자열을 장식하는 데코레이터 추상 클래스
public:
	virtual std::string decorate(const std::string& base) = 0;
};

class AlphabetDecorator : public StringDecorator {	// 알파벳을 더하는 데코레이터
public:
	virtual std::string decorate(const std::string& base) override {
		return base + "abcdefghijklmnopqrstuvwxyz";
	}
};

class NumberDecorator : public StringDecorator {	// 숫자를 더하는 데코레이터
public:
	virtual std::string decorate(const std::string& base) override {
		return base + "0123456789";
	}
};
 
class SpecialCharDecorator : public StringDecorator {	// 특수문자를 더하는 데코레이터
public:
	virtual std::string decorate(const std::string& base) override {
		return base + "!@#$%^&*()_+-=[]{}|;':,.<>?/";
	}
};

class MyString {	// 문자열 객체
private:
	std::string str;	// 문자열
	int location;	// x 위치 값
	int height;		// y 위치 값
	int speed;		// 문자열 하강 속도
	int passed_time = 0;	// 지난 시간 값
public:
	MyString(string str, int location, int height, int speed): str(str), location(location), height(height), speed(speed) {}

	int get_location() {	// location의 값을 반환하는 함수
		return location;
	}
	int get_spped() {		// speed의 값을 반환하는 함수
		return speed;
	}
	int get_height() {		// height의 값을 반환하는 함수
		return height;
	}
	std::string get_string() {	// str의 값을 반환하는 함수
		return str;
	}
	void set_height() {		// height의 값을 하나 증가 시키는 함수
		height++;
	}
	void time_passed() {	// passed_time의 값을 하나 증가 시키는 함수
		passed_time++;
	}
	bool equal_time() {		// speed와 passed_time의 값을 비교하여 두 값이 서로 같을 때 true를 반환하는 함수
		return speed == (passed_time % speed + 1);
	}
};

vector<MyString*> vec;	// 전역변수 vector

class RandomStringGenerator {	// 랜덤 문자열을 생성하는 클래스
private:
	std::vector<StringDecorator*> decorators;  // 데코레이터를 저장하는 벡터
public:
	// 데코레이터를 추가하는 함수
	void addDecorator(StringDecorator* decorator) {
		decorators.push_back(decorator);
	}

	// 데코레이터를 적용하여 랜덤 문자열을 생성하는 함수
	std::string generateRandomString() {
		srand(static_cast<unsigned int>(time(nullptr)));  // 시드 설정
		std::string result;
		int len = (rand() % 3) + 4; // 단어 길이 랜덤 설정
		std::string str;

		for (StringDecorator* decorator : decorators) {	// 옵션에 선택된 데코레이트를 하나의 문자열에 합침
			str = decorator->decorate(str);		
		}
		
		for (int i = 0; i < len; i++) {	// 합친 문자열에서 랜덤으로 골라 randomString 생성
			result.push_back(str[rand() % str.length()]);
		}

		return result;
	}
};

RandomStringGenerator generator;	// 전역변수 랜덤문자열 생성 객체

void play(bool * option) {	// 게임 실행 함수

	// 선택된 옵션에 따라 데코레이터 추가
	if (option[0]) {
		generator.addDecorator(new AlphabetDecorator());
	}
	if (option[1]) {
		generator.addDecorator(new NumberDecorator());
	}
	if (option[2]) {
		generator.addDecorator(new SpecialCharDecorator());
	}
	// 선택된 옵션에 따라 생성된 랜덤 문자열을 얻음
	
	std::thread rainThread(down);

	while (true) {
		std::string randomString = generator.generateRandomString();
		typing(randomString);
	}
	
}

void down() {	// 문자열 하나 내리는 함수
	system("cls");

	gotoxy(0, 15);
	std::cout << "_____________________________________________________________________________________";
	gotoxy(0, 16);
	std::cout << "[Input]: ";
	int max_height = 0;	// 최대 높이 초기화
	double genenrate_second = 2.0;	// 생성 주기 시간 값 초기화

	while (max_height < 15) {	// y축은 15 등분 함
		gotoxy(9, 16);
		if (-0.1 < genenrate_second && genenrate_second < 0.1) {	// 시간이 되어 새로운 문자열을 생성해야 할 때
			int location = randQuarter();	// 랜덤한 값 지정
			int speed = randSpeed();		// 랜덤한 값 지정
			std::string randomString = generator.generateRandomString();
			MyString* ms = new MyString(randomString, location, 0, speed);
			vec.push_back(ms);
			genenrate_second = 2.0;
			gotoxy(location, 0);
			cout << randomString;
		}
		passed();
		max_height = get_max_height();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		genenrate_second -= 0.1;
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	exit(1);	// while 문을 빠져나오게 되면 프로그램 종료
}

void passed() {	// 시간이 지날 때 문자열들을 업데이트 해주는 함수
	for (int i = 0; i < vec.size(); i++) {
		vec[i]->time_passed();
		if (vec[i]->equal_time()) {		// 한 줄 내려가야 할 시간이 되었을 때
			gotoxy(vec[i]->get_location(), vec[i]->get_height());	// 이전 위치 문자 지우기
			cout << "           ";
			vec[i]->set_height();	// 새롭게 height 값 업데이트 (한 줄 밑으로)
			gotoxy(vec[i]->get_location(), vec[i]->get_height());	// 새로운 위치로 출력
			cout << vec[i]->get_string();
		}
	}
}
int get_max_height() {	// 최고 깊은 위치의 height 값을 찾아 반환하는 함수
	int max = 0;
	for (int i = 0; i < vec.size(); i++) {
		max = (max > vec[i]->get_height()) ? max : vec[i]->get_height();
	}
	return max;
}

void typing(std::string answer) {	// 키보드 입력 처리 함수
	std::string userInput;

	while (true) {
		char inputChar = _getch();  // 사용자 입력 받기

		if (inputChar == SUBMIT or inputChar == ' ') {	// 스페이스바 또는 엔터키를 눌렀을 때
			gotoxy(9, 16);	// 이전 값 지우기
			std::cout << "                     ";
			
			for (int i = 0; i < vec.size(); i++) {	// vec에 저장된 문자열과 비교
				if (vec[i]->get_string() == userInput) {	// 같은 문자가 있을 때 vec에 있는 문자 삭제, 화면에서 지움
					gotoxy(vec[i]->get_location(), vec[i]->get_height());
					std::cout << "           ";
					delete vec[i];
					vec.erase(vec.begin() + i);
				}
			}
			userInput = "";	// userInput 값 초기화
			continue;
		}
		else if (inputChar == BACKSPACE) {	// 백스페이스를 입력한 경우
			if (!userInput.empty()) {
				userInput.pop_back();
				int len = userInput.length();
				gotoxy(9 + len, 16);
				std::cout << " ";
			}
			continue;
		}
		
		// 입력된 키를 즉시 출력
		gotoxy(9, 16);
		userInput += inputChar;
		std::cout << userInput;
	}
}
