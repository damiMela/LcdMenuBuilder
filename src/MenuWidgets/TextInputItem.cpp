/*
 * TextInputItem.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: damimela
 */

#include <MenuWidgets/TextInputItem.h>

TextInputItem::TextInputItem(const std::string title, std::string& output):
	MenuItem(title), bufferRef(output){
	buffer = bufferRef;
}

TextInputItem::TextInputItem(const std::string title, std::function<void(TextInputItem*)> callback):
	MenuItem(title), bufferRef(buffer){
	this->SetCallback([callback](MenuItem* item) {
        callback(static_cast<TextInputItem*>(item));
    });
}


TextInputItem::~TextInputItem() {
}


void TextInputItem::Input(MenuNav::MenuNavInput_e input){
	switch(input){
	case MenuNav::CANCEL_KEY:
		navStack.back()->Cancel();
		firstPrint = true;
		break;
	case MenuNav::BACKSPACE_KEY:
		if(buffer.size())
			buffer.pop_back();
		break;
	case MenuNav::ENTER_KEY:
		if(&bufferRef != &buffer)	bufferRef = buffer;
		if(this->callback) 			this->Execute();
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

