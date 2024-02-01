/*
 * MenuSystem.cpp
 *
 *  Created on: Jan 24, 2024
 *      Author: damimela
 */

#include "MenuSystem.h"
#include "MenuExceptions.h"
#include "MenuConfig.h"

#include <fstream>

#define MENU_SYSTEM_NAME "menuSystem"
#define MAIN_MENU_ID	1

bool MenuSystem::started = false;

MenuSystem::MenuSystem(std::initializer_list<MenuItem*> list, bool freeItemsOnDestroy) :
		SubMenu("main menu", list, freeItemsOnDestroy){

	currMenuId = MAIN_MENU_ID;
	navStack.push_back(this);
}

MenuSystem::~MenuSystem() {
	navStack.clear();
}


bool MenuSystem::Start(
			uint8_t width,uint8_t heigth){
	MenuConfig::width = width;
	MenuConfig::heigth = heigth;
	MenuSystem::started = true;


	Render();
	return true;
}

void MenuSystem::Input(MenuNav::MenuNavInput_e input){
	if(navStack.size() == 1)
		SubMenu::Input(input);
	else
		navStack.back()->Input(input);

	navStack.back()->Render();
}

void MenuSystem::Input(char input){
	if(navStack.size() == 1)
		SubMenu::Input(input);
	else
		navStack.back()->Input(input);
	navStack.back()->Render();
}
