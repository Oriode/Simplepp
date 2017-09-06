#include "Debug.h"

std::vector<MemoryAllocation> Debug::_debugMemoryAllocations;




Debug::Debug( void ) {
}


Debug::~Debug( void ) {
}

void Debug::_debugNew( const char * fileName, int lineNumber, unsigned long memoryAddress, unsigned long memorySize ) {
	MemoryAllocation * memoryAllocation = Debug::getMemoryAllocationByAddress( memoryAddress );

	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[i].getMemoryAddress() == memoryAddress ) {
			if ( _debugMemoryAllocations[i].isAllocated() ) {
				Log::displayError( StringASCII( "System allocated a memory already set ?!?!?\n Allocation at " ) + fileName + "@" + lineNumber + " and previously at " + _debugMemoryAllocations[i].getAllocationFileName() + "@" + _debugMemoryAllocations[i].getAllocationLineNumber() );
			}
			_debugMemoryAllocations.erase( _debugMemoryAllocations.begin() + i );
		}
	}
	_debugMemoryAllocations.push_back( MemoryAllocation( memoryAddress, memorySize, std::string( fileName ), lineNumber ) );
}

void Debug::_debugNew( unsigned long memoryAddress, unsigned long memorySize ) {
	_debugNew( "", 0, memoryAddress, memorySize );
}

void Debug::_debugDelete( const char * fileName, int lineNumber, unsigned long memoryAddress ) {
	//A delete null is useless
	if ( memoryAddress == NULL )
		return;

	MemoryAllocation * memoryAllocation = Debug::getMemoryAllocationByAddress( memoryAddress );

	if ( memoryAllocation == NULL ) {
		Log::displayError( StringASCII( "Memory delete at " ) + fileName + "@" + lineNumber + " was unable to detect his allocation !" );
		return;
	}

	if ( !memoryAllocation -> isAllocated() ) {
		Log::displayError( StringASCII( "Memory delete at " ) + fileName + "@" + lineNumber + " is deleting a ALREADY deleted space. Previously deleted at " + memoryAllocation -> getDeleteFileName() + "@" + memoryAllocation -> getDeleteLineNumber() );
		return;
	}

	memoryAllocation -> setDeleteFileName( fileName );
	memoryAllocation -> setDeleteLineNumber( lineNumber );
	memoryAllocation -> setAllocated( false );


	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		//if the memory allocation is himself, bypass and do nothing
		if ( &_debugMemoryAllocations[i] == memoryAllocation )
			continue;

		//if the space is already allocated, bypass
		if ( _debugMemoryAllocations[i].isAllocated() )
			continue;

		continue;
		//checking for double delete
		if ( _debugMemoryAllocations[i].getMemoryAddress() < memoryAllocation -> getMemoryAddress() &&
			 _debugMemoryAllocations[i].getMemoryAddress() + _debugMemoryAllocations[i].getMemorySize() >= memoryAllocation -> getMemoryAddress() ) {
			Log::displayError( StringASCII( "Memory delete at " ) + fileName + "@" + lineNumber + " is deleting a ALREADY deleted space. Previously deleted at " + _debugMemoryAllocations[i].getDeleteFileName() + "@" + _debugMemoryAllocations[i].getDeleteLineNumber() );
			continue;
		} else if ( _debugMemoryAllocations[i].getMemoryAddress() < memoryAllocation -> getMemoryAddress() + memoryAllocation -> getMemorySize() &&
					_debugMemoryAllocations[i].getMemoryAddress() > memoryAllocation -> getMemoryAddress() ) {
			Log::displayError( StringASCII( "Memory delete at " ) + fileName + "@" + lineNumber + " is deleting a ALREADY deleted space. Previously deleted at " + _debugMemoryAllocations[i].getDeleteFileName() + "@" + _debugMemoryAllocations[i].getDeleteLineNumber() );
			continue;
		}
	}


	//delete his value
	_debugMemoryAllocations.erase( _debugMemoryAllocations.begin() + getMemoryAllocationIndexByAddress( memoryAddress ) );

}

void Debug::_debugDelete( unsigned long address ) {
	_debugDelete( "", 0, address );
}

MemoryAllocation * Debug::getMemoryAllocationByAddress( unsigned long memoryAddress ) {
	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[i].getMemoryAddress() == memoryAddress )
			return &( _debugMemoryAllocations[i] );
	}
	return NULL;
}

unsigned int Debug::getMemoryAllocationIndexByAddress( unsigned long memoryAddress ) {
	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[i].getMemoryAddress() == memoryAddress )
			return i;
	}
	return 0;
}
