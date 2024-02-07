/*
 * RadioList.cpp
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#include <MenuWidgets/RadioList.h>
#include <sstream>

RadioList::RadioList(const std::string title, uint8_t &selectedId, std::initializer_list<std::string> list) : MenuItem(title), items(list)
{
	activeItem = std::shared_ptr<uint8_t>(&selectedId);
}

RadioList::RadioList(const std::string title, std::function<void(RadioList *)> callback, std::initializer_list<std::string> list) : MenuItem(title), items(list)
{
	activeItem = std::make_shared<uint8_t>(0);
	this->SetCallback([callback](MenuItem *item)
					  { callback(static_cast<RadioList *>(item)); });
}

RadioList::~RadioList()
{
	// TODO Auto-generated destructor stub
}

void RadioList::Render(void)
{
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
		{
			std::stringstream os;
			os << "(" << (i + printStartPoint == *activeItem ? "X" : " ") << ") > " + items[i + printStartPoint];
			MenuConfig::print(i, os.str());
		}
		else
		{
			std::stringstream os;
			os << "(" << (i + printStartPoint == *activeItem ? "X" : " ") << ") " + items[i + printStartPoint];
			MenuConfig::print(i, os.str());
		}
	}
}

void RadioList::Input(MenuNav::MenuNavInput_e input)
{
	switch (input)
	{
	case MenuNav::ARROW_UP:
		currSelection = secureId(currSelection + 1);
		break;
	case MenuNav::ARROW_DOWN:
		currSelection = secureId(currSelection - 1);
		break;
	case MenuNav::BACKSPACE_KEY:
	case MenuNav::CANCEL_KEY:
	case MenuNav::ARROW_LEFT:
	case MenuNav::ARROW_RIGHT:
		navStack.back()->Cancel();
		break;
	case MenuNav::ENTER_KEY:
		*activeItem = currSelection;
		this->Render();
		if (callback)
			this->Execute();
		break;
	}
}
