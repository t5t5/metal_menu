#ifndef MENUMODELINDEX_H
#define MENUMODELINDEX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

class MenuModel;
struct MenuNode;

class AbstractMenuAction;
class AbstractMenuValue;

class MenuModelIndex
{
protected:
	friend class MenuModel;
	MenuModelIndex(const MenuModel* model, MenuNode* node, int line);
public:
	MenuModelIndex();
	~MenuModelIndex() = default;

	bool isValid() const;
	const MenuModel* model() const;

	MenuModelIndex parent() const;
	int line() const;

	Menu::ItemFlags flags() const;

	const char* name() const;
	AbstractMenuValue* value() const;
	AbstractMenuAction* action() const;

	void setValue(AbstractMenuValue* value) const;
	void setAction(AbstractMenuAction* action) const;
private:
	const MenuModel* m_model;
	MenuNode* m_node;
	int m_line;
};

#endif // MENUMODELINDEX_H
