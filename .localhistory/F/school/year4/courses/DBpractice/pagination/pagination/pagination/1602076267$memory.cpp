#include "memory.h"



memory::memory()
{
}


memory::~memory()
{
}

// Read File Little Prince.txt
bool memory::LoadFile(QString fileName)
{
	//QFile myfile(fileName);
	//if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))	//{	//	int size = myfile.size();	//	qDebug() << size << endl;	//	//QTextStream in(&myfile);	//	//QString line = in.readLine();	//	//while (!line.isNull()) {	//	////	 read the file	//	////	 page the file according to the file size, 4*1024 bytes per page	//	////	 and generate the page table index information.	//	//	line = in.readLine();	//	//	//	//}	//	return true;	//}
	return false;
}

int memory::ReadPage(const int pageno, char* pStr, const int nMaxSize)
{
	// PushStack()
	return 0;
}

bool memory::UpdatePage(const int pageno, char * pStr, const int nMaxSize)
{
	// PushStack()
	return false;
}

void memory::addPage()
{
}

void memory::WriteBack()
{
}

void memory::GetPageNum()
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
