#pragma once

#include "../Vector.h"
#include "../Map.h"
#include "../IO/IO.h"
#include "TLSConnection.h"

namespace Network {

	template<typename I, typename V>
	class ParamT : public IO::BasicIO {
	public:
		///@brief Empty constructor
		ParamT();

		///@brief Constructor from a name only.
		///@param name Name of this param.
		ParamT(const I & name);

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
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(IO::SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(IO::SimpleFileStream* fileStream) const;

	protected:
		I name;
		V value;
	};

	using Param = ParamT<StringASCII, StringASCII>;

	template<typename I, typename V>
	class ParamContainerT : public IO::BasicIO {
	public:
		ParamContainerT();
		ParamContainerT(const ParamContainerT<I, V>& paramContainer);
		ParamContainerT(const ParamContainerT<I, V>&& paramContainer);

		~ParamContainerT();

		ParamContainerT<I, V>& operator=(const ParamContainerT<I, V>& paramContainer);
		ParamContainerT<I, V>& operator=(const ParamContainerT<I, V>&& paramContainer);

		ParamT<I, V>* setParam(const I& paramName, const V& paramValue);
		void setParams(const Vector<ParamT<I, V>>& paramVector);

		const ParamT<I, V>* getParam(const I& paramName) const;
		ParamT<I, V>* getParam(const I& paramName);

		const Vector<ParamT<I, V>*>& getParamVector() const;
		const Map<I, ParamT<I, V>*>& getParamMap() const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(IO::SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(IO::SimpleFileStream* fileStream) const;

	protected:
		void copyParamVector(const Vector<ParamT<I, V>*>& paramVector);
		void addParam(ParamT<I, V>* newParam);

		Vector<ParamT<I, V>*> paramVector;
		Map<I, ParamT<I, V>*> paramMap;
	};

	using ParamContainer = ParamContainerT<StringASCII, StringASCII>;

	using HTTPParam = ParamT<StringASCII, StringASCII>;

	template<typename T>
	class HTTPEndPointT : public ParamContainerT<StringASCII, StringASCII> {
	public:
		enum class Type : unsigned char {
			HTTP,
			HTTPS,
			Unknown
		};

		HTTPEndPointT();
		HTTPEndPointT(typename HTTPEndPointT<T>::Type type, const StringASCII & hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector);

		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPEndPointT(const StringASCII::ElemType ** itP, const EndFunc & endFunc = StringASCII::IS_END_SENTINEL);

		HTTPEndPointT(const HTTPEndPointT<T>& endPoint);

		~HTTPEndPointT();

		HTTPEndPointT<T>& operator=(const HTTPEndPointT<T>& endPoint);
		HTTPEndPointT<T>& operator=(const HTTPEndPointT<T>&& endPoint);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parse(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII format() const;
		void format(StringASCII* outputStr) const;

		void setType(const typename HTTPEndPointT<T>::Type type);
		void setHostname(const StringASCII& hostname);
		void setEndPoint(const StringASCII& endPoint);

		typename HTTPEndPointT<T>::Type getType() const;
		const StringASCII& getHostname() const;
		const StringASCII& getEndPoint() const;

		static const StringASCII& getTypeString(typename HTTPEndPointT<T>::Type type);
		static typename HTTPEndPointT<T>::Type getType(const StringASCII& typeStr);

	private:
		Type type;
		StringASCII hostname;
		StringASCII endPointStr;

	};

	using HTTPEndPoint = HTTPEndPointT<int>;

	template<typename T>
	class HTTPQueryT : protected ParamContainerT<StringASCII, StringASCII> {
	public:
		HTTPQueryT();

		~HTTPQueryT();

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		const HTTPParam* getHeaderParam(const StringASCII& paramName) const;
		HTTPParam* getHeaderParam(const StringASCII& paramName);

		void setProtocol(const StringASCII& protocol);
		void setContent(const StringASCII& content);

		const StringASCII& getProtocol() const;
		const StringASCII& getContent() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQuery(StringASCII* outputStr) const;

		StringASCII protocolStr;

	private:
		///@brief Format the query header using the specified params.
		void formatQueryHeader();

		///@brief Parse the query String and update the header params Vector.
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryHeader(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		bool bHeaderNeedFormat;

		StringASCII headerStr;
		StringASCII contentStr;
	};

