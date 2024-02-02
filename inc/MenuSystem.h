/*
 * MenuSystem.h
 *
 *  Created on: Jan 24, 2024
 *      Author: damimela
 */

#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_

#include "Menu_common.h"
#include "SubMenu.h"
#include <functional>

class MenuSystem : public SubMenu{
public:
	MenuSystem(std::initializer_list<MenuItem*> list, bool freeItemsOnDestroy = true);
	virtual ~MenuSystem();

	bool Start(uint8_t width = 20,uint8_t heigth = 4);
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override;

	static void SetPrintCallback(std::function<void(uint8_t, std::string)> pirntMethod){
		MenuConfig::SetPrintCallback(pirntMethod);
	}

private:
	static bool started;
	uint8_t currMenuId = 0;

	void Render(){SubMenu::Render();}
	void Execute(){SubMenu::Execute();}
	void Cancel(){}

};

#endif /* MENUSYSTEM_H_ */
