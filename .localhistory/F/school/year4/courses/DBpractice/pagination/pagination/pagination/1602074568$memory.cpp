#include "memory.h"



memory::memory(QString fileName)
{
}


memory::~memory()
{
}

void memory::loadFile()
{
	QFile myfile(fileName);
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))
}

void memory::readPage()
{
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