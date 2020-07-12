#include "replicationtool.h"
#include "mcuwidget.h"
#include "optionsetdlg.h"
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QTimer>
#include <QDateTime>
#include <QDockWidget>
#include <QMouseEvent>
#include <QProgressBar>
#include <QDebug>
#include <Windows.h>


ReplicationTool::ReplicationTool(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("烧录软件"));

	createMenu();
	createToolBar();
	createStatusBar();
	createOutputDocWidget();

	//findAllControlsForStatusBar();

	QTimer::singleShot(500, this, SLOT(selectChip_Slot()));
}

ReplicationTool::~ReplicationTool()
{
	
}

void ReplicationTool::createMenu()
{	
	pMenuBar = menuBar();
	
	//菜单-文件
	QMenu *pMenuBarFile= new QMenu(QStringLiteral("文件(&F)"));
	QAction *pActionOpen = new QAction(QStringLiteral("打开"), this);
	pActionOpen->setIcon(QIcon(":/ReplicationTool/png/open.png"));
	pActionOpen->setShortcut(Qt::CTRL | Qt::Key_O);
	pMenuBarFile->addAction(pActionOpen);  

	QAction *pActionSave = new QAction(QStringLiteral("保存"), this);
	pActionSave->setIcon(QIcon(":/ReplicationTool/png/save.png"));
	pActionSave->setShortcut(Qt::CTRL | Qt::Key_S);
	pMenuBarFile->addAction(pActionSave);

	QAction *pActionSaveAs = new QAction(QStringLiteral("另存为"), this);
	pActionSaveAs->setIcon(QIcon(":/ReplicationTool/png/saveAs.png"));
	pActionSaveAs->setShortcut(Qt::CTRL | Qt::Key_A);
	pMenuBarFile->addAction(pActionSaveAs);

	QAction *pActionRecent = new QAction(QStringLiteral("最近打开文件"), this);
	pActionRecent->setIcon(QIcon(":/ReplicationTool/png/recent.png"));
	pMenuBarFile->addAction(pActionRecent);

	QAction *pActionExit = new QAction(QStringLiteral("退出"), this);
	pActionExit->setIcon(QIcon(":/ReplicationTool/png/exit.png"));
	pActionExit->setShortcut(Qt::CTRL | Qt::Key_X);
	pMenuBarFile->addAction(pActionExit);

	//菜单-设置
	QMenu *pMenuBarSetting= new QMenu(QStringLiteral("设置(&S)"));
	QAction *pActionOffSound = new QAction(QStringLiteral("关闭烧写提示音"), this);
	pMenuBarSetting->addAction(pActionOffSound);  

	QAction *pActionForceProgram= new QAction(QStringLiteral("强制烧写"), this);
	pMenuBarSetting->addAction(pActionForceProgram); 

	//菜单-操作
	QMenu *pMenuBarOperate= new QMenu(QStringLiteral("操作(&O)"));

	QAction *pActionConnect = new QAction(QStringLiteral("连接"), this);
	pActionConnect->setIcon(QIcon(":/ReplicationTool/png/connect.ico"));
	pActionConnect->setShortcut(Qt::CTRL | Qt::Key_L);
	pMenuBarOperate->addAction(pActionConnect);

	QAction *pActionDisConnect = new QAction(QStringLiteral("断开连接"), this);
	pActionDisConnect->setIcon(QIcon(":/ReplicationTool/png/disconnect.ico"));
	pActionDisConnect->setShortcut(Qt::CTRL | Qt::Key_U);
	pMenuBarOperate->addAction(pActionDisConnect);

	pMenuBarOperate->addSeparator();

	QAction *pActionDownFlash = new QAction(QStringLiteral("下载FLASH数据"), this);
	pActionDownFlash->setIcon(QIcon(":/ReplicationTool/png/download.ico"));
	pActionDownFlash->setShortcut(Qt::CTRL | Qt::Key_D);
	pMenuBarOperate->addAction(pActionDownFlash);

	QAction *pActionReadFlash = new QAction(QStringLiteral("读取FLASH数据"), this);
	pActionReadFlash->setIcon(QIcon(":/ReplicationTool/png/read.ico"));
	pActionReadFlash->setShortcut(Qt::CTRL | Qt::Key_R);
	pMenuBarOperate->addAction(pActionReadFlash);

	QAction *pActionEraseFlash = new QAction(QStringLiteral("擦除FLASH数据"), this);
	pActionEraseFlash->setIcon(QIcon(":/ReplicationTool/png/erase.ico"));
	pActionEraseFlash->setShortcut(Qt::CTRL | Qt::Key_E);
	pMenuBarOperate->addAction(pActionEraseFlash);

	QAction *pActionCheckFlash = new QAction(QStringLiteral("校验FLASH数据"), this);
	pActionCheckFlash->setIcon(QIcon(":/ReplicationTool/png/check.ico"));
	pActionCheckFlash->setShortcut(Qt::ALT | Qt::Key_C);
	pMenuBarOperate->addAction(pActionCheckFlash);

	pMenuBarOperate->addSeparator();

	QAction *pActionDownOTP = new QAction(QStringLiteral("下载OTP数据"), this);
	pActionDownOTP->setIcon(QIcon(":/ReplicationTool/png/downloadOTP.ico"));
	pActionDownOTP->setShortcut(Qt::CTRL | Qt::Key_P);
	pMenuBarOperate->addAction(pActionDownOTP);

	QAction *pActionReadOTP = new QAction(QStringLiteral("读取OTP数据"), this);
	pActionReadOTP->setIcon(QIcon(":/ReplicationTool/png/readOTP.ico"));
	pActionReadOTP->setShortcut(Qt::ALT | Qt::Key_A);
	pMenuBarOperate->addAction(pActionReadOTP);

	QAction *pActionClearOTP = new QAction(QStringLiteral("OTP查空"), this);
	pActionClearOTP->setIcon(QIcon(":/ReplicationTool/png/cleanOTP.ico"));
	pActionClearOTP->setShortcut(Qt::CTRL | Qt::Key_B);
	pMenuBarOperate->addAction(pActionClearOTP);
			
	QAction *pActionCheckOTP = new QAction(QStringLiteral("校验OTP数据"), this);
	pActionCheckOTP->setIcon(QIcon(":/ReplicationTool/png/checkOTP.ico"));
	pActionCheckOTP->setShortcut(Qt::ALT | Qt::Key_Y);
	pMenuBarOperate->addAction(pActionCheckOTP);

	//菜单-视图
	QMenu *pMenuBarView= new QMenu(QStringLiteral("视图(&V)"));
	QAction *pActionToolBar = new QAction(QStringLiteral("工具栏"), this);
	pActionToolBar->setShortcut(Qt::ALT | Qt::Key_T);
	pActionToolBar->setCheckable(true);
	pActionToolBar->setChecked(true);
	pMenuBarView->addAction(pActionToolBar);

	QAction *pActionState = new QAction(QStringLiteral("状态栏"), this);
	pActionState->setShortcut(Qt::ALT | Qt::Key_S);
	pActionState->setCheckable(true);
	pActionState->setChecked(true);
	pMenuBarView->addAction(pActionState);

	pActionOption = new QAction(QStringLiteral("Option 设置栏"), this);
	pActionOption->setShortcut(Qt::ALT | Qt::Key_B);
	pActionOption->setCheckable(true);
	pMenuBarView->addAction(pActionOption);

	QAction *pActionOutput = new QAction(QStringLiteral("信息输出栏"), this);
	pActionOutput->setShortcut(Qt::ALT | Qt::Key_M);
	connect(pActionOutput, SIGNAL(triggered(bool)), this, SLOT(dataOutputBar_Slot(bool)));
	pActionOutput->setCheckable(true);
	pActionOutput->setChecked(true);
	pMenuBarView->addAction(pActionOutput);

	//菜单-帮助
	QMenu *pMenuBarHelp= new QMenu(QStringLiteral("帮助(&H)"));

	//添加菜单选项
	pMenuBar->addMenu(pMenuBarFile);
	pMenuBar->addMenu(pMenuBarSetting);
	pMenuBar->addMenu(pMenuBarOperate);
	pMenuBar->addMenu(pMenuBarView);
	pMenuBar->addMenu(pMenuBarHelp);

	//槽函数绑定
	connect(pActionOpen, SIGNAL(triggered()), this, SLOT(open_Slot()));
	connect(pActionSave, SIGNAL(triggered()), this, SLOT(save_Slot()));
	connect(pActionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs_Slot()));
	connect(pActionRecent, SIGNAL(triggered()), this, SLOT(recentOpen_Slot()));
	connect(pActionExit, SIGNAL(triggered()), this, SLOT(exit_Slot()));
	connect(pActionOffSound, SIGNAL(triggered()), this, SLOT(offSound_Slot()));
	connect(pActionForceProgram, SIGNAL(triggered()), this, SLOT(forceProgram_Slot()));
	connect(pActionConnect, SIGNAL(triggered()), this, SLOT(connect_Slot()));
	connect(pActionDisConnect, SIGNAL(triggered()), this, SLOT(disConnect_Slot()));
	connect(pActionDownFlash, SIGNAL(triggered()), this, SLOT(downloadFlash_Slot()));
	connect(pActionReadFlash, SIGNAL(triggered()), this, SLOT(readFlash_Slot()));
	connect(pActionEraseFlash, SIGNAL(triggered()), this, SLOT(eraseFlash_Slot()));
	connect(pActionCheckFlash, SIGNAL(triggered()), this, SLOT(checkFlash_Slot()));
	connect(pActionDownOTP, SIGNAL(triggered()), this, SLOT(downLoadOTP_Slot()));
	connect(pActionReadOTP, SIGNAL(triggered()), this, SLOT(readOTP_Slot()));
	connect(pActionClearOTP, SIGNAL(triggered()), this, SLOT(cleanOTP_Slot()));
	connect(pActionCheckOTP, SIGNAL(triggered()), this, SLOT(checkOTP_Slot()));
	connect(pActionToolBar, SIGNAL(triggered(bool)), this, SLOT(toolBar_Slot(bool)));
	connect(pActionState, SIGNAL(triggered(bool)), this, SLOT(stateBar_Slot(bool)));
	connect(pActionOption, SIGNAL(triggered(bool)), this, SLOT(optionBar_Slot(bool)));
}

