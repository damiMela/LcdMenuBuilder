/*
 * MenuSelection.h
 *
 *  Created on: Jan 25, 2024
 *      Author: damimela
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "Menu_common.h"
#include "MenuConfig.h"
#include <functional>
#include <memory>

namespace MenuNav
{
	typedef enum
	{
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		ENTER_KEY,
		CANCEL_KEY,
		BACKSPACE_KEY
	} MenuNavInput_e;
}

class MenuItem;
typedef uint8_t menuId;
typedef std::list<std::shared_ptr<MenuItem>> NavStack;

class MenuItem
{
public:
	MenuItem(const std::string title);

	virtual ~MenuItem();
	virtual void Execute() { callback(this); }
	virtual void Cancel() { navStack.pop_back(); }
	virtual void Input(char input){};
	virtual void Render()
	{
		for (int i = 0; i < MenuConfig::heigth; i++)
			MenuConfig::print(i, "");
	}
	virtual void Input(MenuNav::MenuNavInput_e input)
	{
		if (input == MenuNav::CANCEL_KEY)
			navStack.back()->Cancel();
	}

	menuId GetId() { return id; }
	std::string GetTitle() { return title; }
	static uint8_t NavStackSize() { return navStack.size(); }
	void SetCallback(std::function<void(MenuItem *)> callback) { this->callback = callback; };

protected:
	std::string title;
	menuId id;
	std::function<void(MenuItem *)> callback;
	void *args = nullptr;
	size_t argsLen = 0;

	static NavStack navStack;
	static uint8_t globalItemCounter;
	static void NullCallback()
	{
		std::cout << "default" << std::endl;
		sleep(1);
	}
};

#endif /* MENUITEM_H_ */
