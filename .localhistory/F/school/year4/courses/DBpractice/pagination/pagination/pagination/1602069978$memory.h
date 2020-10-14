#pragma once
#define MEM_NUM 999
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
	int[MEM_NUM] m_anStack;


};

