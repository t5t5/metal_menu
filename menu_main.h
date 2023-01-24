#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

enum MenuIds
{
	File = RootMenuId + 1,
	Open,
	Exit,
	Parameters,
	Param1,
	Param2,
};

extern const MenuNode* mainMenu;

#endif // MENU_FILE_H
