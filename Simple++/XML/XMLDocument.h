///@file XMLDocument.h
///@brief File containing the XMLDocument Class, used to parse XML files
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "Node.h"


namespace XML {

	template<typename T>
	class DocumentT : public BasicIO {
	public:
		///@brief Empty constructor
		DocumentT();

		///@brief Constructor from a buffer
		///@param str StringASCII buffer to be parsed
		DocumentT( const T & str );

		///@brief Constructor from an XML file
		///@param fileName File to be opened and parsed
		DocumentT( const WString & fileName );

		///@brief Destructor
		~DocumentT();

		///@brief Copy Constructor
		///@param document DocumentT<T> to be copied
		DocumentT( const DocumentT<T> & document );

		///@brief Move Constructor
		///@param document DocumentT<T> to be moved
		DocumentT( DocumentT<T> && document );

		///@brief Copy operator
		///@param document DocumentT<T> to be copied
		///@return Reference to THIS
		DocumentT<T> & operator=( const DocumentT<T> & document );

		///@brief Move operator
		///@param document DocumentT<T> to be moved
		///@return Reference to THIS
		DocumentT<T> & operator=( DocumentT<T> && document );


		///@brief Get a vector filled by pointer to all the node corresponding to the id searched in this sub tree.
		///@param id Id to look for
		///@return Vector of NodeT<T>'s pointers with the searched id
		Vector< NodeT<T> * > getElementsById( const T & id ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<T>'s pointers with the searched name
		Vector< NodeT<T> * > getElementsByName( const T & name ) const;

		///@brief Get the root node of this document
		///@return Pointer to the root document node (will never be NULL)
		NodeT<T> * getRoot();

		///@brief Get the version of this document
		///@return Version
		float getVersion() const;

		///@brief Set the version of this document
		///@param version new version to be set
		void setVersion( float version );

		///@brief Get the encoding of this document
		///@return Encoding of this document
		const StringASCII & getEncoding() const;

		///@brief Set the encoding of this document
		///@param encoding Encoding to be set
		void setEncoding( const T & encoding );

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

		///@brief Create an human-readable string of this param.
		///@return Human-readable string of this param.
		template<typename C = T>
		C toString() const;

		///@brief Create an human-readable string of this document.
		///@return Human-readable string of this document.
		T toStringDebug() const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o ) const;

	private:
		void _parse( const T & str );
		bool _parseParameter( const T & str, RandomAccessIterator<char> * it, UCodePoint * lastCodePoint, NodeT<T> * node );
		bool _parseParameterSpecial( const T & str, RandomAccessIterator<char> * it, UCodePoint * lastCodePoint, T * name, T * value );

		void _clear();
		void _unload();
		bool _readXML( const WString & fileName );

		float version;
		StringASCII encoding;

		NodeT<T> * rootNode;
	};

	using Document = DocumentT<UTF8String>;

	

}

#include "XMLDocument.hpp"


