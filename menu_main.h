#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

enum MenuIds
{
	Application = RootMenuId + 1,
	Message,
	Version,
	Exit,
	Parameters,
	Param1,
	BaudRateInt,
	BaudRateEnum,
	BaudRateText,
	Param3,
	ResetParam3,
	Languages,
	RusLang,
	EngLang,
};

extern MenuNode* mainMenu;

#endif // MENU_FILE_H
