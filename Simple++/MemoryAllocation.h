#pragma once

#include "String.h"


class MemoryAllocation{
public:
	MemoryAllocation(void);
	MemoryAllocation(unsigned long memoryAddress, unsigned long memorySize, const String & allocationFileName, unsigned int lineNumber);
	~MemoryAllocation(void);

	void setAllocationFileName(const String & fileName);
	void setAllocationLineNumber(int lineNumber);

	void setDeleteFileName(const String & fileName);
	void setDeleteLineNumber(int lineNumber);

	void setMemoryAddress(unsigned long long address);
	void setMemorySize(unsigned long long size);

	const String & getAllocationFileName() const;
	int getAllocationLineNumber() const;

	const String & getDeleteFileName() const;
	int getDeleteLineNumber() const;

	unsigned long long getMemoryAddress() const;
	unsigned long long getMemorySize() const;

	void setAllocated(bool value);

	bool isAllocated() const;


private:
	bool bAllocated;

	String allocationFileName;
    int allocationLineNumber;

	String deleteFileName;
	int deleteLineNumber;

	unsigned long long memoryAddress;
	unsigned long long memorySize;
};


#include "MemoryAllocation.hpp"