void ReplicationTool::createToolBar()
{
	pToolBar = addToolBar("toolBar");

	QToolButton *pActionOpenBar = new QToolButton(this);
	pActionOpenBar->setIcon(QIcon(":/ReplicationTool/png/open.png"));
	pActionOpenBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionOpenBar->setText(QStringLiteral("打开"));
	pToolBar->addWidget(pActionOpenBar); 

	QToolButton *pActionSaveBar = new QToolButton(this);
	pActionSaveBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionSaveBar->setIcon(QIcon(":/ReplicationTool/png/save.png"));
	pActionSaveBar->setText(QStringLiteral("保存"));
	pToolBar->addWidget(pActionSaveBar); 

	QToolButton *pActionSaveAsBar = new QToolButton(this);
	pActionSaveAsBar->setIcon(QIcon(":/ReplicationTool/png/saveAs.png"));
	pActionSaveAsBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionSaveAsBar->setText(QStringLiteral("另存为"));
	pToolBar->addWidget(pActionSaveAsBar); 

	pToolBar->addSeparator();

	QToolButton *pActionConnectBar = new QToolButton(this);
	pActionConnectBar->setIcon(QIcon(":/ReplicationTool/png/connect.ico"));
	pActionConnectBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionConnectBar->setText(QStringLiteral("连接"));
	pToolBar->addWidget(pActionConnectBar); 

	QToolButton *pActionDisconnectBar = new QToolButton(this);
	pActionDisconnectBar->setIcon(QIcon(":/ReplicationTool/png/disconnect.ico"));
	pActionDisconnectBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionDisconnectBar->setText(QStringLiteral("断开连接"));
	pToolBar->addWidget(pActionDisconnectBar); 

	pToolBar->addSeparator();

	QToolButton *pActionDownBar = new QToolButton(this);
	pActionDownBar->setIcon(QIcon(":/ReplicationTool/png/download.ico"));
	pActionDownBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionDownBar->setText(QStringLiteral("下载flash"));
	pToolBar->addWidget(pActionDownBar); 

	QToolButton *pActionReadBar = new QToolButton(this);
	pActionReadBar->setIcon(QIcon(":/ReplicationTool/png/read.ico"));
	pActionReadBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionReadBar->setText(QStringLiteral("读取flash"));
	pToolBar->addWidget(pActionReadBar); 

	QToolButton *pActionCheckBar = new QToolButton(this);
	pActionCheckBar->setIcon(QIcon(":/ReplicationTool/png/check.ico"));
	pActionCheckBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionCheckBar->setText(QStringLiteral("校验flash"));
	pToolBar->addWidget(pActionCheckBar); 

	pToolBar->addSeparator();

	QToolButton *pActionCleanOTPBar = new QToolButton(this);
	pActionCleanOTPBar->setIcon(QIcon(":/ReplicationTool/png/cleanOTP.ico"));
	pActionCleanOTPBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionCleanOTPBar->setText(QStringLiteral("下载OTP"));
	pToolBar->addWidget(pActionCleanOTPBar); 

	QToolButton *pActionDownOTPBar = new QToolButton(this);
	pActionDownOTPBar->setIcon(QIcon(":/ReplicationTool/png/downloadOTP.ico"));
	pActionDownOTPBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionDownOTPBar->setText(QStringLiteral("下载OTP"));
	pToolBar->addWidget(pActionDownOTPBar); 

	QToolButton *pActionReadOTPBar = new QToolButton(this);
	pActionReadOTPBar->setIcon(QIcon(":/ReplicationTool/png/readOTP.ico"));
	pActionReadOTPBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pActionReadOTPBar->setText(QStringLiteral("读取OTP"));
	pToolBar->addWidget(pActionReadOTPBar); 

	QToolButton *pActionCheckOTPBar = new QToolButton(this);
	pActionCheckOTPBar->setIcon(QIcon(":/ReplicationTool/png/checkOTP.ico"));
	pActionCheckOTPBar->setText(QStringLiteral("检验OTP"));
	pActionCheckOTPBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pToolBar->addWidget(pActionCheckOTPBar); 
	pToolBar->addSeparator();
	
	QToolButton *pActionEditableBar = new QToolButton(this);
	pActionEditableBar->setIcon(QIcon(":/ReplicationTool/png/editable.ico"));
	pActionEditableBar->setText(QStringLiteral("可编辑"));
	pActionEditableBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	pToolBar->addWidget(pActionEditableBar); 

	//槽函数绑定
	connect(pActionOpenBar, SIGNAL(clicked()), this, SLOT(open_Slot()));
	connect(pActionSaveBar, SIGNAL(clicked()), this, SLOT(save_Slot()));
	connect(pActionSaveAsBar, SIGNAL(clicked()), this, SLOT(saveAs_Slot()));
	connect(pActionConnectBar, SIGNAL(clicked()), this, SLOT(connect_Slot()));
	connect(pActionDisconnectBar, SIGNAL(clicked()), this, SLOT(disConnect_Slot()));
	connect(pActionDownBar, SIGNAL(clicked()), this, SLOT(downloadFlash_Slot()));
	connect(pActionReadBar, SIGNAL(clicked()), this, SLOT(readFlash_Slot()));
	connect(pActionCheckBar, SIGNAL(clicked()), this, SLOT(checkFlash_Slot()));
	connect(pActionDownOTPBar, SIGNAL(clicked()), this, SLOT(downLoadOTP_Slot()));
	connect(pActionReadOTPBar, SIGNAL(clicked()), this, SLOT(readOTP_Slot()));
	connect(pActionCleanOTPBar, SIGNAL(clicked()), this, SLOT(cleanOTP_Slot()));
	connect(pActionCheckOTPBar, SIGNAL(clicked()), this, SLOT(checkOTP_Slot()));
	connect(pActionEditableBar, SIGNAL(clicked()), this, SLOT(editable_Slot()));
}


