#ifndef MENUDEFINES_H
#define MENUDEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>
#include <string.h>

#include "flag.h"

class Parameter;

using MenuId = char;
const MenuId NoMenuId = -1;
const MenuId RootMenuId = 0;

namespace Menu
{

enum ItemFlag
{
	NoItemFlag         = 0x00,
	ItemValueReadOnly  = 0x01,
	ItemValueComplex   = 0x02,
};
using ItemFlags = Flag<ItemFlag>;

enum PaintFlag
{
	NoPaintFlag        = 0x00,
	PaintSelectedItem  = 0x01,
	PaintScrollUp      = 0x02,
	PaintScrollDown    = 0x04,
	PaintHasSubMenu    = 0x08,
	PaintHasParentMenu = 0x10,
	PaintParameterEdit = 0x20,
	PaintValueOnly     = 0x40,
	PaintValueComplex  = 0x80,
};
using PaintFlags = Flag<PaintFlag>;

} // namespace Menu

class AbstractMenuValue
{
public:
	virtual ~AbstractMenuValue() { }

	virtual bool isReadOnly() const { return false; }

	virtual bool up() = 0;
	virtual bool down() = 0;
	virtual bool left() = 0;
	virtual bool right() = 0;

	virtual bool apply() = 0;
	virtual void cancel() = 0;

	virtual void toChar(char* out, int size) const = 0;

	virtual Parameter* parameter() const = 0;
};

class AbstractMenuAction
{
public:
	virtual ~AbstractMenuAction() { }

	virtual void call() = 0;
};

struct MenuNode
{
	MenuId id;
	MenuId parentId;
	Menu::ItemFlags flags;
	const char* name;
	const char* translate;
	AbstractMenuValue* value;
	AbstractMenuAction* action;
};

#endif // MENUNODE_H
