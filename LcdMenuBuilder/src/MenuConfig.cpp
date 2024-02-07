/*
 * MenuConfig.cpp
 *
 *  Created on: Jan 29, 2024
 *      Author: damimela
 */



#include "MenuConfig.h"

std::mutex MenuConfig::printMutex;
uint8_t MenuConfig::width;
uint8_t MenuConfig::heigth;
std::function<void(uint8_t, std::string)> MenuConfig::printLineCall;
