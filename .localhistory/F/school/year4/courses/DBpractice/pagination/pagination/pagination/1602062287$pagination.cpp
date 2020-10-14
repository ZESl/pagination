#include "pagination.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

pagination::pagination(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	// Read File Little Prince.txt
	QFile myfile("Little Prince.txt");
	if (myfile.open(QFile::ReadOnly))
	{
		QTextStream in(&myfile);

	}

}

//Read
void pagination::on_pushButton_clicked()
{
	// clear the log file
	QFile myfile("log.txt");
	if (myfile.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&myfile);
		out << "" << endl;
	}

	
}

void pagination::saveFile()
{

}

//Save
void pagination::on_pushButton_2_clicked()
{

}

//Add a page
void pagination::on_pushButton_3_clicked()
{

}

//Open file
void pagination::on_pushButton_4_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
		this,
		tr("open a file."),
		"D:/",
		tr("txt(*.txt);;All files(*.*)"));
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "Warning!", "Failed to open the video!");
	}
	else {
		QFile myfile(fileName);
		if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))		{			QTextStream in(&myfile);			QString line = in.readLine();			while (!line.isNull()) {				// todo line				line = in.readLine();			}		}
	}
}