void ReplicationTool::resizeEvent(QResizeEvent *event)
{
}

void ReplicationTool::open_Slot()
{
	qDebug()<<"open_Slot";
}

void ReplicationTool::save_Slot()
{
	qDebug()<<"save_Slot";
}

void ReplicationTool::saveAs_Slot()
{
	qDebug()<<"saveAs_Slot";
}

void ReplicationTool::recentOpen_Slot()
{
	qDebug()<<"recentOpen_Slot";
}

void ReplicationTool::exit_Slot()
{
	qDebug()<<"exit_Slot";
}

void ReplicationTool::offSound_Slot()
{
	qDebug()<<"offSound_Slot";
}

void ReplicationTool::forceProgram_Slot()
{
	qDebug()<<"forceProgram_Slot";
}

void ReplicationTool::connect_Slot()
{
	qDebug()<<"connect_Slot";
}

void ReplicationTool::disConnect_Slot()
{
	qDebug()<<"disConnect_Slot";
}

void ReplicationTool::downloadFlash_Slot()
{
	qDebug()<<"downloadFlash_Slot";
}

void ReplicationTool::readFlash_Slot()
{
	qDebug()<<"readFlash_Slot";
}

void ReplicationTool::eraseFlash_Slot()
{
	qDebug()<<"eraseFlash_Slot";
}

