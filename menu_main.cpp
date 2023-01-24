#include "menu_main.h"

const char* itemFile = "File";
const char* itemOpen = "Open";
const char* itemExit = "Exit";
const char* itemParameters = "Parameters";
const char* itemParam1 = "Parameter1";
const char* itemParam2 = "Parameter2";

const MenuNode menu1[] = {
//            id  |   parentId |           name |   value   |
	{       File,   RootMenuId,        itemFile,  nullptr, },
	{ Parameters,   RootMenuId,  itemParameters,  nullptr, },
	{       Open,         File,        itemOpen,  nullptr, },
	{       Exit,         File,        itemExit,  nullptr, },
	{     Param1,   Parameters,      itemParam1,  nullptr, },
	{     Param1,   Parameters,      itemParam2,  nullptr, },
	{   NoMenuId,     NoMenuId,         nullptr,  nullptr, },
};

const MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------
