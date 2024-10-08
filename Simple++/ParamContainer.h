#pragma once

#include "Vector.h"
#include "Map.h"
#include "Param.h"

template<typename I, typename V>
class ParamContainerT : public IO::BasicIO {
public:
	ParamContainerT();
	ParamContainerT( const ParamContainerT<I, V>& paramContainer );
	ParamContainerT( const ParamContainerT<I, V>&& paramContainer );

	~ParamContainerT();

	ParamContainerT<I, V>& operator=( const ParamContainerT<I, V>& paramContainer );
	ParamContainerT<I, V>& operator=( const ParamContainerT<I, V>&& paramContainer );

	ParamT<I, V>* setParam( const I& paramName, const V& paramValue );
	void setParams( const Vector<ParamT<I, V>>& paramVector );
	void setParams( const Vector<ParamT<I, V>*>& paramVector );

	bool removeParam( const I& paramName );

	void clearParams();

	const ParamT<I, V>* getParam( const I& paramName ) const;
	ParamT<I, V>* getParam( const I& paramName );

	const Vector<ParamT<I, V>*>& getParamVector() const;
	const Map<I, ParamT<I, V>*>& getParamMap() const;

	///@brief read from a file stream
	///@param stream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool read( Stream * stream, int verbose = 0 );

	///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
	///@param stream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool write( Stream* stream ) const;

protected:
	void copyParamVector( const Vector<ParamT<I, V>*>& paramVector );
	void addParam( ParamT<I, V>* newParam );

	Vector<ParamT<I, V>*> paramVector;
	Map<I, ParamT<I, V>*> paramMap;
};

using ParamContainer = ParamContainerT<StringASCII, StringASCII>;

#include "ParamContainer.hpp"