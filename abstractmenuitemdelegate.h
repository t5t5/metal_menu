#ifndef ABSTRACTMENUITEMDELEGATE_H
#define ABSTRACTMENUITEMDELEGATE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menumodelindex.h"

class AbstractMenuItemDelegate
{
public:
	virtual ~AbstractMenuItemDelegate() = default;

	virtual int rowCount() const = 0;
	virtual int charCount() const = 0;

	virtual void paintHead(
		const MenuModelIndex& index, Menu::PaintFlags flag = Menu::NoPaintFlag) = 0;
	virtual void paintRow(
		int row, const MenuModelIndex& index, Menu::PaintFlags flag = Menu::NoPaintFlag) = 0;
};

#endif // ABSTRACTMENUITEMDELEGATE_H
