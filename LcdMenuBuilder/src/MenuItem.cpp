/*
 * MenuSelection.cpp
 *
 *  Created on: Jan 25, 2024
 *      Author: damimela
 */

#include <MenuItem.h>

uint8_t MenuItem::globalItemCounter  = 2;
NavStack MenuItem::navStack;


MenuItem::MenuItem(std::string title) :
		title(title),  id(globalItemCounter){

	globalItemCounter++;
}

MenuItem::~MenuItem() {
	// TODO Auto-generated destructor stub
}

