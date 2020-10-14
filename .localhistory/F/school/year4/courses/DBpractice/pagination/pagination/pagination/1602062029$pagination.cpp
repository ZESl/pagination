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
		tr("images(*.png *jpeg *bmp);;video files(*.avi *.mp4 *.wmv);;All files(*.*)"));
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "Warning!", "Failed to open the video!");
	}
	else {
		Test *t = new Test();
		t->show();
		Mat cover = imread(fileName.toStdString(), IMREAD_COLOR);
		t->setLabelText(fileName);
		cvtColor(cover, cover, COLOR_BGR2RGB);
		QImage image = QImage((const uchar*)cover.data,
			cover.cols, cover.rows, cover.step,
			QImage::Format_RGB888);
		t->setLabelFrame(image);
	}
}
