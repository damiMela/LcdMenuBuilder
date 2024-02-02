/*
 * CheckBoxItem.cpp
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#include <MenuWidgets/CheckBoxList.h>
#include <sstream>


CheckBoxList::CheckBoxList(const std::string title, std::vector<bool>& selectedItems,
		std::initializer_list<std::string> list) :
				MenuItem(title),
				itemsText(list),
				itemsStateRef(selectedItems){
	if(itemsStateRef.size() == itemsText.size()){
		itemsState = itemsStateRef;
		return;
	}

	for(size_t i = 0; i < itemsText.size(); i++)
		itemsState.push_back(false);
	itemsStateRef = itemsState;
}

CheckBoxList::~CheckBoxList() {
	// TODO Auto-generated destructor stub
}


void CheckBoxList::Render(void){
	if(currSelection >= printStartPoint+MenuConfig::heigth)
		printStartPoint++;

	if(printStartPoint+MenuConfig::heigth > (int)itemsText.size()-1)
		printStartPoint = itemsText.size()-MenuConfig::heigth;

	if(currSelection < printStartPoint)
		printStartPoint--;

	if(printStartPoint < 0)
		printStartPoint = 0;

	for (uint8_t i = 0; i < MenuConfig::heigth; i++) {
		if (i >= itemsText.size())
			MenuConfig::print(i, "");
		else if(i+printStartPoint == currSelection){
			std::stringstream os;
			os << "[" << (itemsState[i+printStartPoint] ? "X" : " ") << "] > " + itemsText[i+printStartPoint];
			MenuConfig::print(i, os.str());
		}
		else{
			std::stringstream os;
			os << "[" << (itemsState[i+printStartPoint] ? "X" : " ") << "] " + itemsText[i+printStartPoint];
			MenuConfig::print(i, os.str());
		}
	}
}


void CheckBoxList::Input(MenuNav::MenuNavInput_e input){
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
		itemsState[currSelection] = !itemsState[currSelection];
		if(&itemsState != &itemsStateRef) itemsStateRef[currSelection]=itemsState[currSelection];
		break;

	}
}