void ReplicationTool::checkFlash_Slot()
{
	qDebug()<<"checkFlash_Slot";
}

void ReplicationTool::downLoadOTP_Slot()
{
	qDebug()<<"downLoadOTP_Slot";
}

void ReplicationTool::readOTP_Slot()
{
	qDebug()<<"readOTP_Slot";
}

void ReplicationTool::cleanOTP_Slot()
{
	qDebug()<<"cleanOTP_Slot";
}

void ReplicationTool::checkOTP_Slot()
{
	qDebug()<<"checkOTP_Slot";
}

void ReplicationTool::toolBar_Slot(bool bState)
{
	qDebug()<<"toolBar_Slot"<<bState;
	if (bState)
	{
		if (!pToolBar->isVisible())
		{
			pToolBar->show();
		}
	} 
	else
	{
		pToolBar->hide();
	}
}

void ReplicationTool::stateBar_Slot(bool bState)
{
	qDebug()<<"stateBar_Slot"<<bState;
	if (bState)
	{
		if (!pStatusBar->isVisible())
		{
			pStatusBar->show();
		}
	}
	else
	{
		pStatusBar->hide();
	}
}

void ReplicationTool::optionBar_Slot(bool bState)
{
	qDebug()<<"optionBar_Slot"<<bState;
	if (bState)
	{
		OptionSetDlg *pOptionSetDlg = new OptionSetDlg(this);
		pOptionSetDlg->show();
	}
	//else
	//{
	//	QString ClassName("Qt5QWindowIcon");
	//	QString AppName = QStringLiteral("Option 设置");

	//	LPCWSTR app = reinterpret_cast<LPCWSTR>(ClassName.data());
	//	LPCWSTR appCaption = reinterpret_cast<LPCWSTR>(AppName.data());

	//	HWND hWnd = ::FindWindow(app, appCaption);
	//	OptionSetDlg *pOptionSetDlg = (OptionSetDlg*)FromHandle(hWnd);
	//	pOptionSetDlg->close();

	//}
}

