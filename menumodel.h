#ifndef MENUMODEL_H
#define MENUMODEL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

#include "menumodelindex.h"

class MenuModel
{
public:
	MenuModel(const MenuNode* n);

	MenuModelIndex index(int line, const MenuModelIndex& parent = MenuModelIndex()) const;
	MenuModelIndex parent(const MenuModelIndex& index) const;

	bool hasChildren(const MenuModelIndex& parent = MenuModelIndex()) const;
	int lineCount(const MenuModelIndex& parent = MenuModelIndex()) const;

	const char* name(const MenuModelIndex& index) const;
	AbstractMenuValue* value(const MenuModelIndex& index) const;
	AbstractMenuAction* action(const MenuModelIndex& index) const;
private:
	const MenuNode* node;
};

#endif // MENUMODEL_H