	using HTTPQuery = HTTPQueryT<int>;

	template<typename T>
	class HTTPResponseT : public HTTPQueryT<T> {
	public:
		HTTPResponseT();
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPResponseT(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr) const;

		void setStatusCode(Size statusCode);
		void setStatusMessage(const StringASCII& statusMessage);

		const Size getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		Size statusCode;
		StringASCII statusMessage;

	private:
	};

	using HTTPResponse = HTTPResponseT<int>;

	template<typename T>
	class HTTPRequestT : public HTTPQueryT<T> {
	public:
		HTTPRequestT();
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPRequestT(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr) const;

		void setMethod(const StringASCII& method);
		void setEndPoint(const HTTPEndPointT<T>& endPoint);
		void setEndPoint(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector);
		bool setEndPoint(const StringASCII& endPoint);

		const StringASCII& getMethod() const;
		const HTTPEndPointT<T> & getEndPoint() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		StringASCII methodStr;
		HTTPEndPointT<T> endPoint;
	};

	template<typename T>
	class HTTPClientT {
	public:
		HTTPClientT();

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		HTTPResponseT<T> * query(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<Param>& urlParams);

	private:
		HTTPRequestT<T> request;
		HTTPResponseT<T> response;
	};

	using HTTPClient = HTTPClientT<int>;

	template<typename I, typename V>
	ParamT<I, V>::ParamT() {

	}

	template<typename I, typename V>
	inline ParamT<I, V>::ParamT(const I& name) :
		name(name)
	{}

	template<typename I, typename V>
	inline ParamT<I, V>::ParamT(const I & name, const V & value) :
		name(name),
		value(value)
	{}

	template<typename I, typename V>
	inline ParamT<I, V>::ParamT(const ParamT<I, V>&param) :
		name(param.name),
		value(param.value)
	{}

	template<typename I, typename V>
	ParamT<I, V>::ParamT(const ParamT<I, V>&& param) :
		name(Utility::toRValue(param.name)),
		value(Utility::toRValue(param.value))
	{

	}

	template<typename I, typename V>
	ParamT<I, V>& ParamT<I, V>::operator=(const ParamT<I, V>& param) {
		this->name = param.name;
		this->value = param.value;

		return *this;
	}

	template<typename I, typename V>
	ParamT<I, V>& ParamT<I, V>::operator=(const ParamT<I, V>&& param) {
		this->name = Utility::toRValue(param.name);
		this->value = Utility::toRValue(param.value);

		return *this;
	}

	template<typename I, typename V>
	inline bool ParamT<I, V>::operator<(const ParamT<I, V>&param) const {
		return this->name < param.name;
	}

	template<typename I, typename V>
	inline void ParamT<I, V>::setValue(const V & value) {
		this->value = value;
	}

	template<typename I, typename V>
	inline const I& ParamT<I, V>::getName() const {
		return this->name;
	}

	template<typename I, typename V>
	inline const V& ParamT<I, V>::getValue() const {
		return this->value;
	}

	template<typename I, typename V>
	bool ParamT<I, V>::read(IO::SimpleFileStream* fileStream) {
		if ( !IO::read(fileStream, &this -> name) ) {
			return false;
		}
		if ( !IO::read(fileStream, &this -> value) ) {
			return false;
		}
		return true;
	}

	template<typename I, typename V>
	bool ParamT<I, V>::write(IO::SimpleFileStream* fileStream) const {
		if ( !IO::write(fileStream, &this -> name) )
			return false;
		if ( !IO::write(fileStream, &this -> value) )
			return false;
		return true;
	}

	template<typename T>
	inline HTTPQueryT<T>::HTTPQueryT() :
		bHeaderNeedFormat(false)
	{}

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {
		
	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		this->bHeaderNeedFormat = true;
		return ParamContainerT<StringASCII, StringASCII>::setParam(paramName, paramValue);
	}

	template<typename T>
	inline const HTTPParam* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) const {
		return ParamContainerT<StringASCII, StringASCII>::getParam(paramName);
	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) {
		return ParamContainerT<StringASCII, StringASCII>::getParam(paramName);
	}

