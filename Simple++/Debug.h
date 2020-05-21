#pragma once

#include <vector>
#include "Log.h"
#include "MemoryAllocation.h"


#ifdef DEBUG
#define debugNew(address, size); Debug::_debugNew((unsigned long long)address, size);
#define debugDelete(address); Debug::_debugDelete((unsigned long long)address);
#else
#define debugNew(address, size);
#define debugDelete(address);
#endif

template<typename T>
class DebugT {
public:
	DebugT( void );
	virtual ~DebugT( void );


	static void _debugNew( const TCHAR * fileName, int lineNumber, T memoryAddress, T memorySize );
	static void _debugNew( T memoryAddress, T memorySize );

	static void _debugDelete( const TCHAR * fileName, int lineNumber, T address );
	static void _debugDelete( T address );


	static std::vector<MemoryAllocation> _debugMemoryAllocations;



private:
	static MemoryAllocation * getMemoryAllocationByAddress( T memoryAddress );
	static unsigned int getMemoryAllocationIndexByAddress( T memoryAddress );

};

using Debug = DebugT<unsigned long long>;

#include "Debug.hpp"

