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
	//	1. read the file	//	2. page the file according to the file size, 4*1024 bytes per page	//	3. generate the page table index information.
	//	1. read the file
	QFile myfile(fileName);
	if (myfile.open(QIODevice::ReadOnly | QIODevice::Text)) {		// 2. page the file according to the file size, 4*1024 bytes per page		ULONGLONG size = myfile.size();		qDebug() << "size:" << QString::number(size) << endl;		// 110592		int pageNum = size / PAGE_SIZE + 1;		m_pPageTable = (PageItem *)malloc(pageNum * sizeof(PageItem));				//	3. generate the page table index information.		for (int i = 0; i < pageNum; i++) {			PageItem tmp = { i, false, false, i*PAGE_SIZE, i};			m_pPageTable[i] = tmp;		}		return true;	}

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
