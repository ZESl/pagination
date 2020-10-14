#pragma once
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
};

