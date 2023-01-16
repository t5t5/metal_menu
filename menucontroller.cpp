#include "menucontroller.h"


MenuController::MenuController()
	: model(nullptr)
	, handlers(nullptr)
	, menuId(-1)
	, childerCount(0)
{
}

void MenuController::setHandlers(MenuHandler* h)
{
	handlers = h;
}

void MenuController::setMenuModel(MenuModel* m)
{
	if (model == m) { return; }
	model = m;
	if (model == nullptr) {
		menuId = -1;
		childerCount = 0;
	} else {
		menuId = 0;
		childerCount = model->childrenCount(menuId);
	}
	handle();
	paint();
}

void MenuController::up()
{
	if (model == nullptr) { return; }
	if (!model->hasParent(menuId)) { return; }
	menuId = model->parent(menuId);
	handle();
	paint();
}

void MenuController::down()
{
	if (model == nullptr) { return; }
	if (!model->hasChild(menuId)) { return; }
	menuId = model->child(menuId);
	handle();
	paint();
}

void MenuController::right()
{
	if (model == nullptr) { return; }
	if (!model->hasNext(menuId)) { return; }
	menuId = model->next(menuId);
	handle();
	paint();
}

void MenuController::left()
{
	if (model == nullptr) { return; }
	if (!model->hasPrevious(menuId)) { return; }
	menuId = model->previous(menuId);
	handle();
	paint();
}

void MenuController::handle()
{
}

void MenuController::paint()
{
}
