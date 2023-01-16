#include "menuhandler.h"

int sizeOfHandlers(const MenuHandlerItem* h)
{
	int i = 0;
	while((h + i++)->id != -1);
	return i;
}

MenuHandler::MenuHandler(const MenuHandlerItem* h)
	: handlerItems(h)
	, handlerCount(sizeOfHandlers(h))
{
}
