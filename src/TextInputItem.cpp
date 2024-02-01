/*
 * TextInputItem.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: damimela
 */

#include "TextInputItem.h"

TextInputItem::TextInputItem(std::string title, std::function<void(void*, size_t)> callback):
	MenuItem(title){
	this->SetCallback(callback);
}

TextInputItem::TextInputItem(std::string title, std::function<void(void*, size_t)> callback,
		void* funcArgs, size_t funcArgsLen): MenuItem(title){
	this->SetCallback(callback);
	args = funcArgs;
	argsLen = funcArgsLen;
}

TextInputItem::~TextInputItem() {
	buffer.clear();
}


void TextInputItem::Input(MenuNav::MenuNavInput_e input){
	switch(input){
	case MenuNav::CANCEL_KEY:
		navStack.back()->Cancel();
		buffer.clear();
		firstPrint = true;
		break;
	case MenuNav::BACKSPACE_KEY:
		if(buffer.size())
			buffer.pop_back();
		break;
	case MenuNav::ENTER_KEY:
		this->Execute();
	}
};


void TextInputItem::Render(){
	MenuConfig::print(0, this->GetTitle());
	MenuConfig::print(1, "::"+buffer);

	if(firstPrint){
		firstPrint = false;
		MenuConfig::print(2, "");
		MenuConfig::print(3, "");
	}
};

