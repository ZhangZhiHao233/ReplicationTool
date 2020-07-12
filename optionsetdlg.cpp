#include "optionsetdlg.h"
#include "replicationtool.h"
#include <QMenuBar>
#include <QDebug>

OptionSetDlg::OptionSetDlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("Option ����"));
	this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	this->setWindowModality(Qt::WindowModal);//������ʾЧ��
	this->setAttribute(Qt::WA_DeleteOnClose);
	
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(sure_Slot()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel_Slot()));
}

OptionSetDlg::~OptionSetDlg()
{

}

void OptionSetDlg::sure_Slot()
{

	//��ȡ������ָ��
	ReplicationTool *pMainDlg = qobject_cast<ReplicationTool *>(this->parentWidget());
	if (pMainDlg->pActionOption->isChecked())
	{
		pMainDlg->pActionOption->setChecked(false);
	}
	this->close();
}

void OptionSetDlg::cancel_Slot()
{
	ReplicationTool *pMainDlg = qobject_cast<ReplicationTool *>(this->parentWidget());
	if (pMainDlg->pActionOption->isChecked())
	{
		pMainDlg->pActionOption->setChecked(false);
	}
	this->close();
}
