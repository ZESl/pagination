#include "memory.h"



memory::memory()
{
	m_pMemory = (MemBlock *)malloc(MEM_NUM * sizeof(MemBlock));
}


memory::~memory()
{
}

bool memory::LoadFile(QString fileName)
{
	//	 read the file	//	 page the file according to the file size, 4*1024 bytes per page	//	 and generate the page table index information.
	QFile myfile(fileName);
	
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text)) {		ULONGLONG size = myfile.size();		qDebug() << "size:" << endl;		qDebug() << QString::number(size) << endl;		int pageNum = 1;		m_pPageTable = (PageItem *)malloc(pageNum * sizeof(PageItem));		return true;	}

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
