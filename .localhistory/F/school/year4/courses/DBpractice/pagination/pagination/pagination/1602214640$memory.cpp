﻿#include "memory.h"
#include <iostream>
#include <fstream>
using namespace std;

memory::memory()
{
	m_pMemory = (MemBlock *)malloc(MEM_NUM * sizeof(MemBlock));
	memset(m_anStack, -1, MEM_NUM * sizeof(int));
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

		pageNum = size / PAGE_SIZE + 1;
		m_pPageTable = (PageItem *)malloc(pageNum * sizeof(PageItem));

		//	3. generate the page table index information.
		for (int i = 0; i < pageNum; i++) {
			PageItem tmp = { i, false, false, i*PAGE_SIZE, -1 };
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
	
	ifstream f = ifstream(name, ios::in);
	int offset = m_pPageTable[pageno].position;
	f.seekg(offset);
	f.get(pStr, nMaxSize);
	f.close();

	qDebug() << QString(QLatin1String(pStr)) << endl;

	return 0;
}

bool memory::UpdatePage(const int pageno, char * pStr, const int nMaxSize)
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
		m_pPageTable[pageno].modify = true;

		int no = m_pPageTable[pageno].memno;
		strcpy(m_pMemory[no].content, pStr);
	}
	else {
		ReadPage(pageno, pStr, nMaxSize);
	}
	return true;
}

void memory::addPage()
{
	// When a new page is added, allocate the memory space for the page table again
	pageNum++;
	m_pPageTable = (PageItem *)realloc(m_pPageTable, pageNum * sizeof(PageItem));
	PageItem tmp = { pageNum-1, false, false, (pageNum - 1)*PAGE_SIZE, -1 };
	m_pPageTable[pageNum - 1] = tmp;
}

void memory::WriteBack()
{
	// When the window is logged out, write back all records in the page table.
	// traverse the whole page table, find the modified page in the memory, and write back into the file.
	for (int i = 0; i < pageNum; i++) {
		if (m_pPageTable[i].modify) {
			int memno = m_pPageTable[i].memno;

			// writeback
			char* name = txtFileName.toLatin1().data();
			ofstream f = ofstream(name);
			int offset = m_pPageTable[i].position;
			f.seekp(offset);
			f.write(m_pMemory[memno].content, strlen(m_pMemory[memno].content));
			f.close();

			m_pPageTable[i].modify = false;
		}
	}
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
		// If it has existed, move this page number to the stack top
		for (int i = 0; i < MEM_NUM; i++) {
			if (pageno == m_anStack[i]) {
				for (int j = i; j < MEM_NUM-1; j++) {
					m_anStack[j] = m_anStack[j+1];
				}
				m_anStack[MEM_NUM - 1] = pageno;
				break;
			}
		}
	}
	else {
		// If it does not exist, add it.
		if (stackTop == MEM_NUM - 1) {
			// If the stack has been full, move out the element of the stack bottom
			// and put this number on the stack top.
			for (int j = 0; j < MEM_NUM - 1; j++) {
				m_anStack[j] = m_anStack[j + 1];
			}
			m_anStack[MEM_NUM - 1] = pageno;
		}
		else {
			m_anStack[stackTop] = pageno;
			stackTop++;
		}
	}
	
}

int memory::PopStack()
{
	return m_anStack[0];
}
