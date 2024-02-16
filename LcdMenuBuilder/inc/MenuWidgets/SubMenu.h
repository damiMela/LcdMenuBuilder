/*
 * SubMenu.h
 *
 *  Created on: Jan 25, 2024
 *      Author: damimela
 */

#ifndef SUBMENU_H_
#define SUBMENU_H_

#include "MenuItem.h"
#include <vector>
#include <memory>

class SubMenu : public MenuItem
{
public:
	SubMenu(const std::string title, std::vector<std::shared_ptr<MenuItem>> list);
	virtual ~SubMenu();

	inline size_t Size() { return items.size(); }
	inline std::shared_ptr<MenuItem> Item(menuId id) { return items[secureId(id)]; }
	inline void SetSelection(menuId id) { currSelection = secureId(id); }
	inline uint8_t GetSelection() { return currSelection; }

	virtual void Render() override;
	virtual void Execute() override;
	virtual void Cancel() override;
	virtual void Input(MenuNav::MenuNavInput_e input) override;
	virtual void Input(char input) override;

protected:
	uint8_t currSelection = 0;
	std::vector<std::shared_ptr<MenuItem>> items;
	NavStack &navStack;

	constexpr uint8_t secureId(uint8_t id)
	{
		return ((int8_t)id < 0) ? 0 : ((id > items.size() - 1) ? (items.size() - 1) : id);
	}
};

#endif /* SUBMENU_H_ */
