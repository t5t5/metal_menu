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
	Network,
	BaudRateInt,
	BaudRateEnum,
	BaudRateText,
	ParamIP,
	ParamIP2,
	Languages,
	RandomInt,
	RandomFloat,
	RusLang,
	EngLang,
	RusEngLang,
};

extern MenuNode* mainMenu;

#endif // MENU_FILE_H
