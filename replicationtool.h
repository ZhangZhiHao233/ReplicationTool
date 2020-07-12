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
	//�˵���-�ļ�
	void open_Slot();
	void save_Slot();
	void saveAs_Slot();
	void recentOpen_Slot();
	void exit_Slot();
	//�˵���-����
	void offSound_Slot();
	void forceProgram_Slot();
	//�˵���-����
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
	//�˵���-����
	void toolBar_Slot(bool);
	void stateBar_Slot(bool);
	void optionBar_Slot(bool);
	void dataOutputBar_Slot(bool);

	//������-�ɱ༭
	void editable_Slot();	

	//״̬��-ʱ��
	void timeUpdate_Slot();

	//оƬѡ��
	void selectChip_Slot();

	//����option����
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
