#pragma once

#include "IO/IO.h"

template<typename I, typename V>
class ParamT : public IO::BasicIO {
public:
	///@brief Empty constructor
	ParamT();

	///@brief Constructor from a name only.
	///@param name Name of this param.
	ParamT(const I& name);

	///brief Constructor from a name and a value
	///@param name Name of this param
	///@param value Value of this param
	ParamT(const I& name, const V& value);

	///@brief Copy Constructor
	///@param param Object to copy
	ParamT(const ParamT<I, V>& param);

	///@brief Move Constructor
	///@param param Object to move
	ParamT(const ParamT<I, V>&& param);

	///@brief Move operator
	///@param param Object to be copied
	///@return reference to THIS
	ParamT<I, V>& operator=(const ParamT<I, V>& param);

	///@brief Move operator
	///@param param Object to be copied
	///@return reference to THIS
	ParamT<I, V>& operator=(const ParamT<I, V>&& param);

	///@brief Less compare operator.
	///@param param Param to be compare.
	///@return True if this is less then param, False otherwise.
	bool operator<(const ParamT<I, V>& param) const;

	///@brief Set the name of this param
	///@param name Name of this param
	void setName(const I& name);

	///@brief Set the value of this param
	///@param value Value of this param
	void setValue(const V& value);

	///@brief get the name of this param
	///@return Name of the param
	const I& getName() const;

	///@brief get the value of this param
	///@return value of the param
	const V& getValue() const;

	///@brief read from a file stream
	///@param stream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool read(Stream* stream);

	///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
	///@param stream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool write(Stream* stream) const;

protected:
	I name;
	V value;
};

using Param = ParamT<StringASCII, StringASCII>;

#include "Param.hpp"