void ReplicationTool::dataOutputBar_Slot(bool bState)
{
	qDebug()<<"dataOutputBar_Slot"<<bState;
	if (bState)
	{
		if (!pOutputDoc->isVisible())
		{
			pOutputDoc->show();
		}
	}
	else
	{
		pOutputDoc->hide();
	}
}

void ReplicationTool::editable_Slot()
{
	qDebug()<<"editable_Slot";
}

void ReplicationTool::createStatusBar()
{
	pStatusBar = statusBar();

	QLabel *pWelCome = new QLabel(QStringLiteral("  就绪"));
	pStatusBar->addWidget(pWelCome);

	QProgressBar * pProgressBar = new QProgressBar();
	pProgressBar->setRange(0,100);
	//pProgressBar->setValue(20);
	pProgressBar->setMaximumWidth(200);
	pStatusBar->addPermanentWidget(pProgressBar);
	pTimeLabel = new QLabel();
	pStatusBar->addPermanentWidget(pTimeLabel);

	QTimer *pTimer = new QTimer(this);
	timeUpdate_Slot();
	pTimer->start(1000); 
	connect(pTimer, SIGNAL(timeout()),this,SLOT(timeUpdate_Slot()));
}

void ReplicationTool::timeUpdate_Slot()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timeStr = currentTime.toString(QStringLiteral("yyyy年MM月dd日 hh:mm:ss"));

	pTimeLabel->setText(timeStr); 
}

