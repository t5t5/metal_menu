#ifndef MENUDEFINES_H
#define MENUDEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>

using MenuId = char;
using MenuFunction = std::function<void(int)>;

struct MenuNode
{
	MenuId id;
	MenuId parentId;
	MenuId leftId;
	MenuId rightId;
	MenuId childId;
	const char* name;
};

struct MenuHandlerItem
{
	MenuFunction function;
	MenuId id;

	MenuHandlerItem(MenuId i, MenuFunction f) : function(f) , id(i) { }
};

#endif // MENUNODE_H
