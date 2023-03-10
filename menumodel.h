#ifndef MENUMODEL_H
#define MENUMODEL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "eventhandler.h"
#include "menudefines.h"
#include "menumodelindex.h"

class MenuModel : public EventHandler
{
public:
	MenuModel(MenuNode* n, MenuId startId = RootMenuId);
	virtual ~MenuModel() override;

	MenuModelIndex index(int line, const MenuModelIndex& parent = MenuModelIndex()) const;
	MenuModelIndex idx(MenuId menuId) const;
	MenuModelIndex parent(const MenuModelIndex& index) const;

	MenuModelIndex start() const;

	bool hasChildren(const MenuModelIndex& parent = MenuModelIndex()) const;
	int lineCount(const MenuModelIndex& parent = MenuModelIndex()) const;

	Menu::ItemFlags flags(const MenuModelIndex& index) const;
	const char* name(const MenuModelIndex& index) const;
	AbstractMenuValue* value(const MenuModelIndex& index) const;
	AbstractMenuAction* action(const MenuModelIndex& index) const;

	void setValue(const MenuModelIndex& index, AbstractMenuValue* value) const;
	void setValue(MenuId menuId, AbstractMenuValue* value) const;
	void setAction(const MenuModelIndex& index, AbstractMenuAction* action) const;
	void setAction(MenuId menuId, AbstractMenuAction* action) const;

	// EventHandler interface
	virtual void event(Event* event) override;
private:
	MenuNode* node;
	MenuId startId;
};

#endif // MENUMODEL_H
