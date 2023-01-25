#include "menuview.h"

#include <algorithm>

#include "abstractmenuitemdelegate.h"
#include "keyevent.h"
#include "menumodel.h"

MenuView::MenuView()
	: m_model(nullptr)
	, m_menuItemDelegate(nullptr)
	, m_parentItemId(NoMenuId)
	, m_childrenCount(0)
{
}

void MenuView::reset()
{
	if (m_model) {
		m_parentItemId = RootMenuId;
		m_childrenCount = m_model->childrenCount(RootMenuId);
		m_visibleIndex = 0;
		m_currentIndex = 0;
	} else {
		m_parentItemId = NoMenuId;
		m_childrenCount = 0;
		m_visibleIndex = 0;
		m_currentIndex = 0;
	}
	paint();
}

void MenuView::paint()
{
	if ((m_menuItemDelegate == nullptr) || (m_model == nullptr)) { return; }

	int flag = m_model->hasParent(m_parentItemId);
	m_menuItemDelegate->paintHead(m_model, m_parentItemId, flag);
	int rowCount = m_menuItemDelegate->rowCount();
	for (int row = 0; row < rowCount; ++row) {
		int index = m_visibleIndex + row;
		int menuItemId;
		int flag = AbstractMenuItemDelegate::EmptyFlag;
		if (index < m_childrenCount) {
			if (m_currentIndex == index) {
				flag = AbstractMenuItemDelegate::SelectedItemFlag;
			}
			menuItemId = m_model->child(m_parentItemId, index);
		} else {
			menuItemId = NoMenuId;
		}
		if ((row == 0) && (m_visibleIndex != 0)) { flag |= AbstractMenuItemDelegate::ScrollUpFlag; }
		if ((row == (rowCount - 1)) && (index != row)) { flag |= AbstractMenuItemDelegate::ScrollDownFlag; }
		if (m_model->hasChild(menuItemId)) { flag |= AbstractMenuItemDelegate::HasSubMenuFlag; }
		m_menuItemDelegate->paintRow(row, m_model, menuItemId, flag);
	}
}

void MenuView::setModel(MenuModel* model)
{
	if (m_model == model) { return; }

	if (m_model) {
		// TODO: отвязка от менюшных event'ов (если есть)
	}
	m_model = model;
	if (m_model) {
		// TODO: привязка к менюшным event'ам (если есть)
	}
	reset();
}

MenuModel* MenuView::model() const
{
	return m_model;
}

void MenuView::keyEvent(KeyEvent* event)
{
	switch (event->key()) {
	case Up:
		break;
	case Down:
		break;
	case Left:
		break;
	case Right:
		break;
	case Forward:
		break;
	case Backward:
		break;
	}
}

void MenuView::setMenuItemDelegate(AbstractMenuItemDelegate* delegate)
{
	if (m_menuItemDelegate == delegate) { return; }

	m_menuItemDelegate = delegate;
	reset();
}
