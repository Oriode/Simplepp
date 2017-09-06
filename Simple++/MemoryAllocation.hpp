
MemoryAllocation::MemoryAllocation( void ) {
}

MemoryAllocation::MemoryAllocation( unsigned long memoryAddress, unsigned long memorySize, const StringASCII & allocationFileName, unsigned int lineNumber ) {
	this -> memoryAddress = memoryAddress;
	this -> memorySize = memorySize;
	this -> allocationFileName = allocationFileName;
	this -> allocationLineNumber = lineNumber;
	this -> bAllocated = true;
}


MemoryAllocation::~MemoryAllocation( void ) {
}

void MemoryAllocation::setAllocationFileName( const StringASCII & fileName ) {
	this -> allocationFileName = fileName;
}

void MemoryAllocation::setAllocationLineNumber( int lineNumber ) {
	this -> allocationFileName = lineNumber;
}

void MemoryAllocation::setDeleteFileName( const StringASCII & fileName ) {
	this -> deleteFileName = fileName;
}

void MemoryAllocation::setDeleteLineNumber( int lineNumber ) {
	this -> deleteLineNumber = lineNumber;
}

void MemoryAllocation::setMemoryAddress( unsigned long long address ) {
	this -> memoryAddress = address;
}

void MemoryAllocation::setMemorySize( unsigned long long size ) {
	this -> memorySize = size;
}

const StringASCII & MemoryAllocation::getAllocationFileName() const {
	return this -> allocationFileName;
}

int MemoryAllocation::getAllocationLineNumber() const {
	return this -> allocationLineNumber;
}

const StringASCII & MemoryAllocation::getDeleteFileName() const {
	return this -> deleteFileName;
}

int MemoryAllocation::getDeleteLineNumber() const {
	return this -> deleteLineNumber;
}

unsigned long long MemoryAllocation::getMemoryAddress() const {
	return this -> memoryAddress;
}

unsigned long long MemoryAllocation::getMemorySize() const {
	return this -> memorySize;
}

bool MemoryAllocation::isAllocated() const {
	return this -> bAllocated;
}

void MemoryAllocation::setAllocated( bool value ) {
	this -> bAllocated = value;
}
