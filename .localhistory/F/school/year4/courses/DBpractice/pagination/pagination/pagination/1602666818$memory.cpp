#include "memory.h"
#include <iostream>
#include <fstream>
using namespace std;

memory::memory()
{
	m_pMemory = (MemBlock *)malloc(MEM_NUM * sizeof(MemBlock));
	memset(m_anStack, -1, MEM_NUM * sizeof(int));
	stackTop = -1;
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
		qDebug() << "size:" << QString::number(size)  << endl;

		if (size % PAGE_SIZE != 0) {
			pageNum = size / PAGE_SIZE + 1;
		}
		else {
			pageNum = size / PAGE_SIZE;
		}
		
		m_pPageTable = NULL;
		m_pPageTable = (PageItem *)malloc(pageNum * sizeof(PageItem));

		//	3. generate the page table index information.
		for (int i = 0; i < pageNum; i++) {
			PageItem tmp = { i, false, false, (ULONGLONG)i*PAGE_SIZE, -1 };
			m_pPageTable[i] = tmp;
		}
		return pageNum;
	}
	else {
		return 0;
	}
}

char* memory::ReadPage(const int pageno)
{
	PushStack(pageno);
	if (m_pPageTable[pageno].load) {
		int memno = m_pPageTable[pageno].memno;
		//char* pStr = (char*)malloc(PAGE_SIZE);
		char pStr[PAGE_SIZE];
		memcpy(pStr, m_pMemory[memno].content, PAGE_SIZE);
		qDebug() << "FROM MEMORY";
		//qDebug() << pStr << endl;
		return pStr;
	}
	else {
		m_pPageTable[pageno].load = true;
		string str = txtFileName.toStdString();
		const char* name = str.c_str();

		char pStr[PAGE_SIZE];
	
		FILE* pfile = nullptr;
		fopen_s(&pfile, name, "rb");
		fseek(pfile, m_pPageTable[pageno].position, SEEK_SET);
		fread(pStr, 1, PAGE_SIZE, pfile);
		fclose(pfile);

		int memno = m_pPageTable[pageno].memno;
		m_pMemory[memno].no = memno;
		memcpy(m_pMemory[memno].content, pStr, PAGE_SIZE);
		qDebug() << "FROM FILE";
		//qDebug() << pStr << endl;
		return pStr;
	}	
}

bool memory::UpdatePage(const int pageno, string str, const int nMaxSize)
{
	// Query whether this page has existed in the current memory block. 
	// If it has existed, update the content in the memory block, and set the modification identifier as true. 
	// If it does not exist, load this page.
	bool exist = false;
	for (int i = 0; i < MEM_NUM; i++) {
		if (pageno == m_anStack[i]) {
			exist = true;
		}
	}
	// search whether this page number has existed in the stack
	if (exist) {
		// fill in the blank
		int len = str.length();
		if (len < PAGE_SIZE) {
			for (int b = len; b < PAGE_SIZE; b++) {
				str += " ";
			}
			str += '\0';
		}
		m_pPageTable[pageno].modify = true;
		int no = m_pPageTable[pageno].memno;
		const char* pStr = str.c_str();
		strcpy(m_pMemory[no].content, pStr);
	}
	/*else {
		ReadPage(pageno, pStr, nMaxSize);
	}*/
	return true;
}

void memory::addPage()
{
	// When a new page is added, allocate the memory space for the page table again
	pageNum++;
	m_pPageTable = (PageItem *)realloc(m_pPageTable, pageNum * sizeof(PageItem));
	PageItem tmp = { pageNum-1, true, true, (pageNum-1)*PAGE_SIZE, -1 };
	m_pPageTable[pageNum - 1] = tmp;

	string text = "";
	for (int g = 0; g < PAGE_SIZE; g++) {
		text = text + " ";
	}
	text = text + '\0';
	const char* str = text.c_str();
	FILE* pfile = nullptr;
	string name = txtFileName.toStdString();
	const char* fileName = name.c_str();
	// 在文件最后追加
	fopen_s(&pfile, fileName, "ab+");
	fprintf_s(pfile, str);
	fclose(pfile);
}

void memory::WriteBack()
{
	// When the window is logged out, write back all records in the page table.
	// traverse the whole page table, find the modified page in the memory, and write back into the file.
	FILE* pfile = nullptr;
	FILE* temp = nullptr;
	string str = txtFileName.toStdString();
	const char* fileName = str.c_str();
	fopen_s(&pfile, fileName, "rb");
	fopen_s(&temp, "temp.txt", "wb");
	for (int i = 0; i < pageNum; i++) {
		if (m_pPageTable[i].modify) {
			int memno = m_pPageTable[i].memno;
			// writeback the memory
			fwrite(m_pMemory[memno].content, 1, PAGE_SIZE, temp);
			m_pPageTable[i].modify = false;
		}
		else {
			// writeback the original file
			char* pStr = NULL;
			pStr = (char *)malloc(PAGE_SIZE * sizeof(char));
			fseek(pfile, m_pPageTable[i].position, SEEK_SET);
			fread(pStr, 1, PAGE_SIZE, pfile);
			fwrite(pStr, 1, PAGE_SIZE, temp);
		}
	}
	fclose(pfile);
	fclose(temp);
	remove("Little Prince.txt");
	rename("temp.txt", "Little Prince.txt");
}

int memory::GetPageNum()
{
	return pageNum;
}

int memory::QueryMemory(const int pageno)
{
	return m_pPageTable[pageno].memno;
}

void memory::PushStack(const int pageno)
{
	bool exist = false;
	for (int i = 0; i < MEM_NUM; i++) {
		if (pageno == m_anStack[i]) {
			exist = true;
		}
	}
	// search whether this page number has existed in the stack
	if (exist) {
		// move this page number to the stack top
		for (int i = 0; i < MEM_NUM; i++) {
			if (pageno == m_anStack[i]) {
				for (int j = i; j < stackTop; j++) {
					m_anStack[j] = m_anStack[j + 1];
				}
				m_anStack[stackTop] = pageno;
				break;
			}
		}
	}
	else {
		// If it does not exist, add it.
		if (stackTop == MEM_NUM - 1) {
			// If the stack has been full, move out the element of the stack bottom
			// and put this number on the stack top.
			m_pPageTable[m_anStack[0]].modify = false;
			m_pPageTable[m_anStack[0]].load = false;
			m_pPageTable[pageno].memno = m_pPageTable[m_anStack[0]].memno;	// replace
			m_pPageTable[m_anStack[0]].memno = -1;

			for (int j = 0; j < MEM_NUM - 1; j++) {
				m_anStack[j] = m_anStack[j + 1];
			}
			m_anStack[MEM_NUM - 1] = pageno;
		}
		else {
			stackTop++;
			m_anStack[stackTop] = pageno;
			m_pPageTable[pageno].memno = stackTop;
		}
	}	
}

int memory::PopStack()
{
	return m_anStack[0];
}
