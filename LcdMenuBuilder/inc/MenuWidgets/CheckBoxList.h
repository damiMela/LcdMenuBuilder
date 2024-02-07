/*
 * CheckBoxItem.h
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#ifndef CHECKBOXLIST_H_
#define CHECKBOXLIST_H_

#include "MenuItem.h"
#include <vector>
#include <memory>

class CheckBoxList : public MenuItem
{
public:
	CheckBoxList(const std::string title, std::vector<bool> &selectedItems, std::initializer_list<std::string> list);
	virtual ~CheckBoxList();

	void Render() override;
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override{};

private:
	std::vector<std::string> itemsText;
	std::shared_ptr<std::vector<bool>> itemsState;
	uint8_t currSelection = 0;
	int8_t printStartPoint = 0;

	constexpr uint8_t secureId(uint8_t id)
	{
		return ((int8_t)id < 0) ? 0 : ((id > itemsText.size() - 1) ? (itemsText.size() - 1) : id);
	}
};

#endif /* CHECKBOXLIST_H_ */
