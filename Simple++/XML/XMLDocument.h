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

		///@brief Constructor from a buffer
		///@param str String buffer to be parsed
		Document( const UTF8String & str );

		///@brief Constructor from an XML file
		///@param fileName File to be opened and parsed
		Document( const WString & fileName );


		///@brief Destructor
		~Document();

		///@brief Copy Constructor
		///@param document Document to be copied
		Document( const Document & document );

		///@brief Move Constructor
		///@param document Document to be moved
		Document( Document && document );


		///@brief Copy operator
		///@param document Document to be copied
		///@return Reference to THIS
		Document & operator=( const Document & document );

		///@brief Move operator
		///@param document Document to be moved
		///@return Reference to THIS
		Document & operator=( Document && document );

		///@brief Write this object as an XML file
		///@param fileName Where to write
		///@return True if success, False otherwise
		bool writeXML( const WString & fileName ) const;

		///@brief Write this object as an XML file
		///@param fileStream Where to write
		///@return True if success, False otherwise
		bool writeXML( std::fstream * fileStream ) const;

		///@brief Write this object as an XML file
		///@param fileName Where to write
		///@return True if success, False otherwise
		bool readXML( const WString & fileName );

		///@brief read from a file stream ( Data has to be wrote by write() )
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

	private:
		void _parse( const UTF8String & str );
		bool _parseParameter( const UTF8String & str, RandomAccessIterator<char> * it, UCodePoint * lastCodePoint, Node * node );
		bool _parseParameterSpecial( const UTF8String & str, RandomAccessIterator<char> * it, UCodePoint * lastCodePoint, UTF8String * name, UTF8String * value );

		void _clear();
		void _unload();
		bool _readXML( const WString & fileName );

		float version;
		String encoding;

		Node * rootNode;
	};

	

}


