#include "IO.h"







size_t IO::readToBuffer( std::fstream * fileStream, char ** buffer ) {
	fileStream -> seekg( 0, fileStream -> end );
	size_t length = fileStream -> tellg();
	fileStream -> seekg( 0, fileStream -> beg );

	if ( length ) {
		*buffer = new char[length];
		fileStream -> read( *buffer, length );
	} else {
		*buffer = NULL;
	}
		
	
	return length;
}

size_t IO::readToBuffer( const String & fileName, char ** data ) {
	std::fstream file( fileName.getData(), std::ios::in | std::ios::binary );
	if ( file.is_open() ) {
		size_t nbChars = readToBuffer( &file, data );
		file.close();
		return nbChars;
	}
	return -1;
}