void ReplicationTool::createOutputDocWidget()
{
	pDataDoc = new QDockWidget(QStringLiteral("数据栏"),this);
	pDataDoc->setFeatures(QDockWidget::AllDockWidgetFeatures);
	pDataDoc->setMinimumHeight(320);

	addDockWidget(Qt::RightDockWidgetArea, pDataDoc);

	pOutputDoc = new QDockWidget(QStringLiteral("输出栏"),this);
	pOutputDoc->setMinimumHeight(80);
	pOutputDoc->setMaximumHeight(220);
	pOutputDoc->setFeatures(QDockWidget::AllDockWidgetFeatures);
	pOutPutText =new QTextEdit();
	pOutPutText->document()->setMaximumBlockCount(50);
	pOutPutText->setReadOnly(true);
	pOutputDoc->setWidget(pOutPutText);

	addDockWidget(Qt::RightDockWidgetArea, pOutputDoc);

	//演示用
	showTextOnOutPutDoc(QStringLiteral("启动软件，初始化中..."));
	showTextOnOutPutDoc(QStringLiteral("初始化成功!"));
}

void ReplicationTool::findAllControlsForStatusBar()
{
	QObjectList list = children();
	QAction *pTB;
	QDockWidget *pDocW;
	QToolButton *pTolB;
	QToolBar *pTolBar;
	foreach (QObject *obj, list) 
	{
		pTB = qobject_cast<QAction*>(obj);
		if(pTB)
		{
			qDebug() << pTB->text();
		}

		pDocW = qobject_cast<QDockWidget*>(obj);
		if(pDocW)
		{
			qDebug() << pDocW->rect();
		}

		pTolBar = qobject_cast<QToolBar*>(obj);
		if(pTolBar)
		{
			QObjectList list = pTolBar->children();
			foreach(QObject *obj, list)
			{
				pTolB = qobject_cast<QToolButton*>(obj);
				if (pTolB)
				{
					qDebug() << pTolB->text();
				}
			}
		}

		/*pTolB = qobject_cast<QToolButton*>(obj);
		if(pTolB)
		{
		qDebug()<<pTolB->rect();
		}*/
	}
}

void ReplicationTool::mouseMoveEvent(QMouseEvent *event)
{
	/*QWidget *action = QApplication::widgetAt(event->x(), event->y());
	QPoint globalPoint = action->mapToGlobal(QPoint(0, 0));
	qDebug()<< globalPoint;*/

}

void ReplicationTool::selectChip_Slot()
{
	MCUWidget *pMCUWidget = new MCUWidget(this);
	connect(pMCUWidget, SIGNAL(selected_Signal()), this, SLOT(optionSetting_Slot()));
	pMCUWidget->show();
}

void ReplicationTool::optionSetting_Slot()
{
	OptionSetDlg *pOptionSetDlg = new OptionSetDlg(this);
	pOptionSetDlg->show();
}

void ReplicationTool::showTextOnOutPutDoc(QString strText)
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString Str = currentTime.toString(QString("[yyyy/MM/dd hh:mm:ss]  %1").arg(strText));
	pOutPutText->append(Str);
}

void ReplicationTool::showTextOnDataDoc()
{

}

