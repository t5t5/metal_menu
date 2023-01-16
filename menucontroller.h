#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>

#include "menumodel.h"


using MenuHandler = void(int);

class MenuController
{
public:
	MenuController();
	~MenuController() = default;

	void setHandlers(MenuHandler* handlers);
	void setMenuModel(MenuModel* model);

	void up();		// на уровень выше, к предку
	void down();	// на уровень ниже, к первому child'у
	void right();	// к следующему пункту, child'у
	void left();	// к предыдущему пункту, child'у
protected:
	void handle();
	void paint();
private:
	MenuModel* model;
	MenuHandler* handlers;
	int menuId;
	int childerCount;
};

#endif // MENUCONTROLLER_H
