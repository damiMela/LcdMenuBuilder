/*
 * TextInputItem.cpp
 *
 *  Created on: Jan 31, 2024
 *      Author: damimela
 */

#include "MenuWidgets/TextInputItem.h"

TextInputItem::TextInputItem(const std::string title, std::string &output) : MenuItem(title)
{
	buffer = std::string(output);
	savedText = &output;
}

TextInputItem::TextInputItem(const std::string title,
							 std::function<void(TextInputItem *)> callback) : MenuItem(title),
																			  savedText(nullptr)
{
	buffer = std::string("");
	this->SetCallback([callback](MenuItem *item)
					  { callback(static_cast<TextInputItem *>(item)); });
}

TextInputItem::~TextInputItem()
{
}

void TextInputItem::Input(MenuNav::MenuNavInput_e input)
{
	switch (input)
	{
	case MenuNav::CANCEL_KEY:
		navStack.back()->Cancel();
		break;
	case MenuNav::BACKSPACE_KEY:
		if (buffer.size())
			buffer.pop_back();
		if (cursorPos)
			cursorPos--;
		break;
	case MenuNav::ENTER_KEY:
		if (savedText)
			*savedText = buffer;
		if (this->callback)
			this->Execute();
		break;

	case MenuNav::ARROW_RIGHT:
		if (buffer.size() < MenuConfig::width)
			break;
		if (cursorPos > (displayTxtLen() - buffer.size()))
			break;
		cursorPos++;
		break;

	case MenuNav::ARROW_LEFT:
		if (buffer.size() < MenuConfig::width)
			break;
		if (cursorPos < 1)
			break;
		cursorPos--;
		break;
	}
};

void TextInputItem::Input(char input)
{
	buffer.push_back(input);
	if (buffer.size() <= displayTxtLen())
		return;
	cursorPos++;
}

void TextInputItem::Cancel()
{
	firstPrint = true;
	if (savedText)
	{
		buffer = *savedText;
		cursorPos = (savedText->size() > displayTxtLen())
						? savedText->size() - displayTxtLen()
						: 0;
	}
	MenuItem::Cancel();
}

void TextInputItem::Render()
{
	MenuConfig::print(0, this->GetTitle());
	if (buffer.size() <= displayTxtLen())
		MenuConfig::print(1, "::" + buffer);
	else
		MenuConfig::print(1, "::" + buffer.substr(cursorPos, displayTxtLen()));

	if (firstPrint)
	{
		firstPrint = false;
		MenuConfig::print(2, "");
		MenuConfig::print(3, "");
	}
};

void TextInputItem::ClearText()
{
	buffer.clear();
	if (savedText)
		savedText->clear();
};
void TextInputItem::SetText(const std::string &text)
{
	buffer = text;
	if (savedText)
		*savedText = text;
}