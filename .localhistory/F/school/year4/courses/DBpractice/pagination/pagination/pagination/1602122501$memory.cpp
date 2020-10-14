#include "memory.h"


memory::memory()
{
	m_pMemory = (MemBlock *)malloc(MEM_NUM * sizeof(MemBlock));
	memset(m_anStack, -1, int);
}


memory::~memory()
{
}

//	1. read the file
//	2. page the file according to the file size, 4*1024 bytes per page
//	3. generate the page table index information.
int memory::LoadFile(QString fileName)
{
	//	1. read the file
	qDebug() << "opening file" << fileName << endl;
	QFile myfile(fileName);
	if (myfile.open(QFile::ReadOnly | QIODevice::Text)) {
		
		// 2. page the file according to the file size, 4*1024 bytes per page
		int size = myfile.size();
		qDebug() << "size:" << endl;
		qDebug() << QString::number(size) << endl;		// 110592

		int pageNum = size / PAGE_SIZE + 1;
		m_pPageTable = (PageItem *)malloc(pageNum * sizeof(PageItem));

		//	3. generate the page table index information.
		for (int i = 0; i < pageNum; i++) {
			PageItem tmp = { i, false, false, i*PAGE_SIZE, i };
			m_pPageTable[i] = tmp;
		}
		return pageNum;
	}
	else {
		return 0;
	}
}

int memory::ReadPage(const int pageno, char* pStr, const int nMaxSize)
{
	PushStack(pageno);
	m_pPageTable[pageno];
	return 0;
}

bool memory::UpdatePage(const int pageno, char * pStr, const int nMaxSize)
{
	PushStack(pageno);

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
	m_anStack[]
	m_pMemory[]
}

int memory::PopStack()
{
	m_anStack[0];	//stack bottom
	return 0;
}
