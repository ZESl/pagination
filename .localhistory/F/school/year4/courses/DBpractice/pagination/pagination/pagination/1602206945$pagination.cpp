#include "pagination.h"
#define PAGE_SIZE (4*1024)

pagination::pagination(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	m_memory = new memory();
}

//Read
void pagination::on_pushButton_clicked()
{
	int pageno = ui.comboBox->currentIndex();
	char* pStr;
	m_memory->ReadPage(pageno, pStr, PAGE_SIZE);
	m_strContent = QString(QLatin1String(pStr));
	ui.textBrowser->setText(m_strContent);

	int mem_block = m_memory->QueryMemory(pageno);
	// todo
	ui.lineEdit->setText("");
}

//Save
void pagination::on_pushButton_2_clicked()
{
	int pageno = ui.comboBox->currentIndex();
	QString str = ui.textBrowser->toPlainText();
	char* pStr = str.toLatin1().data();
	m_memory->UpdatePage(pageno, pStr, PAGE_SIZE);
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
