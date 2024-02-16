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
#define MAIN_MENU_ID 1

bool MenuSystem::started = false;

MenuSystem::MenuSystem(std::vector<std::shared_ptr<MenuItem>> list) : SubMenu("main menu", list)
{
	currMenuId = MAIN_MENU_ID;
}

MenuSystem::~MenuSystem()
{
	navStack.clear();
}

bool MenuSystem::Start(
	uint8_t width, uint8_t heigth)
{
	MenuConfig::width = width;
	MenuConfig::heigth = heigth;
	MenuSystem::started = true;

	SubMenu::Render();
	return true;
}

void MenuSystem::Input(MenuNav::MenuNavInput_e input)
{
	if (navStack.size() > 0)
		navStack.back()->Input(input);
	else
		SubMenu::Input(input);

	if (navStack.size() > 0)
		navStack.back()->Render();
	else
		SubMenu::Render();
}

void MenuSystem::Input(char input)
{
	if (navStack.size() > 0)
		navStack.back()->Input(input);
	else
		SubMenu::Input(input);

	if (navStack.size() > 0)
		navStack.back()->Render();
	else
		SubMenu::Render();
}
