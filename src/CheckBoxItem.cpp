/*
 * CheckBoxItem.cpp
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#include "CheckBoxItem.h"
#include <sstream>


CheckBoxItem::CheckBoxItem(std::string title, std::initializer_list<std::pair<bool*,const std::string>> list) :
				MenuItem(title), items(list){
	// TODO Auto-generated constructor stub

}

CheckBoxItem::~CheckBoxItem() {
	// TODO Auto-generated destructor stub
}


void CheckBoxItem::Render(void){
	if(currSelection >= printStartPoint+MenuConfig::heigth)
		printStartPoint++;

	if(printStartPoint+MenuConfig::heigth> items.size()-1)
		printStartPoint = items.size()-MenuConfig::heigth;

	if(currSelection < printStartPoint)
		printStartPoint--;

	if(printStartPoint < 0)
		printStartPoint = 0;

	for (uint8_t i = 0; i < MenuConfig::heigth; i++) {
		if (i >= items.size())
			MenuConfig::print(i, "");
		else if(i+printStartPoint == currSelection){
			std::stringstream os;
			os << "[" << (*items[i+printStartPoint].first ? "X" : " ") << "] > " + items[i+printStartPoint].second;
			MenuConfig::print(i, os.str());
		}
		else{
			std::stringstream os;
			os << "[" << (*items[i+printStartPoint].first ? "X" : " ") << "] " + items[i+printStartPoint].second;
			MenuConfig::print(i, os.str());
		}
	}
}


void CheckBoxItem::Input(MenuNav::MenuNavInput_e input){
	switch(input){
	case MenuNav::ARROW_UP:
		currSelection = secureId(currSelection+1);
		break;
	case MenuNav::ARROW_DOWN:
		currSelection = secureId(currSelection-1);
		break;
	case MenuNav::BACKSPACE_KEY:
	case MenuNav::CANCEL_KEY:
	case MenuNav::ARROW_LEFT:
		navStack.back()->Cancel();
		break;
	case MenuNav::ENTER_KEY:
		*items[currSelection].first = !(*items[currSelection].first);
		break;

	}
}
