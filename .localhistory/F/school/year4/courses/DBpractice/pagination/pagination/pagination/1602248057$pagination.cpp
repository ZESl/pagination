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
	checkIfModified();
	pageno = ui.comboBox->currentIndex();
	char* pStr = NULL;
	pStr = (char *)malloc(PAGE_SIZE * sizeof(char));
	m_memory->ReadPage(pageno, pStr, PAGE_SIZE);
	m_strContent = QString(QLatin1String(pStr));
	ui.textBrowser->setText(m_strContent);

	int mem_block = m_memory->QueryMemory(pageno);
	QString msg = "";
	for (int i = 0; i < MEM_NUM; i++) {
		msg += " ";
		msg += QString::number(m_memory->m_anStack[i]);
	}
	ui.lineEdit->setText(msg);
}

//Save
void pagination::on_pushButton_2_clicked()
{
	checkIfModified();
	int pageno = ui.comboBox->currentIndex();
	QString qstr = ui.textBrowser->toPlainText();
	string str = qstr.toStdString();
	m_memory->UpdatePage(pageno, str, PAGE_SIZE);
}

//Add a page
void pagination::on_pushButton_3_clicked()
{
	checkIfModified();
	m_memory->addPage();
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

void pagination::checkIfModified()
{
	QString qstr = ui.textBrowser->toPlainText();
	qDebug() << m_strContent << endl;
	qDebug() << qstr << endl;
	if (m_strContent == qstr) {
		// do nothing
	}
	else{
		QMessageBox::StandardButton result = QMessageBox::information(NULL, "Warning", "Save the current text?", QMessageBox::Yes | QMessageBox::No);
		switch (result)
		{
			case QMessageBox::Yes:
			{
				qDebug() << "Yes";
				//string str = ui.textBrowser->toPlainText().toStdString();
				//char* pStr = str.c_str();

				//char*  pStr;
				//QByteArray ba = str.toLatin1(); // must
				//pStr = ba.data();

				string str = qstr.toStdString();
				m_memory->UpdatePage(pageno, str, PAGE_SIZE);
				break;
			}

			case QMessageBox::No:
				qDebug() << "NO";
				break;

			default:
				break;
		}
	}
}

void pagination::closeEvent(QCloseEvent *event)
{
	// before destroy the window
	// m_memory->WriteBack();
}