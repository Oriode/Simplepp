///@file XMLDocument.h
///@brief File containing the XMLDocument Class, used to parse XML files
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "Node.h"


namespace XML {

	class Document : public BasicIO {
	public:

		///@brief 
		Document( const UTF8String & str );


		///@brief Destructor
		~Document();

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

	private:
		void _parse( const UTF8String & str );
		bool _parseParameter( const UTF8String & str, RandomAccessIterator<char> * it, UCodePoint * lastCodePoint, UTF8String * name, UTF8String * value );
		void _clear();
		void _unload();

		float version;
		String encoding;
		Vector<Node *> nodes;

	};

	

}


