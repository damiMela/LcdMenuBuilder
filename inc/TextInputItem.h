/*
 * TextInputItem.h
 *
 *  Created on: Jan 31, 2024
 *      Author: damimela
 */

#ifndef TEXTINPUTITEM_H_
#define TEXTINPUTITEM_H_

#include "MenuItem.h"

class TextInputItem : public MenuItem{
public:
	TextInputItem(std::string title, std::function<void(void*, size_t)> callback);
	TextInputItem(std::string title, std::function<void(void*, size_t)> callback, void* funcArgs, size_t funcArgsLen);
	virtual ~TextInputItem();

	void Render();
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override{ buffer+=input; };
	std::string buffer;

private:
	bool firstPrint = true;

};

#endif /* TEXTINPUTITEM_H_ */
