//============================================================================
// Name        : LCDMenuBuilder.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <Menu_common.h>
#include <array>

#include "MenuSystem.h"
#include "MenuExceptions.h"
#include "MenuConfig.h"
#include "TextInputItem.h"

//#define PRINT_KEY

char getch() {
    char buf = 0;
    if(read(0, &buf, 1) < 0)
        perror ("read()");
    return (buf);
}

void print(uint8_t line, std::string text) {
	static std::array<std::string, 4> display;
	display[line] = text;

	std::cout << "\033[2J"; // ANSI escape code to clear screen
	std::cout << "\033[H";  // Move cursor to home position
	for (const auto &s : display) {
		std::cout << s << std::endl;
	}
}

bool captureKeys(MenuSystem& menu){
	char key = getch();
	switch(key) {
	case 65:
		menu.Input(MenuNav::ARROW_DOWN);
	    break;
	case 66:
		menu.Input(MenuNav::ARROW_UP);
	    break;
	case 67:
		menu.Input(MenuNav::ARROW_RIGHT);
	    break;
	case 68:
		menu.Input(MenuNav::ARROW_LEFT);
	    break;
	case 127:
		menu.Input(MenuNav::BACKSPACE_KEY);
		break;
	case 10:
		menu.Input(MenuNav::ENTER_KEY);
		break;
	case 51:
		if(MenuItem::NavStackSize()> 1){
			menu.Input(MenuNav::CANCEL_KEY);
			return false;
		}
		return true;
	default:
		menu.Input(key);
		break;
	}
#ifdef PRINT_KEY
		std::cout << "Key:"<<(int)key << std::endl;
		sleep(1);
#endif
	return false;
}

void testHandler(void* args, size_t len){
	if(len > 0){
		char * _args = (char*)args;
		std::cout << "value:" << (int)_args[0] <<std::endl; sleep(1);
	}
}

int main() {
	struct termios oldTermios, newTermios;

	tcgetattr(STDOUT_FILENO, &oldTermios);

	newTermios = oldTermios;
	newTermios.c_lflag &= ~ECHO; // Turn off echo
	newTermios.c_lflag &= ~ICANON; // Turn off canonical mode
	newTermios.c_cc[VMIN] = 1;
	newTermios.c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSANOW, &newTermios);

	try {
		uint8_t testVal = 0;

		NavStack navStack;
		MenuConfig config(print);
		MenuSystem m( {
			new MenuItem("item1"),
			new MenuItem("item2"),
			new SubMenu("item3", {
					new SubMenu("subsub", {new MenuItem("asd")}),
					new MenuItem("8989")}),
			new SubMenu("item4", {new MenuItem("4646")}),
			new SubMenu("item5", {new MenuItem("4646")}),
			new TextInputItem("item6", testHandler, (void*)&testVal, (size_t)1),
			new MenuItem("item7"),
			new MenuItem("item8"),
			new MenuItem("item9"),
		});

		m.Start();
		while(!captureKeys(m)){
			usleep(10000);
			testVal++;
		}
	} catch (MenuException &e) {
		std::cout << e.what() << std::endl;
	}

	tcsetattr(STDOUT_FILENO, TCSANOW, &oldTermios);

	std::cout << "\033[2J" << "\033[H" << "Program Ended" << std::endl;
	return 0;
}

