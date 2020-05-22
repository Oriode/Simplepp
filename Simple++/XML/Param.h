#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Math/Math.h"

namespace XML {

	template<typename T>
	class ParamT : public BasicIO {
	public:
		///@brief Empty constructor
		ParamT();

		///brief Constructor from a name and a value
		///@param name Name of this param
		///@param value Value of this param
		ParamT( const UTF8String & name, const UTF8String & value );

		///@brief Copy Constructor
		///@param param Object to copy
		ParamT( const ParamT<T> & param );

		///@brief Move Constructor
		///@param param Object to move
		ParamT( ParamT<T> && param );

		///@brief Convert to StringASCII operator
		///@return StringASCII generated
		operator UTF8String() const;

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		ParamT<T> & operator=( const ParamT<T> & param );

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		ParamT<T> & operator=( ParamT<T> && param );

		///@brief get the name of this param
		///@return Name of the param
		const UTF8String & getName() const;

		///@brief Set the name of this param (Warning: Changing this param name to "id" will not change the id of the node associated, @see Node::setId())
		///@param name Name of this param
		void setName( const UTF8String & name );

		///@brief get the value of this param 
		///@return value of the param
		const UTF8String & getValue() const;

		///@brief Set the value of this param (Warning: Changing this param value if name is "id" will not change the id of the node associated, @see Node::setId())
		///@param value Value of this param
		void setValue( const UTF8String & value );

		///@brief Write this object in the XML syntax into the fileStream
		///@param fileStream stream used to write this object
		///@return True if success, False otherwise
		bool writeXML( std::fstream * fileStream ) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

		///@brief Create an human-readable string of this param.
		///@return Human-readable string of this param.
		template<typename C = T>
		C toString() const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o ) const;
	private:
		void _clear();
		

		UTF8String name;
		UTF8String value;
	};

}

#include "Param.hpp"