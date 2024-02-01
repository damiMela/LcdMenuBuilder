/*
 * CheckBoxItem.h
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#ifndef CHECKBOXITEM_H_
#define CHECKBOXITEM_H_

#include "MenuItem.h"
#include <vector>
#include <map>


class CheckBoxItem : public MenuItem{
public:
	CheckBoxItem(std::string title, std::initializer_list<std::pair<bool*,const std::string>> list);
	virtual ~CheckBoxItem();

	void Render() override;
	void Input(MenuNav::MenuNavInput_e input) override;
	void Input(char input) override{};
private:
	std::vector<std::pair<bool*,const std::string>> items;
	uint8_t currSelection = 0;
	int8_t printStartPoint = 0;

	constexpr uint8_t secureId(uint8_t id){
		return ((int8_t)id < 0) ? 0 : ((id > items.size()-1) ? (items.size() -1) : id);
	}
};

#endif /* CHECKBOXITEM_H_ */
