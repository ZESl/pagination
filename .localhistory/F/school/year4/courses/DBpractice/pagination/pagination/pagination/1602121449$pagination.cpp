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
		m_cbPageNum = m_memory->LoadFile(fileName);
		if (m_cbPageNum > 0) {
			// add pages to combobox
			for (int i = 0; i < m_cbPageNum; i++) {
				ui.comboBox->addItem(QString::number(i));
			}
		}
		else {
			QMessageBox::warning(this, "Warning!", "Failed to load the file!");
		}
	}
}
