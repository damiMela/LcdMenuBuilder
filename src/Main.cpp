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
#include <array>

#include "MenuSystem.h"
#include "MenuExceptions.h"
#include "MenuConfig.h"
#include "TextInputItem.h"
#include "CheckBoxItem.h"

//#define PRINT_KEY


char getch() {
    char buf = 0;
    if(read(0, &buf, 1) < 0) perror ("read()");
    return (buf);
}

void print(uint8_t line, std::string text) {
	static std::array<std::string, 4> display;
	display[line] = text;
	std::cout << "\033[2J"; // ANSI escape code to clear screen
	std::cout << "\033[H";  // Move cursor to home position
	for (const auto &s : display)  std::cout << s << std::endl;
}

bool captureKeys(MenuSystem& menu){
	char key = getch();
	switch(key) {
	case 65:		menu.Input(MenuNav::ARROW_DOWN);	    break;
	case 66:		menu.Input(MenuNav::ARROW_UP);	   		break;
	case 67:		menu.Input(MenuNav::ARROW_RIGHT);	    break;
	case 68:		menu.Input(MenuNav::ARROW_LEFT);	    break;
	case 127:		menu.Input(MenuNav::BACKSPACE_KEY);		break;
	case 10:		menu.Input(MenuNav::ENTER_KEY);			break;
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

/////////////////////////////////////////////////

struct test_st{
	uint8_t test_val;
	std::string test_string;
};

void testHandler(void* args, size_t len){
	if(len > 0){
		test_st * _args = (test_st*)args;
		std::cout << "value:" << _args->test_string
				<< " ----- n:" << (int)_args->test_val<<std::endl; sleep(1);
	}
}

////////////////////////////////////////////////

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
		//////// for Text input item
		test_st test;
		test.test_val = 0;
		test.test_string = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. "
				"Aenean commodo ligula eget dolor. Aenean massa. "
				"Cum sociis natoque penatibus et magnis dis";

		///////// for Chek Items
		bool options[3] = {false};

		//---------------------- example -------------------//
		MenuConfig config(print);
		MenuSystem m( {
			new MenuItem("Void item"),
			new SubMenu("Sub Menu", {
					new MenuItem("void item 2"),
					new SubMenu("Sub-SubMenu", {new MenuItem("void item 3")})
				}),
			new TextInputItem("Text input", testHandler, (void*)&test, sizeof(test_st)),
			new CheckBoxItem("check box", {
					{options, "option 1"},
					{options+1,"option 2"},
					{options+2,"option 3"}
				})
		});

		m.Start();
		while(!captureKeys(m)){
			usleep(10000);
			test.test_val++;
		}
	} catch (MenuException &e) {
		std::cout << e.what() << std::endl;
	}

	tcsetattr(STDOUT_FILENO, TCSANOW, &oldTermios);

	std::cout << "\033[2J" << "\033[H" << "Program Ended" << std::endl;
	return 0;
}

