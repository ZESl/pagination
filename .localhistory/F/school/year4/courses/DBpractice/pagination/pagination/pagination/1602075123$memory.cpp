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
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))
	else {
		return false;
	}
}

int memory::readPage(const int pageno, char* pStr, const int nMaxSize)
{
}

int memory::QueryMemory(const int)
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