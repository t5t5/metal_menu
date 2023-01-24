#include <iostream>

#include "menu_main.h"
#include "menumodel.h"
#include "menuview.h"
#include "abstractmenuitemdelegate.h"

class MenuItemDelegate : public AbstractMenuItemDelegate
{
private:
	static const int RowCount = 2;
	static const int CharCount = 30;
public:
	MenuItemDelegate();
	virtual ~MenuItemDelegate() override;

	virtual int rowCount() const override;
	virtual int charCount() const override;
	virtual void paintHead(MenuModel* model, int itemId) override;
	virtual void paintRow(int index, MenuModel* model, int itemId, int flag) override;
private:
	std::string header;
	std::vector<std::string> rows;

	std::string formatItem(const char* name, const char* value, int size);

	void show();
};

MenuItemDelegate::MenuItemDelegate()
{
	rows.resize(RowCount);
}

MenuItemDelegate::~MenuItemDelegate()
{
}

int MenuItemDelegate::rowCount() const
{
	return RowCount;
}

int MenuItemDelegate::charCount() const
{
	return CharCount;
}

void MenuItemDelegate::paintHead(MenuModel* model, int itemId)
{
	header = (itemId == RootMenuId)
			? "application"
			: model->name(itemId);
	show();
}

void MenuItemDelegate::paintRow(int index, MenuModel* model, int itemId, int flag)
{
	if (itemId == NoMenuId) {
		rows[index].clear();
	} else {
		auto text = model->name(itemId);
		auto value = model->valueToString(itemId);
		auto item = formatItem(text, value, CharCount - 3);
		if ((flag & SelectedItemFlag) != 0) {
			item = '>' + item;
		} else {
			item = ' ' + item;
		}
		if ((flag & IsMenuFlag) != 0) {
			item = item + '>';;
		} else {
			item = item + ' ';
		}
		if ((flag & ScrollUpFlag) != 0) {
			item = item + '^';
		} else
		if ((flag & ScrollDownFlag) != 0) {
			item = item + 'v';
		} else {
			item = item + ' ';
		}
		rows[index] = item;
	}
	show();
}

std::string MenuItemDelegate::formatItem(const char* name, const char* value, int size)
{
	int nameSize = (name != nullptr) ? strlen(name) : 0;
	int valueSize = (value != nullptr) ? strlen(value) : 0;
	int spaceSize = (size - nameSize - valueSize);
	if (spaceSize < 0) { spaceSize = 0; }
//	strncpy_s(buffer, size, name, nameSize);
//	memset(buffer + nameSize, ' ', spaceSize);
//	strncpy_s(buffer + nameSize + spaceSize, size - nameSize - spaceSize, value, valueSize);

	std::string result = name;
	result.append(spaceSize, ' ');
	result.append(value == nullptr ? "" : value);
	return result;
}

void MenuItemDelegate::show()
{
	std::cout << header << std::endl;
	std::cout << std::string(CharCount, '-') << std::endl;
	for (const auto& row : rows) {
		std::cout << row << std::endl;
	}
	std::cout << std::endl;
}

// ------------------------------------------------------------------------

int main() {
	MenuModel m(mainMenu);
	auto c = m.childrenCount(RootMenuId);
	std::cout << c << std::endl;

	MenuItemDelegate d;

	MenuView v;
	v.setMenuItemDelegate(&d);
	v.setModel(&m);

	return 0;
}
