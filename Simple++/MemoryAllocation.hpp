
MemoryAllocation::MemoryAllocation(void){
}

MemoryAllocation::MemoryAllocation( unsigned long memoryAddress, unsigned long memorySize, const String & allocationFileName, unsigned int lineNumber ){
	this -> memoryAddress = memoryAddress;
	this -> memorySize = memorySize;
	this -> allocationFileName = allocationFileName;
	this -> allocationLineNumber = lineNumber;
	this -> bAllocated = true;
}


MemoryAllocation::~MemoryAllocation(void){
}

void MemoryAllocation::setAllocationFileName( const String & fileName ){
	this -> allocationFileName = fileName;
}

void MemoryAllocation::setAllocationLineNumber( int lineNumber ){
	this -> allocationFileName = lineNumber;
}

void MemoryAllocation::setDeleteFileName( const String & fileName ){
	this -> deleteFileName = fileName;
}

void MemoryAllocation::setDeleteLineNumber( int lineNumber ){
	this -> deleteLineNumber = lineNumber;
}

void MemoryAllocation::setMemoryAddress( unsigned long long address ){
	this -> memoryAddress = address;
}

void MemoryAllocation::setMemorySize( unsigned long long size ){
	this -> memorySize = size;
}

const String & MemoryAllocation::getAllocationFileName() const{
	return this -> allocationFileName;
}

int MemoryAllocation::getAllocationLineNumber() const{
	return this -> allocationLineNumber;
}

const String & MemoryAllocation::getDeleteFileName() const{
	return this -> deleteFileName;
}

int MemoryAllocation::getDeleteLineNumber() const{
	return this -> deleteLineNumber;
}

unsigned long long MemoryAllocation::getMemoryAddress() const{
	return this -> memoryAddress;
}

unsigned long long MemoryAllocation::getMemorySize() const{
	return this -> memorySize;
}

bool MemoryAllocation::isAllocated() const{
	return this -> bAllocated;
}

void MemoryAllocation::setAllocated( bool value ){
	this -> bAllocated = value;
}
