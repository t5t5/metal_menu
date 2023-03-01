#include "menuview.h"

#include <algorithm>

#include "abstractmenuitemdelegate.h"
#include "event.h"
#include "menumodel.h"

MenuView::MenuView()
	: m_model(nullptr)
	, m_menuItemDelegate(nullptr)
{
	reset();
	subscribe(Event::EventModelItemChanged);
	subscribe(Event::EventKey);
}

MenuView::~MenuView()
{
	unsubscribe();
}

void MenuView::reset()
{
	m_parentIndex = m_model ? m_model->start() : MenuModelIndex();
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

	if ((m_mode == WalkMode) || (m_mode == EditMode)) {
		walkMode_paint();
	} else {
		editMode_paint();
	}

}

void MenuView::walkMode_paint()
{
	int flag = m_parentIndex.parent().isValid()
		? Menu::PaintHasParentMenu
		: Menu::NoPaintFlag;
	if (m_mode == EditMode) {
		flag |= Menu::PaintParameterEdit;
	}
	m_menuItemDelegate->paintHead(m_parentIndex, flag);

	for (int row = 0; row < m_visibleRows; ++row) {
		int rowIndex = m_visibleIndex + row;
		MenuModelIndex menuIndex;
		int flag = Menu::NoPaintFlag;
		if (rowIndex < m_lineCount) {
			if (m_currentIndex.line() == rowIndex) {
				flag = Menu::PaintSelectedItem;
				if (m_mode == EditMode) {
					flag |= Menu::PaintParameterEdit;
				}
			}
			menuIndex = m_model->index(rowIndex, m_parentIndex);
		}
		if ((row == 0) && (m_visibleIndex != 0)) {
			flag |= Menu::PaintScrollUp;
		}
		if ((row == (m_visibleRows - 1)) && (rowIndex != (m_lineCount - 1))) {
			flag |= Menu::PaintScrollDown;
		}
		if (m_model->hasChildren(menuIndex)) {
			flag |= Menu::PaintHasSubMenu;
		}
		if (menuIndex.flags().test(Menu::ItemValueComplex)) {
			flag |= Menu::PaintValueComplex;
		}
		m_menuItemDelegate->paintRow(row, menuIndex, flag);
	}
}

void MenuView::editMode_paint()
{
	m_menuItemDelegate->paintHead(m_currentIndex);

	int skipLines = (m_visibleRows) / 2;
	int row = 0;
	for (; row < skipLines; ++row) {
		m_menuItemDelegate->paintRow(row, MenuModelIndex());
	}
	m_menuItemDelegate->paintRow(row++, m_currentIndex, Menu::PaintValueOnly);
	for (; row < m_visibleRows; ++row) {
		m_menuItemDelegate->paintRow(row, MenuModelIndex());
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
	Menu::ItemFlags flags = m_currentIndex.flags();
	if (lineCount) {
		// если есть подменю, идем в него
		m_parentIndex = m_currentIndex;
		m_currentIndex = m_model->index(0, m_parentIndex);
		m_lineCount = lineCount;
		m_visibleIndex = 0;
	} else
	if (!flags.test(Menu::ItemValueReadOnly)) {
		// если редактируемое значение, входим в режим редактирования
		m_mode = flags.test(Menu::ItemValueComplex)
			? ComplexEditMode
			: EditMode;
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

void MenuView::editMode_up()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->up()) { return; }
	paint();
}

void MenuView::editMode_down()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->down()) { return; }
	paint();
}

void MenuView::editMode_left()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->left()) { return; }
	paint();
}

void MenuView::editMode_right()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value || !value->right()) { return; }
	paint();
}

void MenuView::editMode_apply()
{
	AbstractMenuValue* value = m_currentIndex.value();
	if (!value) { return; }

	m_mode = WalkMode;
	bool valueChanged = value->apply();
	if (valueChanged) {
		ParameterChangedEvent e(value->parameter());
		sendEvent(&e);
	} else {
		paint();
	}
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
	m_model = model;
	reset();
}

MenuModel* MenuView::model() const
{
	return m_model;
}

void MenuView::setMenuItemDelegate(AbstractMenuItemDelegate* delegate)
{
	if (m_menuItemDelegate == delegate) { return; }

	m_menuItemDelegate = delegate;
	reset();
}

void MenuView::event(Event* event)
{
	switch (event->eventType()) {
	case Event::EventKey: {
		KeyEvent* ke = static_cast<KeyEvent*>(event);
		keyEvent(ke);
		break;
	}
	case Event::EventModelItemChanged: {
		MenuItemChangedEvent* ic = static_cast<MenuItemChangedEvent*>(event);
		menuItemChangedEvent(ic);
		break;
	}
	default:
		break;
	}
}

void MenuView::keyEvent(KeyEvent* event)
{
	if (!m_model) { return; }

	switch (event->key()) {
	case Up:
		(m_mode == WalkMode) ? walkMode_up() : editMode_up();
		break;
	case Down:
		(m_mode == WalkMode) ? walkMode_down() : editMode_down();
		break;
	case Left:
		(m_mode == WalkMode) ? walkMode_up() : editMode_left();
		break;
	case Right:
		(m_mode == WalkMode) ? walkMode_down() : editMode_right();
		break;
	case Forward:
		(m_mode == WalkMode) ? walkMode_forward() : editMode_apply();
		break;
	case Backward:
		(m_mode == WalkMode) ? walkMode_backward() : editMode_cancel();
		break;
	}
}

void MenuView::menuItemChangedEvent(MenuItemChangedEvent* e)
{
	if (e->index().model() != m_model) { return; }
	if (e->index().parent() != m_parentIndex) { return; }
	int line = e->index().line();
	if ((m_visibleIndex <= line) &&
		(line < (m_visibleIndex + m_visibleRows)))
	{
		paint();
	}
}
