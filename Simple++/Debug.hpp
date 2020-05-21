template<typename T>
std::vector<MemoryAllocation> DebugT<T>::_debugMemoryAllocations;

template<typename T>
DebugT<T>::DebugT( void ) {}

template<typename T>
DebugT<T>::~DebugT( void ) {}

template<typename T>
void DebugT<T>::_debugNew( const TCHAR * fileName, int lineNumber, T memoryAddress, T memorySize ) {
	MemoryAllocation * memoryAllocation = DebugT<T>::getMemoryAllocationByAddress( memoryAddress );

	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[ i ].getMemoryAddress() == memoryAddress ) {
			if ( _debugMemoryAllocations[ i ].isAllocated() ) {
				Log::displayError( StringASCII::format("System allocated a memory already set ?!?!?\n Allocation at %@% and previously at %@%", fileName, lineNumber, _debugMemoryAllocations[ i ].getAllocationFileName(), _debugMemoryAllocations[ i ].getAllocationLineNumber() ) );
			}
			_debugMemoryAllocations.erase( _debugMemoryAllocations.begin() + i );
		}
	}
	_debugMemoryAllocations.push_back( MemoryAllocation( memoryAddress, memorySize, fileName, lineNumber ) );
}

template<typename T>
void DebugT<T>::_debugNew( T memoryAddress, T memorySize ) {
	_debugNew( TEXT( "" ), 0, memoryAddress, memorySize );
}

template<typename T>
void DebugT<T>::_debugDelete( const TCHAR * fileName, int lineNumber, T memoryAddress ) {
	//A delete null is useless
	if ( memoryAddress == NULL )
		return;

	MemoryAllocation * memoryAllocation = DebugT<T>::getMemoryAllocationByAddress( memoryAddress );

	if ( memoryAllocation == NULL ) {
		Log::displayError( StringASCII::format("Memory delete at %@% was unable to detect his allocation !", fileName, lineNumber ) );
		return;
	}

	if ( !memoryAllocation -> isAllocated() ) {
		Log::displayError( StringASCII::format("Memory delete at %@% is deleting a ALREADY deleted space. Previously deleted at %@%", fileName, lineNumber, memoryAllocation -> getDeleteFileName(), memoryAllocation -> getDeleteLineNumber() ) );
		return;
	}

	memoryAllocation -> setDeleteFileName( fileName );
	memoryAllocation -> setDeleteLineNumber( lineNumber );
	memoryAllocation -> setAllocated( false );


	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		//if the memory allocation is himself, bypass and do nothing
		if ( &_debugMemoryAllocations[ i ] == memoryAllocation )
			continue;

		//if the space is already allocated, bypass
		if ( _debugMemoryAllocations[ i ].isAllocated() )
			continue;

		continue;
		//checking for double delete
		if ( _debugMemoryAllocations[ i ].getMemoryAddress() < memoryAllocation -> getMemoryAddress() &&
			_debugMemoryAllocations[ i ].getMemoryAddress() + _debugMemoryAllocations[ i ].getMemorySize() >= memoryAllocation -> getMemoryAddress() ) {
			Log::displayError( StringASCII::format("Memory delete at %@% is deleting a ALREADY deleted space. Previously deleted at %@%", fileName, lineNumber, _debugMemoryAllocations[ i ].getDeleteFileName(), _debugMemoryAllocations[ i ].getDeleteLineNumber() ) );
			continue;
		} else if ( _debugMemoryAllocations[ i ].getMemoryAddress() < memoryAllocation -> getMemoryAddress() + memoryAllocation -> getMemorySize() &&
			_debugMemoryAllocations[ i ].getMemoryAddress() > memoryAllocation -> getMemoryAddress() ) {
			Log::displayError( StringASCII::format("Memory delete at %@% is deleting a ALREADY deleted space. Previously deleted at %@%", fileName, lineNumber, _debugMemoryAllocations[ i ].getDeleteFileName(), _debugMemoryAllocations[ i ].getDeleteLineNumber() ) );
			continue;
		}
	}


	//delete his value
	_debugMemoryAllocations.erase( _debugMemoryAllocations.begin() + getMemoryAllocationIndexByAddress( memoryAddress ) );

}

template<typename T>
void DebugT<T>::_debugDelete( T address ) {
	_debugDelete( TEXT( "" ), 0, address );
}

template<typename T>
MemoryAllocation * DebugT<T>::getMemoryAllocationByAddress( T memoryAddress ) {
	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[ i ].getMemoryAddress() == memoryAddress )
			return &( _debugMemoryAllocations[ i ] );
	}
	return NULL;
}

template<typename T>
unsigned int DebugT<T>::getMemoryAllocationIndexByAddress( T memoryAddress ) {
	for ( unsigned int i = 0; i < _debugMemoryAllocations.size(); i++ ) {
		if ( _debugMemoryAllocations[ i ].getMemoryAddress() == memoryAddress )
			return i;
	}
	return 0;
}
