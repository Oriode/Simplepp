///@file XMLDocument.h
///@brief File containing the XMLDocument Class, used to parse XML files
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "Node.h"


namespace XML {

	template<typename S>
	class DocumentT : public IO::BasicIO {
	public:
		///@brief Empty constructor
		DocumentT();

		///@brief Constructor from a buffer
		///@param str StringASCII buffer to be parsed
		DocumentT( const S & str );

		///@brief Constructor from an XML file
		///@param filePath File to be opened and parsed
		DocumentT( const OS::Path & filePath );

		///@brief Destructor
		~DocumentT();

		///@brief Copy Constructor
		///@param document DocumentT<S> to be copied
		DocumentT( const DocumentT<S> & document );

		///@brief Move Constructor
		///@param document DocumentT<S> to be moved
		DocumentT( DocumentT<S> && document );

		///@brief Copy operator
		///@param document DocumentT<S> to be copied
		///@return Reference to THIS
		DocumentT<S> & operator=( const DocumentT<S> & document );

		///@brief Move operator
		///@param document DocumentT<S> to be moved
		///@return Reference to THIS
		DocumentT<S> & operator=( DocumentT<S> && document );


		///@brief Get a vector filled by pointer to all the node corresponding to the id searched in this sub tree.
		///@param id Id to look for
		///@return Vector of NodeT<S>'s pointers with the searched id
		Vector< NodeT<S> * > getElementsById( const S & id ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<S>'s pointers with the searched name
		Vector< NodeT<S> * > getElementsByName( const S & name ) const;

		///@brief Get the root node of this document
		///@return Pointer to the root document node (will never be NULL)
		NodeT<S> * getRoot();

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
		void setEncoding( const S & encoding );

		///@brief Write this object as an XML file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool writeFileXML( const OS::Path & filePath ) const;

		///@brief Write this object as an XML file
		///@param stream Where to write
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeXML( Stream * stream ) const;

		///@brief Read this object as an XML file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool readFileXML( const OS::Path & filePath );

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readXML( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readXML( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readXML( const S & str );

		///@brief read from a file stream ( Data has to be wrote by write() )
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;

		///@brief Create an human-readable string of this param.
		///@return Human-readable string of this param.
		template<typename S2 = S>
		S2 toString() const;

		///@brief Create an human-readable string of this document.
		///@return Human-readable string of this document.
		S toStringDebug() const;

		///@brief Write this object to an Object that support opperator '<<'.
		///@param o Object to write to.
		template<typename C = S, typename Elem = C::ElemType>
		void _writeXML( C & o ) const;

	private:
		
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool _parseParameterSpecial( const C ** buffer, S * name, S * value, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		void _clear();
		void _unload();
		bool _readFileXML( const OS::Path & filePath );

		template<typename C>
		static bool cmpStr( const C * b1, const C * b2, int size );

		float version;
		StringASCII encoding;

		NodeT<S> * rootNode;
	};

	using Document = DocumentT<UTF8String>;

	

}

#include "XMLDocument.hpp"


