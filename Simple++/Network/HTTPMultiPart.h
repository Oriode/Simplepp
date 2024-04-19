#pragma once

#include "../Vector.h"
#include "../String.h"
#include "HTTPQuery.h"


namespace Network {

	template<typename T>
	class HTTPMultiPartFileT {
	public:
		HTTPMultiPartFileT();
		HTTPMultiPartFileT( const StringASCII& name, const StringASCII& fileName, const char* data = NULL, Size dataSize = 0 );

		void setData( const char* data, Size dataSize );

		void setName( const StringASCII& name );
		void setFileName( const StringASCII& fileName );

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parse( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		StringASCII format() const;
		void format( StringASCII* outputStr ) const;

	private:
		StringASCII name;
		StringASCII fileName;

		const char* data{ NULL };
		Size dataSize{ 0 };
	};


	template<typename T>
	class HTTPMultiPartT {
	public:

		void addFile(const StringASCII & name, const StringASCII & fileName, const char * data, Size dataSize );

		StringASCII format() const;
		void format( StringASCII* outputStr ) const;

		template<typename S = StringASCII>
		S toString() const;

	private:
		Vector<HTTPMultiPartFileT<T>> multiPartVector;

	};

	using HTTPMultiPart = HTTPMultiPartT<int>;

	template<typename T>
	inline HTTPMultiPartFileT<T>::HTTPMultiPartFileT() { }

	template<typename T>
	inline HTTPMultiPartFileT<T>::HTTPMultiPartFileT( const StringASCII& name, const StringASCII& fileName, const char* data, Size dataSize ) :
		name( name ),
		fileName( fileName ),
		data( data ),
		dataSize( dataSize ) { }

	template<typename T>
	inline void HTTPMultiPartFileT<T>::setData( const char* data, Size dataSize ) {
		this->data = data;
		this->dataSize = dataSize;
	}

	template<typename T>
	inline void HTTPMultiPartFileT<T>::setName( const StringASCII& name ) {
		this->name = name;
	}

	template<typename T>
	inline void HTTPMultiPartFileT<T>::setFileName( const StringASCII& fileName ) {
		this->fileName = fileName;
	}

	template<typename T>
	inline StringASCII HTTPMultiPartFileT<T>::format() const {
		StringASCII outString;
		format( &outString );
		return outString;
	}

	template<typename T>
	inline void HTTPMultiPartFileT<T>::format( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		static StringASCII referenceStr( "Content-Disposition: form-data; name=\"%\"; filename=\"%\"" );
		
		str << StringASCII::format( referenceStr, this->name, this->fileName );

		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );
		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );

		str.concat( this->data, this->dataSize );

		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );
	}



	template<typename T>
	template<typename EndFunc>
	inline bool HTTPMultiPartFileT<T>::parse( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
		return false;
	}

	template<typename T>
	inline void HTTPMultiPartT<T>::addFile( const StringASCII& name, const StringASCII& fileName, const char* data, Size dataSize ) {
		
		HTTPMultiPartFileT<T> newMultiPart( name, fileName, data, dataSize );

		this->multiPartVector.push( newMultiPart );
	}

	template<typename T>
	inline StringASCII HTTPMultiPartT<T>::format() const {
		StringASCII outString;
		format( &outString );
		return outString;
	}

	template<typename T>
	inline void HTTPMultiPartT<T>::format( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		static StringASCII boundary( "boundary" );

		for ( Size i( 0 ); i < this->multiPartVector.getSize(); i++ ) {
			const HTTPMultiPartFileT<T>& multiPart( this->multiPartVector.getValueI( i ) );

			str << StringASCII::ElemType( '-' );
			str << StringASCII::ElemType( '-' );
			str << boundary;
			str << StringASCII::ElemType( '\r' );
			str << StringASCII::ElemType( '\n' );

			multiPart.format( &str );
		}

		str << StringASCII::ElemType( '-' );
		str << StringASCII::ElemType( '-' );
		str << boundary;
		str << StringASCII::ElemType( '-' );
		str << StringASCII::ElemType( '-' );
	}

	template<typename T>
	template<typename S>
	inline S HTTPMultiPartT<T>::toString() const {
		return format();
	}

}
