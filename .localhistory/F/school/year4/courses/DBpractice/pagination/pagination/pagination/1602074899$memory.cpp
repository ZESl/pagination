#include "memory.h"



memory::memory()
{
}


memory::~memory()
{
}

bool memory::loadFile(QString fileName)
{
	QFile myfile(fileName);
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))	{		QTextStream in(&myfile);		QString line = in.readLine();		while (!line.isNull()) {			// todo line			line = in.readLine();		}	}
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
