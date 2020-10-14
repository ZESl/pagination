#include "memory.h"
#include <iostrream.h>

memory::memory()
{
	m_pMemory = (MemBlock *)malloc(MEM_NUM * sizeof(MemBlock));
	memset(m_anStack, -1, sizeof(int));
	stackTop = 0;
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
		txtFileName = fileName;

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
	m_pPageTable[pageno].load = true;
	m_pPageTable[pageno].memno = stackTop;
	
	char* name = txtFileName.toLatin1().data();

	ifstream f;
	f.open(name, ios::in);
	int offset = m_pPageTable[pageno].position;
	f.seekg(offset);
	pStr = (char *)malloc(nMaxSize * sizeof(char));
	pStr = f.get();
	f.close();

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
	if (stackTop == MEM_NUM - 1) {
		// 顺移
	}
	else {
		m_anStack[stackTop] = pageno;
	}
}

int memory::PopStack()
{
	m_anStack[0];	//stack bottom
	return 0;
}
