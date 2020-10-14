#pragma once

#define MEM_NUM 4
#include <QtWidgets/QMainWindow>
#include "ui_pagination.h"
#include "memory.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

class pagination : public QMainWindow
{
    Q_OBJECT

public:
    pagination(QWidget *parent = Q_NULLPTR);

private:
    Ui::paginationClass ui;

	int m_cbPageNum;
	int pageno;
	QString m_strContent;
	QString m_strMemory;

	memory* m_memory;

private slots:
	void on_pushButton_clicked();	//Read
	void on_pushButton_2_clicked();	//Save
	void on_pushButton_3_clicked();	//Add a page
	void on_pushButton_4_clicked();	//Open file

protected:
	void updatePage();
	void closeEvent(QCloseEvent *event);
};
