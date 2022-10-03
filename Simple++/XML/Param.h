#pragma once

#include "../IO/IO.h"
#include "../Math/Math.h"
#include "../Param.h"

namespace XML {

	template<typename S>
	class ParamT : public ::ParamT<S, S> {
	public:
		///@brief Empty constructor
		ParamT();

		///brief Constructor from a name and a value
		///@param name Name of this param
		///@param value Value of this param
		ParamT( const S & name, const S & value );

		///@brief Copy Constructor
		///@param param Object to copy
		ParamT( const ParamT<S> & param );

		///@brief Move Constructor
		///@param param Object to move
		ParamT( ParamT<S> && param );

		///@brief Convert to StringASCII operator
		///@return StringASCII generated
		operator S() const;

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		ParamT<S> & operator=( const ParamT<S> & param );

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		ParamT<S> & operator=( ParamT<S> && param );

		///@brief get the name of this param
		///@return Name of the param
		using ::ParamT<S, S>::getName;

		///@brief Set the name of this param (Warning: Changing this param name to "id" will not change the id of the node associated, @see Node::setId())
		///@param name Name of this param
		using ::ParamT<S, S>::setName;

		///@brief get the value of this param 
		///@return value of the param
		using ::ParamT<S, S>::getValue;

		///@brief Set the value of this param (Warning: Changing this param value if name is "id" will not change the id of the node associated, @see Node::setId())
		///@param value Value of this param
		using ::ParamT<S, S>::setValue;

		///@brief Write this object in the XML syntax into the stream
		///@param stream stream used to write this object
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeXML( Stream * stream ) const;

		///@brief Create an human-readable string of this param.
		///@return Human-readable string of this param.
		template<typename S2 = S>
		S2 toString() const;

		template<typename C = S, typename Elem = C::ElemType>
		void _writeXML( C & o ) const;
	private:
		void _clear();
	};

}

#include "Param.hpp"