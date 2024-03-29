/*
 * SubMenu.cpp
 *
 *  Created on: Jan 25, 2024
 *      Author: damimela
 */

#include "MenuWidgets/SubMenu.h"
#include "MenuConfig.h"

SubMenu::SubMenu(const std::string title, std::vector<std::shared_ptr<MenuItem>> list) : MenuItem(title),
																						 navStack(MenuItem::navStack),
																						 items(list)
{
}

SubMenu::~SubMenu()
{
	items.clear();
}

void SubMenu::Render(void)
{
	static int8_t printStartPoint = 0;
	if (currSelection >= printStartPoint + MenuConfig::heigth)
		printStartPoint++;

	if (printStartPoint + MenuConfig::heigth > (int)items.size() - 1)
		printStartPoint = items.size() - MenuConfig::heigth;

	if (currSelection < printStartPoint)
		printStartPoint--;

	if (printStartPoint < 0)
		printStartPoint = 0;

	for (uint8_t i = 0; i < MenuConfig::heigth; i++)
	{
		if (i >= items.size())
			MenuConfig::print(i, "");
		else if (i + printStartPoint == currSelection)
			MenuConfig::print(i, "> " + items[i + printStartPoint]->GetTitle());
		else
			MenuConfig::print(i, items[i + printStartPoint]->GetTitle());
	}
}

void SubMenu::Execute()
{
	navStack.push_back(items[currSelection]);
}

void SubMenu::Cancel()
{
	if (navStack.size())
		navStack.pop_back();
}

void SubMenu::Input(MenuNav::MenuNavInput_e input)
{
	switch (input)
	{
	case MenuNav::ARROW_UP:
		currSelection = secureId(currSelection - 1);
		break;
	case MenuNav::ARROW_DOWN:
		currSelection = secureId(currSelection + 1);
		break;
	case MenuNav::BACKSPACE_KEY:
	case MenuNav::CANCEL_KEY:
	case MenuNav::ARROW_LEFT:
		if (navStack.size())
			navStack.back()->Cancel();
		break;
	case MenuNav::ENTER_KEY:
	case MenuNav::ARROW_RIGHT:
		if (navStack.size())
			navStack.back()->Execute();
		else
			SubMenu::Execute();
		break;
	}
}

void SubMenu::Input(char input)
{
	return;
}
