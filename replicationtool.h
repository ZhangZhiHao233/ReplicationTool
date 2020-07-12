#ifndef REPLICATIONTOOL_H
#define REPLICATIONTOOL_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include "ui_replicationtool.h"

class ReplicationTool : public QMainWindow
{
	Q_OBJECT

public:
	ReplicationTool(QMainWindow *parent = 0);
	~ReplicationTool();

private:
	Ui::ReplicationToolClass ui;

protected:
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	void createMenu();
	void createToolBar();
	void createStatusBar();
	void createOutputDocWidget();

	void findAllControlsForStatusBar();
	void showTextOnOutPutDoc(QString strText);
	void showTextOnDataDoc();

private slots:
	//菜单栏-文件
	void open_Slot();
	void save_Slot();
	void saveAs_Slot();
	void recentOpen_Slot();
	void exit_Slot();
	//菜单栏-设置
	void offSound_Slot();
	void forceProgram_Slot();
	//菜单栏-操作
	void connect_Slot();
	void disConnect_Slot();
	void downloadFlash_Slot();
	void readFlash_Slot();
	void eraseFlash_Slot();
	void checkFlash_Slot();
	void downLoadOTP_Slot();
	void readOTP_Slot();
	void cleanOTP_Slot();
	void checkOTP_Slot();	
	//菜单栏-帮助
	void toolBar_Slot(bool);
	void stateBar_Slot(bool);
	void optionBar_Slot(bool);
	void dataOutputBar_Slot(bool);

	//工具栏-可编辑
	void editable_Slot();	

	//状态栏-时间
	void timeUpdate_Slot();

	//芯片选项
	void selectChip_Slot();

	//弹出option设置
	void optionSetting_Slot();

private:
	QLabel* pTimeLabel;
	QMenuBar *pMenuBar;
	QToolBar *pToolBar;
	QStatusBar* pStatusBar;

	QDockWidget *pDataDoc;
	QDockWidget *pOutputDoc;
	QTextEdit *pOutPutText;

public:
	QAction *pActionOption;
};

#endif // REPLICATIONTOOL_H
