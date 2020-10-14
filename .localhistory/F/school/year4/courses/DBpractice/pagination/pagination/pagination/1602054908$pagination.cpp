#include "pagination.h"
#include <QDebug>

pagination::pagination(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//Read
void pagination::on_pushButton_clicked()
{

}

//Save
void pagination::on_pushButton2_clicked()
{
}

//Add a page
void pagination::on_pushButton3_clicked()
{
}

//Open file
void pagination::on_pushButton4_clicked()
{
	qDebug()<<"open file"<<endl;
}
