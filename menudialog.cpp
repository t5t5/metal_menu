#include "menudialog.h"
#include "ui_menudialog.h"

#include "abstractmenuitemdelegate.h"
#include "keyevent.h"
#include "menumodel.h"
#include "menuview.h"

#include "menu_main.h"

class MenuItemDelegate : public AbstractMenuItemDelegate
{
private:
	static const int RowCount = 2;
	static const int CharCount = 30;
	static const int ValueCount = 10;
public:
	MenuItemDelegate();
	virtual ~MenuItemDelegate() override;

	virtual int rowCount() const override;
	virtual int charCount() const override;
	virtual void paintHead(MenuModel* model, int itemId, int flag = EmptyFlag) override;
	virtual void paintRow(int index, MenuModel* model, int itemId, int flag = EmptyFlag) override;
public:
	void setOutWidget(QTextEdit* widget);
private:
	std::string header;
	std::vector<std::string> rows;

	std::string formatItem(const char* name, const char* value, int size);

	void show();

	QTextEdit* widget;
};

MenuItemDelegate::MenuItemDelegate()
	: widget(nullptr)
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

void MenuItemDelegate::paintHead(MenuModel* model, int itemId, int flag /* = EmptyFlag */)
{
	header = (itemId == RootMenuId)
			? "application"
			: model->name(itemId);
	show();
}

void MenuItemDelegate::paintRow(int index, MenuModel* model, int itemId, int flag /* = EmptyFlag */)
{
	if (itemId == NoMenuId) {
		rows[index].clear();
	} else {
		char value[ValueCount];
		value[0] = 0;
		auto text = model->name(itemId);
		auto v = model->value(itemId);
		if (v) { v->toChar(value, ValueCount); }
		auto item = formatItem(text, &value[0], CharCount - 3);
		if ((flag & SelectedItemFlag) != 0) {
			item = '>' + item;
		} else {
			item = ' ' + item;
		}
		if ((flag & HasSubMenuFlag) != 0) {
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

void MenuItemDelegate::setOutWidget(QTextEdit* w)
{
	widget = w;
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
	if (!widget) { return; }
	widget->clear();

	QString text = QString("%1\n%2\n").arg(
			QString::fromStdString(header),
			QString(CharCount, '-'));
	for (const auto& row : rows) {
		text.append(QString("%1\n").arg(QString::fromStdString(row)));
	}
	widget->setPlainText(text);
}

// ------------------------------------------------------------------------

MenuDialog::MenuDialog(QWidget* parent /* = nullptr */)
	: QDialog(parent)
	, ui(new Ui::MenuDialog)
	, menuModel(nullptr)
	, menuView(nullptr)
	, menuDelegate(nullptr)
{
	ui->setupUi(this);

	ui->menuText->setFontFamily("Source Code Pro");

	connect(
		ui->upButton, &QAbstractButton::clicked,
		this, &MenuDialog::processUp);

	connect(
		ui->downButton, &QAbstractButton::clicked,
		this, &MenuDialog::processDown);

	connect(
		ui->leftButton, &QAbstractButton::clicked,
		this, &MenuDialog::processLeft);

	connect(
		ui->rightButton, &QAbstractButton::clicked,
		this, &MenuDialog::processRight);

	connect(
		ui->forwardButton, &QAbstractButton::clicked,
		this, &MenuDialog::processForward);

	connect(
		ui->backwardButton, &QAbstractButton::clicked,
		this, &MenuDialog::processBackward);

}

MenuDialog::~MenuDialog()
{
	delete ui;
	if (menuModel) { delete menuModel; }
}

void MenuDialog::start()
{
	menuDelegate = new MenuItemDelegate();
	menuDelegate->setOutWidget(ui->menuText);

	menuModel = new MenuModel(mainMenu);
	menuView = new MenuView();
	menuView->setModel(menuModel);
	menuView->setMenuItemDelegate(menuDelegate);
}

void MenuDialog::processUp()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Up);
	menuView->keyEvent(&e);
}

void MenuDialog::processDown()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Down);
	menuView->keyEvent(&e);
}

void MenuDialog::processLeft()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Left);
	menuView->keyEvent(&e);
}

void MenuDialog::processRight()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Right);
	menuView->keyEvent(&e);
}

void MenuDialog::processForward()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Forward);
	menuView->keyEvent(&e);
}

void MenuDialog::processBackward()
{
	if (!menuView) { return; }
	KeyEvent e(Key::Backward);
	menuView->keyEvent(&e);
}
