#ifndef MENUVIEW_H
#define MENUVIEW_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

class AbstractMenuItemDelegate;
class KeyEvent;
class MenuModel;

class MenuView
{
public:
	MenuView();
	~MenuView() = default;

	void setModel(MenuModel* model);
	MenuModel* model() const;

	void keyEvent(KeyEvent* event);

	void setMenuItemDelegate(AbstractMenuItemDelegate* delegate);
private:
	enum Mode { WalkMode, EditMode, };

	void reset();
	void paint();

	void walkMode_down();
	void walkMode_up();
	void walkMode_forward();
	void walkMode_backward();

	void editMode_increase();
	void editMode_decrease();
	void editMode_apply();
	void editMode_cancel();

	MenuModel* m_model;
	AbstractMenuItemDelegate* m_menuItemDelegate;

	Mode m_mode;
	int m_parentItemId;
	int m_childrenCount;
	int m_visibleIndex;

	int m_currentIndex;

};

#endif // MENUVIEW_H
