#include "pagination.h"

pagination::pagination(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	m_memory = new memory();
}

//Read
void pagination::on_pushButton_clicked()
{



	//// clear the log file
	//QFile myfile("log.txt");
	//if (myfile.open(QFile::WriteOnly | QIODevice::Truncate))
	//{
	//	QTextStream out(&myfile);
	//	out << "" << endl;
	//}	
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("open a file."), "", tr("txt(*.txt);;All files(*.*)"));
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "Warning!", "No file selected!");
	}
	else {
		// load the file
		int pageNum = m_memory->LoadFile(fileName);
		if (pageNum>0) {
			QMessageBox::warning(this, "Success!", "Already opened the file!");
			
			for (int i = 0; i < pageNum; i++) {
				ui.comboBox->addItem(i);
			}
			
		}
		else {
			QMessageBox::warning(this, "Warning!", "Failed to load the file!");
		}
	}
}
