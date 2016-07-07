#pragma once

#include <vector>
#include "Log.h"
#include "MemoryAllocation.h"


#ifdef DEBUG
#define debugNew(address, size); Debug::_debugNew((unsigned long)address, size);
#define debugDelete(address); Debug::_debugDelete((unsigned long)address);
#else
#define debugNew(address, size);
#define debugDelete(address);
#endif

class Debug {
public:
	Debug( void );
	virtual ~Debug( void );


	static void _debugNew( const char * fileName, int lineNumber, unsigned long memoryAddress, unsigned long memorySize );
	static void _debugNew( unsigned long memoryAddress, unsigned long memorySize );

	static void _debugDelete( const char * fileName, int lineNumber, unsigned long address );
	static void _debugDelete( unsigned long address );


	static std::vector<MemoryAllocation> _debugMemoryAllocations;



private:
	static MemoryAllocation * getMemoryAllocationByAddress( unsigned long memoryAddress );
	static unsigned int getMemoryAllocationIndexByAddress( unsigned long memoryAddress );

};