	template<typename T>
	inline void HTTPQueryT<T>::setProtocol(const StringASCII& protocol) {
		this->protocolStr = protocol;
	}

	template<typename T>
	inline void HTTPQueryT<T>::setContent(const StringASCII& content) {
		this->contentStr = content;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getProtocol() const {
		return this->protocolStr;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getContent() const {
		return this->contentStr;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		if ( !parseQueryHeader(itP, endFunc) ) {
			return false;
		}

		const StringASCII::ElemType *& it(*itP);
		for ( ; ( *it == StringASCII::ElemType('\n') || *it == StringASCII::ElemType('\r') ) && !endFunc(it); it++ );

		const StringASCII::ElemType * contentStrBeginIt(it);
		for ( ; !endFunc(it); it++ );
		this->contentStr = StringASCII(contentStrBeginIt, Size(it - contentStrBeginIt));

		return true;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQuery(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		const_cast<HTTPQueryT<T> *>(this)->formatQueryHeader();

		str << this->headerStr;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
		str << this->contentStr;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryHeader() {
		if ( this->bHeaderNeedFormat ) {

			this->headerStr.clear();

			for ( typename Vector<HTTPParam*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
				const HTTPParam* param(this->paramVector.getValueIt(it));

				this->headerStr << param->getName();
				this->headerStr << StringASCII::ElemType(':');
				this->headerStr << StringASCII::ElemType(' ');
				this->headerStr << param->getValue();
				this->headerStr << StringASCII::ElemType('\r');
				this->headerStr << StringASCII::ElemType('\n');
			}

			this->bHeaderNeedFormat = false;
		}
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQueryHeader(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorParamName(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType(':') || * it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorParamName functorParamName(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType *& it(*itP);
		while ( true ) {
			// Skip spaces.
			for ( ; !functorSpace(it); it++ );

			const StringASCII::ElemType * paramNameBeginIt(it);
			for ( ; !functorParamName(it); it++ );
			const StringASCII::ElemType * paramNameEndIt(it);

			if ( *it == StringASCII::ElemType(':') ) {
				it++;
			}

			// Skip spaces.
			for ( ; !functorSpace(it); it++ );

			const StringASCII::ElemType * paramValueBeginIt(it);
			for ( ; !functorNewLine(it); it++ );
			const StringASCII::ElemType * paramValueEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt || paramValueBeginIt == paramValueEndIt ) {
				error("HTTP header syntax error.");
				return false;
			}

			StringASCII newParamName(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));
			StringASCII newParamValue(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			HTTPParam* newParam(new HTTPParam(newParamName, newParamValue));

			this->paramVector.push(newParam);

			// End condition.
			if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
				it++;
				if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
					it++;
				}
				if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
					it++;
					if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
						it++;
					}
					break;
				}
				continue;
			}

			break;
		}

		return true;
	}

	template<typename T>
	inline HTTPResponseT<T>::HTTPResponseT() {}

	template<typename T>
	template<typename EndFunc>
	inline HTTPResponseT<T>::HTTPResponseT(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		if ( !parseQueryTitle(itP, endFunc) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery(itP, endFunc) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline StringASCII HTTPResponseT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		formatQuery(&outputStr);
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQuery(StringASCII* outputStr) const {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusCode(Size statusCode) {
		this->statusCode = statusCode;
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusMessage(const StringASCII& statusMessage) {
		this->statusMessage = statusMessage;
	}

	template<typename T>
	inline const Size HTTPResponseT<T>::getStatusCode() const {
		return this->statusCode;
	}

	template<typename T>
	inline const StringASCII& HTTPResponseT<T>::getStatusMessage() const {
		return this->statusMessage;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord(const EndFunc& endFunc) :
				endFunc(endFunc){}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorWord functorWord(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType * & it(*itP);
		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType * protocolStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType * protocolStrEndIt(it);

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		Size statusCode(StringASCII::toULongLong(&it, 10, functorWord));

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType * statusMessageBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType * statusMessageEndIt(it);

		// Skip up to end line.
		for ( ; !functorNewLine(it); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
			it++;
			if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
				it++;
			}
		}

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			error("HTTP response syntax error.");
			return false;
		}

		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));
		StringASCII statusMessage(statusMessageBeginIt, Size(statusMessageEndIt - statusMessageBeginIt));

		this->protocolStr = protocolStr;
		this->statusCode = statusCode;
		this->statusMessage = statusMessage;

		return true;
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQueryTitle(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->protocolStr;
		str << StringASCII::ElemType(' ');
		str << this->statusCode;
		str << StringASCII::ElemType(' ');
		str << this->statusMessage;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT() {}

	template<typename T>
	template<typename EndFunc>
	inline HTTPRequestT<T>::HTTPRequestT(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		if ( !parseQueryTitle(itP, endFunc) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery(itP, endFunc) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorWord functorWord(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType *& it(*itP);

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType * methodStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType * methodStrEndIt(it);

		if ( methodStrBeginIt == methodStrEndIt ) {
			error("HTTP request syntax error : no method.");
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		if ( !this->endPoint.parse(&it, functorWord) ) {
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType * protocolStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType * protocolStrEndIt(it);

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			error("HTTP request syntax error : no protocol.");
			return false;
		}

		// Skip up to end line.
		for ( ; !functorNewLine(it); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
			it++;
			if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
				it++;
			}
		}

		StringASCII methodStr(methodStrBeginIt, Size(methodStrEndIt - methodStrBeginIt));
		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));

		this->methodStr = methodStr;
		this->protocolStr = protocolStr;

		return true;
	}

	template<typename T>
	inline StringASCII HTTPRequestT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		formatQuery(&outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQuery(StringASCII* outputStr) const {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::setMethod(const StringASCII& method) {
		this->methodStr = method;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(const HTTPEndPointT<T>& endPoint) {
		this->endPoint = endPoint;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector) {
		this->endPoint.setType(type);
		this->endPoint.setHostname(hostname);
		this->endPoint.setEndPoint(endPointStr);
		this->endPoint.setParams(paramVector);
	}

	template<typename T>
	inline bool HTTPRequestT<T>::setEndPoint(const StringASCII& endPoint) {
		StringASCII::IsEndIterator endFunc(endPoint.getEnd());
		String::Iterator it(endPoint.getBegin());

		return this->endPoint.parse(&it, endFunc);
	}

	template<typename T>
	inline const StringASCII& HTTPRequestT<T>::getMethod() const {
		return this->methodStr;
	}

	template<typename T>
	inline const HTTPEndPointT<T>& HTTPRequestT<T>::getEndPoint() const {
		return this->endPoint;
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQueryTitle(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->methodStr;
		str << StringASCII::ElemType(' ');
		this->endPoint.format(&str);
		// str << this->endPoint.getEndPoint();
		str << StringASCII::ElemType(' ');
		str << this->protocolStr;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
	}

	template<typename T>
	inline HTTPEndPointT<T>::HTTPEndPointT() {}

	template<typename T>
	inline HTTPEndPointT<T>::HTTPEndPointT(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector) :
		type(type),
		hostname(hostname),
		endPointStr(endPointStr)
	{
		setParams(paramVector);
	}

	template<typename T>
	inline HTTPEndPointT<T>::HTTPEndPointT(const HTTPEndPointT<T>& endPoint) :
		type(endPoint.type),
		endPointStr(endPoint.endPointStr)
	{
		copyParamVector(endPoint.paramVector);
	}

	template<typename T>
	inline HTTPEndPointT<T>::~HTTPEndPointT() {
		
	}

	template<typename T>
	inline HTTPEndPointT<T>& HTTPEndPointT<T>::operator=(const HTTPEndPointT<T>& endPoint) {
		ParamContainerT<StringASCII, StringASCII>::operator=(endPoint);
		this->type = endPoint.type;
		this->endPointStr = endPoint.endPointStr;

		return *this;
	}

	template<typename T>
	inline HTTPEndPointT<T>& HTTPEndPointT<T>::operator=(const HTTPEndPointT<T>&& endPoint) {
		ParamContainerT<StringASCII, StringASCII>::operator=(Utility::toRValue(endPoint));
		this->type = Utility::toRValue(endPoint.type);
		this->endPointStr = Utility::toRValue(endPoint.endPointStr);

		return *this;
	}

	template<typename T>
	inline StringASCII HTTPEndPointT<T>::format() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		format(&outputStr);
	}

	template<typename T>
	inline void HTTPEndPointT<T>::format(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << getTypeString(this->type);
		str << StringASCII::ElemType(':');
		str << StringASCII::ElemType('/');
		str << StringASCII::ElemType('/');
		str << this->hostname;
		str << this->endPointStr;

		if ( this->paramVector.getSize() > Size(0) ) {
			str << StringASCII::ElemType('?');
			for ( typename Vector<HTTPParam*>::Iterator it(this->paramVector.getBegin()); it < this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
				const HTTPParam* param(this->paramVector.getValueIt(it));

				if ( it != this->paramVector.getBegin() ) {
					str << StringASCII::ElemType('&');
				}

				str << param->getName();
				if ( param->getValue().getSize() > Size(0) ) {
					str << StringASCII::ElemType('=');
					str << param->getValue();
				}
			}
		}
	}

	template<typename T>
	inline void HTTPEndPointT<T>::setType(const typename HTTPEndPointT<T>::Type type) {
		this->type = type;
	}

	template<typename T>
	inline void HTTPEndPointT<T>::setHostname(const StringASCII& hostname) {
		this->hostname = hostname;
	}

	template<typename T>
	inline void HTTPEndPointT<T>::setEndPoint(const StringASCII& endPoint) {
		this->endPointStr = endPoint;
	}

	template<typename T>
	inline typename HTTPEndPointT<T>::Type HTTPEndPointT<T>::getType() const {
		return this->type;
	}

	template<typename T>
	inline const StringASCII& HTTPEndPointT<T>::getHostname() const {
		return this->hostname;
	}

	template<typename T>
	inline const StringASCII& HTTPEndPointT<T>::getEndPoint() const {
		return this->endPointStr;
	}

	template<typename T>
	inline const StringASCII& HTTPEndPointT<T>::getTypeString(typename HTTPEndPointT<T>::Type type) {
		static const StringASCII typeStrTable[] = { StringASCII("http"), StringASCII("https") };
		unsigned char typeIndex(static_cast< unsigned char >( type ));
		if ( typeIndex < sizeof(typeStrTable) ) {
			return typeStrTable[ typeIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename HTTPEndPointT<T>::Type HTTPEndPointT<T>::getType(const StringASCII& typeStr) {
		switch ( typeStr ) {
			case getTypeString(Type::HTTP): {
				return Type::HTTP;
			}
			case getTypeString(Type::HTTPS): {
				return Type::HTTPS;
			}
			default:
				{
					return Type::Unknown;
				}
		}
	}

	template<typename T>
	template<typename EndFunc>
	inline HTTPEndPointT<T>::HTTPEndPointT(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		parse(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPEndPointT<T>::parse(const StringASCII::ElemType ** itP, const EndFunc& endFunc) {
		struct FunctorProtocol {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType(':') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorHostname {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('/') || *it == StringASCII::ElemType('?') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorEndPoint {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('?') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('=') || *it == StringASCII::ElemType('&') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamValue {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType * it) const { return *it == StringASCII::ElemType('&') || endFunc(it); }

			const EndFunc& endFunc;
		};

		FunctorProtocol functorProtocol(endFunc);
		FunctorHostname functorHostname(endFunc);
		FunctorEndPoint functorEndPoint(endFunc);
		FunctorParamName functorParamName(endFunc);
		FunctorParamValue functorParamValue(endFunc);

		const StringASCII::ElemType *& it(*itP);

		const StringASCII::ElemType * protocolStrBeginIt(it);
		for ( ; !functorProtocol(it); it++ );
		const StringASCII::ElemType * protocolStrEndIt(it);

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			error("EndPoint syntax error : no protocol.");
			return false;
		}

		if ( !endFunc(it) ) {
			StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));
			this->type = getType(protocolStr.toLower());

			if ( this->type == Type::Unknown ) {
				error("EndPoint syntax error : unknown protocol.");
				return false;
			}

			// Skip :
			it++;

			// Skip /
			for ( ; *it == StringASCII::ElemType('/') && !endFunc(it); it++ );
		} else {
			this->type = Type::Unknown;
			// No protocol founded, start over without searching any.
			it = *itP;
		}

		const StringASCII::ElemType * hostnameStrBeginIt(it);
		for ( ; !functorHostname(it); it++ );
		const StringASCII::ElemType * hostnameStrEndIt(it);

		const StringASCII::ElemType * endPointStrBeginIt(it);
		for ( ; !functorEndPoint(it); it++ );
		const StringASCII::ElemType * endPointStrEndIt(it);

		if ( endPointStrBeginIt == endPointStrEndIt ) {
			error("EndPoint syntax error : no end point.");
			return false;
		}

		StringASCII hostnameStr(hostnameStrBeginIt, Size(hostnameStrEndIt - hostnameStrBeginIt));
		StringASCII endPointStr(endPointStrBeginIt, Size(endPointStrEndIt - endPointStrBeginIt));

		this->hostname = hostnameStr;
		this->endPointStr = endPointStr;
		this->paramVector.clear();
		this->paramMap.clear();

		if ( endFunc(it) ) {
			return true;
		}

		// Skip ?
		it++;

		// Parse the params
		while ( true ) {
			const StringASCII::ElemType * paramNameBeginIt(it);
			for ( ; !functorParamName(it); it++ );
			const StringASCII::ElemType * paramNameEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt ) {
				error("EndPoint syntax error : param name missing.");
				return false;
			}

			StringASCII paramNameStr(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));

			if ( functorParamValue(it) ) {

				addParam(new HTTPParam(paramNameStr));

				if ( endFunc(it) ) {
					break;
				}

				if ( functorParamValue(it) ) {
					// Skip &
					it++;
					continue;
				}
			}

			// Skip =
			it++;

			const StringASCII::ElemType * paramValueBeginIt(it);
			for ( ; !functorParamValue(it); it++ );
			const StringASCII::ElemType * paramValueEndIt(it);

			StringASCII paramValueStr(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			addParam(new HTTPParam(paramNameStr, paramValueStr));

			if ( !endFunc(it) ) {
				break;
			}
		}

		return true;
	}

	template<typename T>
	inline HTTPClientT<T>::HTTPClientT() {
		this->request.setMethod(StringASCII("GET"));
		this->request.setProtocol(StringASCII("HTTP/1.1"));

		this->request.setHeaderParam(StringASCII("Accept"), StringASCII("*/*"));
		this->request.setHeaderParam(StringASCII("Connection"), StringASCII("close"));
	}

	template<typename T>
	inline HTTPParam* HTTPClientT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		return this->request.setHeaderParam(paramName, paramValue);
	}

	template<typename T>
	inline HTTPResponseT<T> * HTTPClientT<T>::query(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<Param>& urlParams) {
		this->request.setEndPoint(type, hostname, endPointStr, urlParams);

		static StringASCII sendBuffer;
		static char receiveBuffer[ 1000000 ];

		TLSConnectionT<T> connection;

		if ( type == HTTPEndPointT<T>::Type::HTTPS ) {
			if ( connection.connect(hostname, unsigned short(443), Network::SockType::TCP) ) {

				this->request.formatQuery(&sendBuffer);

				if ( !connection.send(sendBuffer.toCString(), int(sendBuffer.getSize())) ) {
					return NULL;
				}

				int totalReceivedLength(0);
				while ( true ) {
					int receivedLength(connection.receive(receiveBuffer + totalReceivedLength, sizeof(receiveBuffer) - totalReceivedLength));

					if ( receivedLength <= int(0) ) {
						break;
					}

					totalReceivedLength += receivedLength;
				}

				const StringASCII::ElemType * parseIt(receiveBuffer);
				StringASCII::IsEndIterator endFunc(receiveBuffer + totalReceivedLength);
				if ( !this->response.parseQuery(&parseIt, endFunc) ) {
					return NULL;
				}

				return &this->response;
			}
		}

		return NULL;
	}

	template<typename I, typename V>
	inline ParamContainerT<I, V>::ParamContainerT() {}

	template<typename I, typename V>
	inline ParamContainerT<I, V>::ParamContainerT(const ParamContainerT<I, V>& paramContainer) {
		copyParamVector(paramContainer.paramVector);
	}

	template<typename I, typename V>
	inline ParamContainerT<I, V>::ParamContainerT(const ParamContainerT<I, V>&& paramContainer) :
		paramVector(Utility::toRValue(paramContainer.paramVector)),
		paramMap(Utility::toRValue(paramContainer.paramMap))
	{
		
	}

	template<typename I, typename V>
	inline ParamContainerT<I, V>::~ParamContainerT() {
		for ( typename Vector<ParamT<I, V>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
			delete this->paramVector.getValueIt(it);
		}
	}

	template<typename I, typename V>
	inline ParamContainerT<I, V>& ParamContainerT<I, V>::operator=(const ParamContainerT<I, V>& paramContainer) {
		copyParamVector(paramContainer.paramVector);

		return *this;
	}

	template<typename I, typename V>
	inline ParamContainerT<I, V>& ParamContainerT<I, V>::operator=(const ParamContainerT<I, V>&& paramContainer) {
		this->paramVector = Utility::toRValue(endPoint.paramVector);
		this->paramMap = Utility::toRValue(endPoint.paramMap);

		return *this;
	}

	template<typename I, typename V>
	inline ParamT<I, V>* ParamContainerT<I, V>::setParam(const I& paramName, const V& paramValue) {
		ParamT<I, V>* param(getParam(paramName));

		if ( param ) {
			param->setValue(paramValue);
		} else {
			param = new ParamT<I, V>(paramName, paramValue);
			addParam(param);
		}

		return param;
	}

	template<typename I, typename V>
	inline void ParamContainerT<I, V>::setParams(const Vector<ParamT<I, V>>& paramVector) {
		this->paramVector.clear();
		this->paramMap.clear();
		for ( typename Vector<ParamT<I, V>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
			const ParamT<I, V>& param(paramVector.getValueIt(it));

			addParam(new ParamT<I, V>(param));
		}
	}

	template<typename I, typename V>
	inline const ParamT<I, V>* ParamContainerT<I, V>::getParam(const I& paramName) const {
		return const_cast< ParamContainerT<I, V> * >( this )->getParam(paramName);
	}

	template<typename I, typename V>
	inline ParamT<I, V>* ParamContainerT<I, V>::getParam(const I& paramName) {
		ParamT<I, V>** paramP(this->paramMap.getValueI(paramName));
		if ( paramP ) {
			return *paramP;
		}
		return NULL;
	}

	template<typename I, typename V>
	inline const Vector<ParamT<I, V>*>& ParamContainerT<I, V>::getParamVector() const {
		return this->paramVector;
	}

	template<typename I, typename V>
	inline const Map<I, ParamT<I, V>*>& ParamContainerT<I, V>::getParamMap() const {
		return this->paramMap;
	}

	template<typename I, typename V>
	inline bool ParamContainerT<I, V>::read(IO::SimpleFileStream* fileStream) {
		Size nbParams;

		if ( !IO::read(fileStream, &nbParams) ) {
			return false;
		}
		for ( Size i(0); i < nbParams; i++ ) {
			ParamT<I, V>* newParam(new ParamT<I, V>());

			if ( !IO::read(fileStream, newParam) ) {
				return false;
			}
		}

		return true;
	}

	template<typename I, typename V>
	inline bool ParamContainerT<I, V>::write(IO::SimpleFileStream* fileStream) const {
		const Size nbParams(this->paramVector.getSize());

		if ( !IO::write(fileStream, &nbParams) ) {
			return false;
		}
		for ( typename Vector<ParamT<I, V>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
			const ParamT<I, V>* param(this->paramVector.getValueIt(it));

			if ( !IO::write(fileStream, param) ) {
				return false;
			}
		}

		return true;
	}

	template<typename I, typename V>
	inline void ParamContainerT<I, V>::copyParamVector(const Vector<ParamT<I, V>*>& paramVector) {
		this->paramVector.clear();
		this->paramMap.clear();
		for ( typename Vector<ParamT<I, V>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
			const ParamT<I, V>* param(paramVector.getValueIt(it));

			addParam(new ParamT<I, V>(*param));
		}
	}

	template<typename I, typename V>
	inline void ParamContainerT<I, V>::addParam(ParamT<I, V>* newParam) {
		this->paramVector.push(newParam);
		this->paramMap.insert(newParam->getName(), newParam);
	}

}

#include "HTTPClient.hpp"