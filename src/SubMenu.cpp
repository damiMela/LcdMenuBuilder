/*
 * SubMenu.cpp
 *
 *  Created on: Jan 25, 2024
 *      Author: damimela
 */

#include "SubMenu.h"
#include "MenuConfig.h"

SubMenu::SubMenu(std::string title, std::initializer_list<MenuItem*> list,
		bool freeItemsOnDestroy) :
	MenuItem(title),
	items(list),
	navStack(MenuItem::navStack),
	freeItemsOnDestroy(freeItemsOnDestroy){

}


SubMenu::~SubMenu() {
	if(freeItemsOnDestroy){
		for(const auto& item : items){
			delete item;
		}
	}
	items.clear();
}


void SubMenu::Render(void){
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
		else if(i+printStartPoint == currSelection)
			MenuConfig::print(i, "> " + items[i+printStartPoint]->GetTitle());
		else
			MenuConfig::print(i, items[i+printStartPoint]->GetTitle());
	}
}


void SubMenu::Execute(){
	navStack.push_back(items[currSelection]);
}

void SubMenu::Cancel(){
	if(navStack.size() > 1)
		navStack.pop_back();
}

void SubMenu::Input(MenuNav::MenuNavInput_e input){
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
	case MenuNav::ARROW_RIGHT:
		navStack.back()->Execute();
		break;
	}
}

void SubMenu::Input(char input){
	return;
}

