#ifndef MCUWIDGET_H
#define MCUWIDGET_H

#include <QWidget>
#include "ui_mcuwidget.h"

class MCUWidget : public QWidget
{
	Q_OBJECT

public:
	MCUWidget(QWidget *parent = 0);
	~MCUWidget();

private:
	Ui::MCUWidget ui;

private slots:
	void sure_Slot();
	void cancel_Slot();

signals:
	void selected_Signal();
};

#endif // MCUWIDGET_H
