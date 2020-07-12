#ifndef OPTIONSETDLG_H
#define OPTIONSETDLG_H

#include <QWidget>
#include "ui_optionsetdlg.h"

class OptionSetDlg : public QWidget
{
	Q_OBJECT

public:
	OptionSetDlg(QWidget *parent = 0);
	~OptionSetDlg();

private:
	Ui::OptionSetDlg ui;

private slots:
	void sure_Slot();
	void cancel_Slot();
};

#endif // OPTIONSETDLG_H
