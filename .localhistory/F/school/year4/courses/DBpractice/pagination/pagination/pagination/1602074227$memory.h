#pragma once

#define PAGE_SIZE (4*1024)
#define MEM_NUM 16
#include <windows.h>
using namespace std;

struct MemBlock
{
	int no; // Number
	char content[PAGE_SIZE]; // Memory page content
};

struct Index
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

	void loadFile();
	void readPage();
	void updatePage();
	void addPage();
	void writeBack();
	void getPageNum();
	void getMemInfo();

private:
	int m_anStack[MEM_NUM];		// m_anStack[0];	//Stack bottom
	int m_nStackSize;	//Stack top

};

