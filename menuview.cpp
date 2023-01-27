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
	m_parentIndex = MenuModelIndex();
	m_childrenCount = m_model ? m_model->lineCount(m_parentIndex) : 0;
	m_mode = WalkMode;
	m_visibleIndex = 0;
	m_currentIndex = 0;
	paint();
}

void MenuView::paint()
{
	if (!m_menuItemDelegate || !m_model) { return; }

	int flag = m_parentIndex.parent().isValid()
		? AbstractMenuItemDelegate::HasParentMenuFlag
		: AbstractMenuItemDelegate::EmptyFlag;
	if (m_mode == EditMode) {
		flag |= AbstractMenuItemDelegate::ParameterEditFlag;
	}
	m_menuItemDelegate->paintHead(m_parentIndex, flag);
	int rowCount = m_menuItemDelegate->rowCount();

	for (int row = 0; row < rowCount; ++row) {
		int rowIndex = m_visibleIndex + row;
		MenuModelIndex menuIndex;
		int flag = AbstractMenuItemDelegate::EmptyFlag;
		if (rowIndex < m_childrenCount) {
			if (m_currentIndex == rowIndex) {
				flag = AbstractMenuItemDelegate::SelectedItemFlag;
				if (m_mode == EditMode) {
					flag |= AbstractMenuItemDelegate::ParameterEditFlag;
				}
			}
			menuIndex = m_model->index(rowIndex, m_parentIndex);
		}
		if ((row == 0) && (m_visibleIndex != 0)) { flag |= AbstractMenuItemDelegate::ScrollUpFlag; }
		if ((row == (rowCount - 1)) && (rowIndex != (m_childrenCount - 1))) { flag |= AbstractMenuItemDelegate::ScrollDownFlag; }
		if (m_model->hasChildren(menuIndex)) {
			flag |= AbstractMenuItemDelegate::HasSubMenuFlag;
		}
		m_menuItemDelegate->paintRow(row, menuIndex, flag);
	}
}

void MenuView::walkMode_down()
{
	if (m_menuItemDelegate == nullptr) { return; }

	if (m_currentIndex == (m_childrenCount - 1)) { return; }
	++m_currentIndex;
	int rowCount = m_menuItemDelegate->rowCount();
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
	MenuModelIndex currentMenuIndex = m_model->index(m_currentIndex, m_parentIndex);
	if (!currentMenuIndex.isValid()) { return; }

	int childrenCount = m_model->lineCount(currentMenuIndex);
	if (childrenCount) {
		// если есть подменю, идем в него
		m_parentIndex = currentMenuIndex;
		m_childrenCount = childrenCount;
		m_visibleIndex = 0;
		m_currentIndex = 0;
	} else
	if (currentMenuIndex.value() != nullptr) {
		// если редактируемое значение, входим в режим редактирования
		m_mode = EditMode;
	} else
	if (currentMenuIndex.action() != nullptr) {
		// если на пункт назначено действие, выполняем
		currentMenuIndex.action()->call();
	}
	paint();
}

void MenuView::walkMode_backward()
{
	if (!m_model) { return; }

	if (!m_parentIndex.isValid()) { return; } // выше некуда
	m_parentIndex = m_parentIndex.parent();
	m_childrenCount = m_model->lineCount(m_parentIndex);
	m_visibleIndex = 0;
	m_currentIndex = 0;
	paint();
}

void MenuView::editMode_increase()
{
	if (!m_model) { return; }

	MenuModelIndex currentIndex = m_model->index(m_currentIndex, m_parentIndex);
	if (!currentIndex.isValid()) { return; }

	AbstractMenuValue* value = currentIndex.value();
	if (!value) { return; }

	if (!value->next()) { return; }
	paint();
}

void MenuView::editMode_decrease()
{
	if (!m_model) { return; }

	MenuModelIndex currentIndex = m_model->index(m_currentIndex, m_parentIndex);
	if (!currentIndex.isValid()) { return; }

	AbstractMenuValue* value = currentIndex.value();
	if (!value) { return; }

	if (!value->previous()) { return; }
	paint();
}

void MenuView::editMode_apply()
{
	if (!m_model) { return; }

	MenuModelIndex currentIndex = m_model->index(m_currentIndex, m_parentIndex);
	if (!currentIndex.isValid()) { return; }

	AbstractMenuValue* value = currentIndex.value();
	if (!value) { return; }

	value->apply();
	m_mode = WalkMode;
	paint();
}

void MenuView::editMode_cancel()
{
	if (!m_model) { return; }

	MenuModelIndex currentIndex = m_model->index(m_currentIndex, m_parentIndex);
	if (!currentIndex.isValid()) { return; }

	AbstractMenuValue* value = currentIndex.value();
	if (!value) { return; }

	value->cancel();
	m_mode = WalkMode;
	paint();
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
