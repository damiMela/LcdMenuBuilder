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
	TextInputItem(const std::string title, std::string& buffer);
	TextInputItem(const std::string title, std::function<void(TextInputItem*)> callback);
	virtual ~TextInputItem();

	void Render() override;
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override{ buffer+=input; };
	void Cancel() override{
		MenuItem::Cancel();
		firstPrint = true;
	}

	std::string GetCurrentText() {return buffer;}
	void ClearText(){buffer.clear();};
	void SetText(const std::string& text) {buffer = text;}

private:
	std::string buffer;
	std::string& bufferRef;
	bool firstPrint = true;

};

#endif /* TEXTINPUTITEM_H_ */
