#ifndef ABSTRACTMENUITEMDELEGATE_H
#define ABSTRACTMENUITEMDELEGATE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menumodelindex.h"

class AbstractMenuItemDelegate
{
public:
	enum PaintFlag
	{
		EmptyFlag         = 0x00,
		SelectedItemFlag  = 0x01,
		ScrollUpFlag      = 0x02,
		ScrollDownFlag    = 0x04,
		HasSubMenuFlag    = 0x08,
		HasParentMenuFlag = 0x10,
		ParameterEditFlag = 0x20,
	};

	virtual ~AbstractMenuItemDelegate() = default;

	virtual int rowCount() const = 0;
	virtual int charCount() const = 0;

	virtual void paintHead(const MenuModelIndex& index, int flag = EmptyFlag) = 0;
	virtual void paintRow(int row, const MenuModelIndex& index, int flag = EmptyFlag) = 0;
};

#endif // ABSTRACTMENUITEMDELEGATE_H
