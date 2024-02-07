/*
 * MenuConfig.h
 *
 *  Created on: Jan 29, 2024
 *      Author: damimela
 */

#ifndef INC_MENUCONFIG_H_
#define INC_MENUCONFIG_H_

#include "Menu_common.h"
#include <functional>
#include <mutex>




class MenuConfig{
private:
	static std::mutex printMutex;
	static std::function<void(uint8_t, std::string)> printLineCall;

public:
	static uint8_t width;
	static uint8_t heigth;

	static void print(uint8_t line, std::string text){
		std::unique_lock<std::mutex> lock(printMutex);
		printLineCall(line, text);
	}

	static void SetPrintCallback(std::function<void(uint8_t, std::string)> pirntMethod){
		printLineCall = pirntMethod;
	}


};


#endif /* INC_MENUCONFIG_H_ */
