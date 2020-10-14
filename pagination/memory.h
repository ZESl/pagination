#pragma once

#define PAGE_SIZE (4*1024)
#define MEM_NUM 4
#include <windows.h>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <malloc.h>

using namespace std;

struct MemBlock
{
	int no; // Number
	char* content; // Memory page content
};

struct PageItem
{
	int pageno; // Page number.
	bool load; // Determine whether it has been loaded into the memory, false: it has not been loaded, true: it has been loaded into the memory.
	bool modify; // Whether it has been modified, false it has not bee modified, true it has been modified.
	ULONGLONG position; // Indicate the start address of this page on the file.
	int memno; // Physical block number.
};

class memory
{
public:
	memory();
	~memory();

	PageItem* m_pPageTable;
	int pageNum;

	MemBlock* m_pMemory;
	int m_anStack[MEM_NUM];		//Stack bottom:m_anStack[0] Stack top:int m_nStackSize;
	int stackTop;
	QString txtFileName;

	int LoadFile(QString);
	char* ReadPage(const int);
	bool UpdatePage(const int, string, const int);
	void addPage();
	void WriteBack();	//Write back the modified page information in the memory. Call before the program ends.
	int GetPageNum();	// Get the total page number.
	int QueryMemory(const int);

	void PushStack(const int);
	int PopStack();


private:
	
};

