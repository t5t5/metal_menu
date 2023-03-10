#ifndef MENUVIEW_H
#define MENUVIEW_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

class AbstractMenuItemDelegate;
class KeyEvent;
class MenuModel;

#include "eventhandler.h"
#include "menumodelindex.h"

class MenuView : public EventHandler
{
public:
	MenuView();
	~MenuView();

	void setModel(MenuModel* model);
	MenuModel* model() const;

	void setMenuItemDelegate(AbstractMenuItemDelegate* delegate);

	// EventHandler interface
	virtual void event(Event* event) override;
private:
	void keyEvent(KeyEvent* event);
	void menuItemChangedEvent(MenuItemChangedEvent* event);

	enum Mode { WalkMode, EditMode, ComplexEditMode };

	void reset();
	void paint();
	void walkMode_paint();
	void editMode_paint();

	void walkMode_down();
	void walkMode_up();
	void walkMode_forward();
	void walkMode_backward();

	void editMode_up();
	void editMode_down();
	void editMode_left();
	void editMode_right();
	void editMode_apply();
	void editMode_cancel();

	MenuModel* m_model;
	AbstractMenuItemDelegate* m_menuItemDelegate;

	Mode m_mode;
	MenuModelIndex m_parentIndex;
	MenuModelIndex m_currentIndex;
	int m_lineCount;
	int m_visibleIndex;
	int m_visibleRows;

//	int m_currentIndex;
};

#endif // MENUVIEW_H
