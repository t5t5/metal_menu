#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class MenuDialog;
}

class AbstractMenuAction;
class MenuItemDelegate;
class MenuModel;
class MenuView;

class MenuDialog : public QDialog
{
	Q_OBJECT

public:
	MenuDialog(QWidget* parent = nullptr);
	~MenuDialog();

public slots:
	void start();

private slots:
	void processUp();
	void processDown();
	void processLeft();
	void processRight();
	void processForward();
	void processBackward();

	void randomParameter();
private:
	QTimer randomUpdateTimer;

	Ui::MenuDialog *ui;

	MenuModel* menuModel;
	MenuView* menuView;
	MenuItemDelegate* menuDelegate;

	AbstractMenuAction* messageAction;
	AbstractMenuAction* versionAction;
	AbstractMenuAction* exitAction;
};

#endif // MENUDIALOG_H
