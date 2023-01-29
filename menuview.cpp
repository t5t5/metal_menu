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
	m_currentIndex = m_model ? m_model->index(0, m_parentIndex) : MenuModelIndex();
	m_lineCount = m_model ? m_model->lineCount(m_parentIndex) : 0;
	m_mode = WalkMode;
	m_visibleIndex = 0;
	m_visibleRows = m_menuItemDelegate ? m_menuItemDelegate->rowCount() : 0;
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

	for (int row = 0; row < m_visibleRows; ++row) {
		int rowIndex = m_visibleIndex + row;
		MenuModelIndex menuIndex;
		int flag = AbstractMenuItemDelegate::EmptyFlag;
		if (rowIndex < m_lineCount) {
			if (m_currentIndex.line() == rowIndex) {
				flag = AbstractMenuItemDelegate::SelectedItemFlag;
				if (m_mode == EditMode) {
					flag |= AbstractMenuItemDelegate::ParameterEditFlag;
				}
			}
			menuIndex = m_model->index(rowIndex, m_parentIndex);
		}
		if ((row == 0) && (m_visibleIndex != 0)) {
			flag |= AbstractMenuItemDelegate::ScrollUpFlag;
		}
		if ((row == (m_visibleRows - 1)) && (rowIndex != (m_lineCount - 1))) {
			flag |= AbstractMenuItemDelegate::ScrollDownFlag;
		}
		if (m_model->hasChildren(menuIndex)) {
			flag |= AbstractMenuItemDelegate::HasSubMenuFlag;
		}
		m_menuItemDelegate->paintRow(row, menuIndex, flag);
	}
}

void MenuView::walkMode_down()
{
	if (m_currentIndex.line() == (m_lineCount - 1)) { return; }
	m_currentIndex = m_model->index(m_currentIndex.line() + 1, m_parentIndex);
	if ((m_visibleIndex + m_visibleRows) == m_currentIndex.line()) { ++m_visibleIndex; }
	paint();
}

void MenuView::walkMode_up()
{
	if (m_currentIndex.line() == 0) { return; }
	m_currentIndex = m_model->index(m_currentIndex.line() - 1, m_parentIndex);
	if (m_currentIndex.line() < m_visibleIndex) { --m_visibleIndex; }
	paint();
}

void MenuView::walkMode_forward()
{
	int lineCount = m_model->lineCount(m_currentIndex);
	if (lineCount) {
		// если есть подменю, идем в него
		m_parentIndex = m_currentIndex;
		m_currentIndex = m_model->index(0, m_parentIndex);
		m_lineCount = lineCount;
		m_visibleIndex = 0;
	} else
	if ((m_currentIndex.value() != nullptr) && !m_currentIndex.value()->isReadOnly()) {
		// если редактируемое значение, входим в режим редактирования
		m_mode = EditMode;
	} else
	if (m_currentIndex.action() != nullptr) {
		// если на пункт назначено действие, выполняем
		m_currentIndex.action()->call();
	}
	paint();
}

void MenuView::walkMode_backward()
{
	if (!m_parentIndex.isValid()) { return; } // выше некуда
	m_parentIndex = m_parentIndex.parent();
	m_currentIndex = m_model->index(0, m_parentIndex);
	m_lineCount = m_model->lineCount(m_parentIndex);
	m_visibleIndex = 0;
	paint();
}

void MenuView::editMode_increase()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->next()) { return; }
	paint();
}

void MenuView::editMode_decrease()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->previous()) { return; }
	paint();
}

void MenuView::editMode_apply()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value) { return; }

	value->apply();
	m_mode = WalkMode;
	paint();
}

void MenuView::editMode_cancel()
{
	AbstractMenuValue* value = m_currentIndex.value();
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
	if (!m_model) { return; }

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
