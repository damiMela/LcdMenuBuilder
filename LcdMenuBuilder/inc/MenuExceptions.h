/*
 * MenuExceptions.h
 *
 *  Created on: Jan 24, 2024
 *      Author: damimela
 */

#ifndef INC_MENUEXCEPTIONS_H_
#define INC_MENUEXCEPTIONS_H_

#include <exception>

class MenuException : public std::exception {};

class NoMenuSystem : public MenuException {
    public:
	const char* what() const noexcept override { return "No menu system declaration was found."; }
};

class NoMainMenu: public MenuException {
    public:
	const char* what() const noexcept override { return "MAIN_MENU declaration missing"; }
};




#endif /* INC_MENUEXCEPTIONS_H_ */
