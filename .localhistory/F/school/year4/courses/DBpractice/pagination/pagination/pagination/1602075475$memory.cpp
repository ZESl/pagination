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
	// PushStack()
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
	// PushStack()
}

bool memory::UpdatePage(const int pageno, char * pStr, const int nMaxSize)
{
	return false;
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