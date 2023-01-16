#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

class MenuHandler
{
public:
	MenuHandler(const MenuHandlerItem* handlerItems);

	void process(int id) const;
private:
	const MenuHandlerItem* handlerItems;
	const int handlerCount;
};

#endif // MENUHANDLER_H
