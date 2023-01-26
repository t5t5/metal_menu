#include "menu_main.h"

const char* itemFile = "File";
const char* itemOpen = "Open";
const char* itemExit = "Exit";
const char* itemParameters = "Parameters";
const char* itemParam1 = "Parameter1";
const char* itemParam2 = "Parameter2";
const char* itemParam3 = "Parameter3";
const char* itemResetParam3 = "Reset Parameter3";

static int param3 = 100;

static NumberMenuValue<int> param3value(&param3);
static SetValueMenuAction<int> param3reset(&param3, 100);

const MenuNode menu1[] = {
//             id  |   parentId |           name |        value |      action
	{        File,   RootMenuId,        itemFile,       nullptr,      nullptr, },
	{  Parameters,   RootMenuId,  itemParameters,       nullptr,      nullptr, },
	{      Param3,   RootMenuId,      itemParam3,  &param3value,      nullptr, },
	{ ResetParam3,   RootMenuId, itemResetParam3,       nullptr, &param3reset, },
	{        Open,         File,        itemOpen,       nullptr,      nullptr, },
	{        Exit,         File,        itemExit,       nullptr,      nullptr, },
	{      Param1,   Parameters,      itemParam1,       nullptr,      nullptr, },
	{      Param2,   Parameters,      itemParam2,       nullptr,      nullptr, },
	{    NoMenuId,     NoMenuId,         nullptr,       nullptr,      nullptr, },
};

const MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------
