
template<typename C>
bool IO::write( const WString & fileName, const C * object ) {
	std::fstream fileStream( fileName.getData(), std::ios::out | std::ios::binary );
	if ( fileStream.is_open() ) {
		bool result( IO::write( &fileStream, object ) );
		fileStream.close();
		return result;
	} else
		return false;
}


template<typename C>
bool IO::read( const WString & fileName, C * object ) {
	std::fstream fileStream( fileName.getData(), std::ios::in | std::ios::binary );
	if ( fileStream.is_open() ) {
		bool result( IO::read( &fileStream, object ) );
		fileStream.close();
		return result;
	} else
		return false;
}
