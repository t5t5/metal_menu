#ifndef MENUMODEL_H
#define MENUMODEL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

class MenuModel
{
public:
	MenuModel(const MenuNode* n);

	bool hasNext(int itemId) const;
	bool hasPrevious(int itemId) const;
	bool hasParent(int itemId) const;
	bool hasChild(int itemId) const;

	int childrenCount(int itemId) const;

	int id(int itemId) const;
	int next(int itemId) const;
	int previous(int itemId) const;
	int parent(int itemId) const;
	int child(int itemId) const;
	const char* name(int itemId) const;
private:
	const MenuNode* node;
};

#endif // MENUMODEL_H
