#include "mcuwidget.h"

MCUWidget::MCUWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("MCU"));
	this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	this->setWindowModality(Qt::WindowModal);//发出提示效果
	this->setAttribute(Qt::WA_DeleteOnClose);


	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(sure_Slot()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel_Slot()));

}

MCUWidget::~MCUWidget()
{

}

void MCUWidget::sure_Slot()
{
	emit selected_Signal();
	this->close();
}

void MCUWidget::cancel_Slot()
{
	this->close();
}
