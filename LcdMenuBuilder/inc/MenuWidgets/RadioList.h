/*
 * RadioList.h
 *
 *  Created on: Feb 1, 2024
 *      Author: damimela
 */

#ifndef RADIOLIST_H_
#define RADIOLIST_H_

#include "MenuItem.h"
#include <vector>
class RadioList : public MenuItem{
public:
	RadioList(const std::string titile, uint8_t& selectedId, std::initializer_list<std::string> list);
	RadioList(const std::string titile, std::function<void(RadioList*)> callback, std::initializer_list<std::string> list);
	virtual ~RadioList();

	virtual void Render() override;
	virtual void Input(MenuNav::MenuNavInput_e input) override;

	uint8_t GetCurrentSelection() {return activeItem;}
	std::string GetOptionTitile(uint8_t id) { return items[secureId(id)];}

private:
	int8_t printStartPoint = 0;
	uint8_t currSelection = 0;

	std::vector<std::string> items;
	uint8_t activeItem;
	uint8_t& activeItemRef;


	constexpr uint8_t secureId(uint8_t id){
		return ((int8_t)id < 0) ? 0 : ((id > items.size()-1) ? (items.size() -1) : id);
	}
};

#endif /* RADIOLIST_H_ */
