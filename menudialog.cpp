#include "menudialog.h"
#include "ui_menudialog.h"

#include <QTimer>

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
	virtual void paintHead(const MenuModelIndex& index, int flag) override;
	virtual void paintRow(int row, const MenuModelIndex& index, int flag) override;
public:
	void setOutWidget(QTextEdit* widget);
private:
	QString header;
	QVector<QString> rows;

	QString formatItem(const char* name, const char* value, int size);

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

void MenuItemDelegate::paintHead(const MenuModelIndex& index, int flag)
{
	header = (index.isValid())
			? QString::fromUtf8(index.name())
			: QString::fromUtf8("application");
	if (flag == ParameterEditFlag) {
		int spaceSize = (CharCount - header.size() - 1);
		header.append(QString(spaceSize, ' '));
		header.append("*");
	}
	show();
}

void MenuItemDelegate::paintRow(int row, const MenuModelIndex& index, int flag)
{
	if (!index.isValid()) {
		rows[row].clear();
	} else {
		char value[ValueCount];
		value[0] = 0;
		auto text = index.name();
		auto v = index.value();
		if (v) { v->toChar(value, ValueCount); }
		auto item = formatItem(text, &value[0], CharCount - 3);
		if ((flag & SelectedItemFlag) != 0) {
			item = (((flag & ParameterEditFlag) == 0) ? '>' : '*') + item;
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
		rows[row] = item;
	}
	show();
}

void MenuItemDelegate::setOutWidget(QTextEdit* w)
{
	widget = w;
}

QString MenuItemDelegate::formatItem(const char* name, const char* value, int size)
{
	QString n = QString::fromUtf8(name);
	QString v = QString::fromUtf8(value);
	int nameSize = (name != nullptr) ? n.size() : 0;
	int valueSize = (value != nullptr) ? v.size() : 0;
	int spaceSize = (size - nameSize - valueSize);
	if (spaceSize < 0) { spaceSize = 0; }
//	strncpy_s(buffer, size, name, nameSize);
//	memset(buffer + nameSize, ' ', spaceSize);
//	strncpy_s(buffer + nameSize + spaceSize, size - nameSize - spaceSize, value, valueSize);

	QString result = name;
	result.append(QString(spaceSize, ' '));
	result.append(value == nullptr ? "" : value);
	return result;
}

void MenuItemDelegate::show()
{
	if (!widget) { return; }
	widget->clear();

	QString text = QString("%1\n%2\n").arg(
			header,
			QString(CharCount, '-'));
	for (const auto& row : rows) {
		text.append(QString("%1\n").arg(row));
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

	messageAction = new FunctionMenuAction(
		[this] () {
			ui->actionEdit->setText("Message!");
			QTimer::singleShot(2000, this, [this] () { ui->actionEdit->clear(); });
		}
	);
	versionAction = new FunctionMenuAction(
		[this] () {
			ui->actionEdit->setText("About author!");
			QTimer::singleShot(2000, this, [this] () { ui->actionEdit->clear(); });
		}
	);
	exitAction = new FunctionMenuAction([this] () { close(); });
}

MenuDialog::~MenuDialog()
{
	delete ui;
	if (menuModel) { delete menuModel; }

	if (exitAction) { delete exitAction; }
	if (versionAction) { delete versionAction; }
	if (messageAction) { delete messageAction; }
}

void MenuDialog::start()
{
	menuDelegate = new MenuItemDelegate();
	menuDelegate->setOutWidget(ui->menuText);

	menuModel = new MenuModel(mainMenu);
	menuView = new MenuView();
	menuView->setModel(menuModel);
	menuView->setMenuItemDelegate(menuDelegate);

	menuModel->setAction(Message, messageAction);
	menuModel->setAction(Version, versionAction);
	menuModel->setAction(Exit, exitAction);
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
