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

namespace MenuNav{
	typedef enum{
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		ENTER_KEY,
		CANCEL_KEY,
		BACKSPACE_KEY
	}MenuNavInput_e;
}

class MenuItem;
typedef uint8_t menuId;
typedef std::list<MenuItem*> NavStack;

class MenuItem {
public:
	MenuItem(std::string title);
	MenuItem(std::string title, void* args, size_t argsLen);
	void SetCallback(std::function<void(void*, size_t)> callback){ _callback=callback;};
	std::string GetTitle() { return title;	}
	menuId GetId(){return id;}
	static uint8_t NavStackSize() {return navStack.size();}

	virtual ~MenuItem();
	virtual void Execute() {	_callback(args, argsLen);	}
	virtual void Cancel(){ navStack.pop_back();}
	virtual void Input(char input){};
	virtual void Render(){
		for (int i = 0; i < MenuConfig::heigth; i++) MenuConfig::print(i, "");
	}
	virtual void Input(MenuNav::MenuNavInput_e input){
		if(input==MenuNav::CANCEL_KEY) navStack.back()->Cancel();
	}

protected:
	std::string title;
	menuId id;
	std::function<void(void*, size_t)>  _callback;
	void* args = nullptr;
	size_t argsLen = 0;

	static NavStack navStack;
	static uint8_t globalItemCounter;
	static void NullCallback(){ std::cout << "default" << std::endl; sleep(1);}

};


#endif /* MENUITEM_H_ */
