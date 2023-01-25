#include "menuview.h"

#include <algorithm>

#include "abstractmenuitemdelegate.h"
#include "keyevent.h"
#include "menumodel.h"

MenuView::MenuView()
	: m_model(nullptr)
	, m_menuItemDelegate(nullptr)
{
	reset();
}

void MenuView::reset()
{
	if (m_model) {
		m_parentItemId = RootMenuId;
		m_childrenCount = m_model->childrenCount(RootMenuId);
	} else {
		m_parentItemId = NoMenuId;
		m_childrenCount = 0;
	}
	m_mode = WalkMode;
	m_visibleIndex = 0;
	m_currentIndex = 0;
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
		if ((row == (rowCount - 1)) && (index != (m_childrenCount - 1))) { flag |= AbstractMenuItemDelegate::ScrollDownFlag; }
		if (m_model->hasChild(menuItemId)) { flag |= AbstractMenuItemDelegate::HasSubMenuFlag; }
		m_menuItemDelegate->paintRow(row, m_model, menuItemId, flag);
	}
}

void MenuView::walkMode_down()
{
	if (m_menuItemDelegate == nullptr) { return; }
	int rowCount = m_menuItemDelegate->rowCount();

	if (m_currentIndex == (m_childrenCount - 1)) { return; }
	++m_currentIndex;
	if ((m_visibleIndex + rowCount) == m_currentIndex) { ++m_visibleIndex; }

	paint();
}

void MenuView::walkMode_up()
{
	if (m_currentIndex == 0) { return; }
	--m_currentIndex;
	if (m_currentIndex < m_visibleIndex) { --m_visibleIndex; }
	paint();
}

void MenuView::walkMode_forward()
{
	if (!m_model) { return; }

	int currentMenuId = m_model->child(m_parentItemId, m_currentIndex);
	if (currentMenuId == NoMenuId) { return; }

	if (m_model->hasChild(currentMenuId)) {
		// если есть подменю, идем в него
		m_parentItemId = currentMenuId;
		m_childrenCount = m_model->childrenCount(m_parentItemId);
		m_visibleIndex = 0;
		m_currentIndex = 0;
		paint();
	} else
	if (m_model->value(currentMenuId) != nullptr) {
		// если редактируемое значение, входим в режим редактирования
		m_mode = EditMode;
	}
}

void MenuView::walkMode_backward()
{
	if (!m_model) { return; }

	int parentMenuId = m_model->parent(m_parentItemId);
	if (parentMenuId == NoMenuId) { return; }

	m_parentItemId = parentMenuId;
	m_childrenCount = m_model->childrenCount(m_parentItemId);
	m_visibleIndex = 0;
	m_currentIndex = 0;
	paint();
}

void MenuView::editMode_increase()
{
	if (!m_model) { return; }

	int currentMenuId = m_model->child(m_parentItemId, m_currentIndex);
	if (currentMenuId == NoMenuId) { return; }

	AbstractMenuValue* value = m_model->value(currentMenuId);
	if (!value) { return; }

	if (!value->next()) { return; }
	paint();
}

void MenuView::editMode_decrease()
{
	if (!m_model) { return; }

	int currentMenuId = m_model->child(m_parentItemId, m_currentIndex);
	if (currentMenuId == NoMenuId) { return; }

	AbstractMenuValue* value = m_model->value(currentMenuId);
	if (!value) { return; }

	if (!value->previous()) { return; }
	paint();
}

void MenuView::editMode_apply()
{
	if (!m_model) { return; }

	int currentMenuId = m_model->child(m_parentItemId, m_currentIndex);
	if (currentMenuId == NoMenuId) { return; }

	AbstractMenuValue* value = m_model->value(currentMenuId);
	if (!value) { return; }

	value->apply();
	paint();
	m_mode = WalkMode;
}

void MenuView::editMode_cancel()
{
	if (!m_model) { return; }

	int currentMenuId = m_model->child(m_parentItemId, m_currentIndex);
	if (currentMenuId == NoMenuId) { return; }

	AbstractMenuValue* value = m_model->value(currentMenuId);
	if (!value) { return; }

	value->cancel();
	paint();
	m_mode = WalkMode;
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
		(m_mode == WalkMode) ? walkMode_up() : editMode_increase();
		break;
	case Down:
		(m_mode == WalkMode) ? walkMode_down() : editMode_decrease();
		break;
	case Left:
		(m_mode == WalkMode) ? walkMode_up() : editMode_decrease();
		break;
	case Right:
		(m_mode == WalkMode) ? walkMode_down() : editMode_increase();
		break;
	case Forward:
		(m_mode == WalkMode) ? walkMode_forward() : editMode_apply();
		break;
	case Backward:
		(m_mode == WalkMode) ? walkMode_backward() : editMode_cancel();
		break;
	}
}

void MenuView::setMenuItemDelegate(AbstractMenuItemDelegate* delegate)
{
	if (m_menuItemDelegate == delegate) { return; }

	m_menuItemDelegate = delegate;
	reset();
}
