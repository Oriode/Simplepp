#pragma once

#include "String.h"


class MemoryAllocation {
public:
	MemoryAllocation( void );
	MemoryAllocation( unsigned long memoryAddress, unsigned long memorySize, const StringASCII & allocationFileName, unsigned int lineNumber );
	~MemoryAllocation( void );

	void setAllocationFileName( const StringASCII & fileName );
	void setAllocationLineNumber( int lineNumber );

	void setDeleteFileName( const StringASCII & fileName );
	void setDeleteLineNumber( int lineNumber );

	void setMemoryAddress( unsigned long long address );
	void setMemorySize( unsigned long long size );

	const StringASCII & getAllocationFileName() const;
	int getAllocationLineNumber() const;

	const StringASCII & getDeleteFileName() const;
	int getDeleteLineNumber() const;

	unsigned long long getMemoryAddress() const;
	unsigned long long getMemorySize() const;

	void setAllocated( bool value );

	bool isAllocated() const;


private:
	bool bAllocated;

	StringASCII allocationFileName;
	int allocationLineNumber;

	StringASCII deleteFileName;
	int deleteLineNumber;

	unsigned long long memoryAddress;
	unsigned long long memorySize;
};


#include "MemoryAllocation.hpp"
