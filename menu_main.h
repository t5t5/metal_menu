#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

enum MenuIds
{
	File = 0,
	Edit = 1,
	View = 2,
	Save = 3,
	Open = 4,
	Exit = 5,
	Undo = 6,
	Redo = 7,
	View1 = 8,
	View2 = 9,
};

extern const MenuNode* mainMenu;

extern const MenuHandlerItem* mainMenuHandlers;

#endif // MENU_FILE_H
