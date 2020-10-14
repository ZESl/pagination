#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pagination.h"

class pagination : public QMainWindow
{
    Q_OBJECT

public:
    pagination(QWidget *parent = Q_NULLPTR);

private:
    Ui::paginationClass ui;

	int m_cbPageNum;
	QString m_strContent;
	QString m_strMemory;

private slots:
	void on_pushButton_clicked();	//Read
	void on_pushButton_2_clicked();	//Save
	void on_pushButton_3_clicked();	//Add a page
	void on_pushButton_4_clicked();	//Open file
};
