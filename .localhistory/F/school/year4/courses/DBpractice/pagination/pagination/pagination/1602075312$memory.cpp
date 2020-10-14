#include "memory.h"



memory::memory()
{
}


memory::~memory()
{
}

// Read File Little Prince.txt
bool memory::loadFile(QString fileName)
{
	QFile myfile(fileName);
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))	{		QTextStream in(&myfile);		QString line = in.readLine();		while (!line.isNull()) {			// read the file			// page the file according to the file size, 4*1024 bytes per page			// and generate the page table index information.			line = in.readLine();			return true;		}	}
	else {
		return false;
	}
}

int memory::readPage(const int pageno, char* pStr, const int nMaxSize)
{
}

int memory::QueryMemory(const int pageno)
{
	return 0;
}

void memory::PushStack(const int pageno)
{
}

int memory::PopStack()
{
	return 0;
}

void memory::updatePage()
{
}

void memory::addPage()
{
}

void memory::writeBack()
{
}

void memory::getPageNum()
{
}

void memory::getMemInfo()
{
}
