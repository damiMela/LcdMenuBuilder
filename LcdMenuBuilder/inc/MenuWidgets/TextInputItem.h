/*
 * TextInputItem.h
 *
 *  Created on: Jan 31, 2024
 *      Author: damimela
 */

#ifndef TEXTINPUTITEM_H_
#define TEXTINPUTITEM_H_

#include "MenuItem.h"
#include <memory>

class TextInputItem : public MenuItem
{
public:
	TextInputItem(const std::string title, std::string &buffer);
	TextInputItem(const std::string title, std::function<void(TextInputItem *)> callback);
	virtual ~TextInputItem();

	void Render() override;
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override;
	void Cancel() override;

	std::string GetCurrentText() { return buffer; }
	void ClearText();
	void SetText(const std::string &text);

private:
	std::string *savedText = nullptr;
	std::string buffer;
	int8_t cursorPos = 0;
	bool firstPrint = true;

	inline uint8_t displayTxtLen() { return MenuConfig::width - 2; }
};

#endif /* TEXTINPUTITEM_H_ */
