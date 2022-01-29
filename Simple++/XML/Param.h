#pragma once

#include "../IO/IO.h"
#include "../Math/Math.h"
#include "../Param.h"

namespace XML {

	template<typename T>
	class ParamT : public ::ParamT<T, T> {
	public:
		///@brief Empty constructor
		ParamT();

		///brief Constructor from a name and a value
		///@param name Name of this param
		///@param value Value of this param
		ParamT( const T & name, const T & value );

		///@brief Copy Constructor
		///@param param Object to copy
		ParamT( const ParamT<T> & param );

		///@brief Move Constructor
		///@param param Object to move
		ParamT( ParamT<T> && param );

		///@brief Convert to StringASCII operator
		///@return StringASCII generated
		operator T() const;

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
		using ::ParamT<T, T>::getName;

		///@brief Set the name of this param (Warning: Changing this param name to "id" will not change the id of the node associated, @see Node::setId())
		///@param name Name of this param
		using ::ParamT<T, T>::setName;

		///@brief get the value of this param 
		///@return value of the param
		using ::ParamT<T, T>::getValue;

		///@brief Set the value of this param (Warning: Changing this param value if name is "id" will not change the id of the node associated, @see Node::setId())
		///@param value Value of this param
		using ::ParamT<T, T>::setValue;

		///@brief Write this object in the XML syntax into the fileStream
		///@param fileStream stream used to write this object
		///@return True if success, False otherwise
		bool writeXML( IO::SimpleFileStream * fileStream ) const;

		///@brief Create an human-readable string of this param.
		///@return Human-readable string of this param.
		template<typename C = T>
		C toString() const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o ) const;
	private:
		void _clear();
	};

}

#include "Param.hpp"