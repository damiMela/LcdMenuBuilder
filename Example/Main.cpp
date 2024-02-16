//============================================================================
// Name        : LCDMenuBuilder.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "MenuWidgets/CheckBoxList.h"
#include "MenuWidgets/RadioList.h"
#include "MenuWidgets/TextInputItem.h"
#include <array>

#include "MenuSystem.h"
#include "MenuExceptions.h"

// #define PRINT_KEY

char getch()
{
	char buf = 0;
	if (read(0, &buf, 1) < 0)
		perror("read()");
	return (buf);
}

void print(uint8_t line, std::string text)
{
	static std::array<std::string, 4> display;
	display[line] = text;
	std::cout << "\033[2J"; // ANSI escape code to clear screen
	std::cout << "\033[H";	// Move cursor to home position
	std::cout << "--------------------" << std::endl;
	for (const auto &s : display)
		std::cout << s << std::endl;
}

bool captureKeys(MenuSystem &menu)
{
	char key = getch();
	switch (key)
	{
	case 65:
		menu.Input(MenuNav::ARROW_UP);
		break;
	case 66:
		menu.Input(MenuNav::ARROW_DOWN);
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
		if (MenuItem::NavStackSize() > 0)
		{
			menu.Input(MenuNav::CANCEL_KEY);
			return false;
		}
		return true;

	default:
		if (std::isalnum(key) || std::isspace(key))
			menu.Input(key);
		break;
	}
#ifdef PRINT_KEY
	std::cout << "Key:" << (int)key << std::endl;
	sleep(1);
#endif
	return false;
}

/////////////////////////////////////////////////

void testTextHandler(TextInputItem *input)
{
	std::cout << input->GetCurrentText() << std::endl;
	sleep(1);
	input->ClearText(); // clear buffer
	input->Cancel();	// exit widget
}

void testRadioListHandler(RadioList *input)
{
	std::cout << "selected option: " << (uint)input->GetCurrentSelection() << std::endl;
	sleep(1);
}

////////////////////////////////////////////////

int main()
{
	struct termios oldTermios, newTermios;

	tcgetattr(STDOUT_FILENO, &oldTermios);

	newTermios = oldTermios;
	newTermios.c_lflag &= ~ECHO;   // Turn off echo
	newTermios.c_lflag &= ~ICANON; // Turn off canonical mode
	newTermios.c_cc[VMIN] = 1;
	newTermios.c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSANOW, &newTermios);

	try
	{
		///////// for textInput
		std::string buffer = "hello world";

		///////// for Chek Items
		std::vector<std::string> CheckBoxOptions = {"option A", "option B", "option C"};
		std::vector<bool> checkListReuslt(3);

		///////// for radio list
		std::vector<std::string> RadioOptions = {"option 1", "option 2", "option 3"};
		uint8_t selectedId = 0;

		///////// Shared item
		std::vector<std::string> SharedRadioOptions = {"Shared", "item", "test"};
		uint8_t SharedSelectedId = 0;
		auto sharedItem = std::make_shared<RadioList>("Shared radio list", SharedSelectedId, SharedRadioOptions);

		///////// Sub menus
		std::vector<std::shared_ptr<MenuItem>> subSubMenu{
			std::make_shared<MenuItem>("Void item 3"),
			sharedItem};

		std::vector<std::shared_ptr<MenuItem>> subMenu{
			std::make_shared<MenuItem>("Void item 2"),
			sharedItem,
			std::make_shared<SubMenu>("Sub-SubMenu", subSubMenu)};

		MenuSystem::SetPrintCallback(print);
		MenuSystem m({std::make_shared<MenuItem>("Void item"),
					  std::make_shared<TextInputItem>("Text input (handler)", testTextHandler),
					  std::make_shared<TextInputItem>("Text input (shared)", buffer),
					  std::make_shared<CheckBoxList>("check box", checkListReuslt, CheckBoxOptions),
					  std::make_shared<RadioList>("radio list", selectedId, RadioOptions),
					  std::make_shared<SubMenu>("Sub Menu", subMenu)});

		m.Start();
		while (!captureKeys(m))
		{
			usleep(10000);
		}
	}
	catch (MenuException &e)
	{
		std::cout << e.what() << std::endl;
	}

	tcsetattr(STDOUT_FILENO, TCSANOW, &oldTermios);

	std::cout << "\033[2J"
			  << "\033[H"
			  << "Program Ended" << std::endl;
	return 0;
}
