#pragma once

#include "../Vector.h"
#include "TLSConnection.h"

namespace Network {

	template<typename T>
	class HTTPParamT {
	public:
		HTTPParamT(const StringASCII & name);
		HTTPParamT(const StringASCII& name, const StringASCII& value);

		HTTPParamT(const HTTPParamT<T>& param);

		void setValue(const StringASCII& value);

		const StringASCII& getName() const;
		const StringASCII& getValue() const;

	private:
		StringASCII name;
		StringASCII value;
	};

	using HTTPParam = HTTPParamT<int>;

	template<typename T>
	class HTTPEndPointT {
	public:
		enum class Type : unsigned char {
			HTTP,
			HTTPS,
			Unknown
		};

		HTTPEndPointT();
		HTTPEndPointT(typename HTTPEndPointT<T>::Type type, const StringASCII & hostname, const StringASCII& endPointStr, const Vector<HTTPParamT<T>>& paramVector);

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

		HTTPParamT<T>* setParam(const StringASCII& paramName, const StringASCII& paramValue);
		void setParams(const Vector<HTTPParamT<T>>& paramVector);
		void setType(const typename HTTPEndPointT<T>::Type type);
		void setHostname(const StringASCII& hostname);
		void setEndPoint(const StringASCII& endPoint);

		const HTTPParamT<T>* getParam(const StringASCII& paramName) const;
		HTTPParamT<T>* getParam(const StringASCII& paramName);
		typename HTTPEndPointT<T>::Type getType() const;
		const StringASCII& getHostname() const;
		const StringASCII& getEndPoint() const;

		static const StringASCII& getTypeString(typename HTTPEndPointT<T>::Type type);
		static typename HTTPEndPointT<T>::Type getType(const StringASCII& typeStr);

	private:
		void copyParamVector(const Vector<HTTPParamT<T>*>& paramVector);

		Vector<HTTPParamT<T>*> paramVector;
		Type type;
		StringASCII hostname;
		StringASCII endPointStr;

	};

	using HTTPEndPoint = HTTPEndPointT<int>;

	template<typename T>
	class HTTPQueryT {
	public:
		HTTPQueryT();

		~HTTPQueryT();

		HTTPParamT<T>* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		const HTTPParamT<T>* getHeaderParam(const StringASCII& paramName) const;
		HTTPParamT<T>* getHeaderParam(const StringASCII& paramName);

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

		Vector<HTTPParamT<T>*> headerParamVector;

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
		void setEndPoint(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParamT<T>>& paramVector);
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

		HTTPParamT<T>* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		HTTPResponseT<T> * query(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& urlParams);

	private:
		HTTPRequestT<T> request;
		HTTPResponseT<T> response;
	};

	using HTTPClient = HTTPClientT<int>;

	template<typename T>
	inline HTTPParamT<T>::HTTPParamT(const StringASCII& name) :
		name(name)
	{}

	template<typename T>
	inline HTTPParamT<T>::HTTPParamT(const StringASCII & name, const StringASCII & value) :
		name(name),
		value(value)
	{}

	template<typename T>
	inline HTTPParamT<T>::HTTPParamT(const HTTPParamT<T>&param) :
		name(param.name),
		value(param.value)
	{}

	template<typename T>
	inline void HTTPParamT<T>::setValue(const StringASCII & value) {
		this->value = value;
	}

	template<typename T>
	inline const StringASCII& HTTPParamT<T>::getName() const {
		return this->name;
	}

	template<typename T>
	inline const StringASCII& HTTPParamT<T>::getValue() const {
		return this->value;
	}

	template<typename T>
	inline HTTPQueryT<T>::HTTPQueryT() :
		bHeaderNeedFormat(false)
	{}

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->headerParamVector.getBegin()); it != this->headerParamVector.getEnd(); this->headerParamVector.iterate(&it) ) {
			delete this->headerParamVector.getValueIt(it);
		}
	}

	template<typename T>
	inline HTTPParamT<T>* HTTPQueryT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		HTTPParamT<T>* param(getHeaderParam(paramName));
		if ( param ) {
			param->setValue(paramValue);
		} else {
			param = new HTTPParamT<T>(paramName, paramValue);
			this->headerParamVector.push(param);
		}
		this->bHeaderNeedFormat = true;
		return param;
	}

	template<typename T>
	inline const HTTPParamT<T>* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) const {
		return const_cast< HTTPQueryT<T> * >( this )->getHeaderParam(paramName);
	}

	template<typename T>
	inline HTTPParamT<T>* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) {
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->headerParamVector.getBegin()); it != this->headerParamVector.getEnd(); this->headerParamVector.iterate(&it) ) {
			HTTPParamT<T>* param(this->headerParamVector.getValueIt(it));

			if ( param->getName() == paramName ) {
				return param;
			}
		}
		return NULL;
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

			for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->headerParamVector.getBegin()); it != this->headerParamVector.getEnd(); this->headerParamVector.iterate(&it) ) {
				const HTTPParamT<T>* param(this->headerParamVector.getValueIt(it));

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

			HTTPParamT<T>* newParam(new HTTPParamT<T>(newParamName, newParamValue));

			this->headerParamVector.push(newParam);

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
	inline void HTTPRequestT<T>::setEndPoint(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParamT<T>>& paramVector) {
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
	inline HTTPEndPointT<T>::HTTPEndPointT(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParamT<T>>& paramVector) :
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
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
			delete this->paramVector.getValueIt(it);
		}
	}

	template<typename T>
	inline HTTPEndPointT<T>& HTTPEndPointT<T>::operator=(const HTTPEndPointT<T>& endPoint) {
		this->type = endPoint.type;
		this->endPointStr = endPoint.endPointStr;
		copyParamVector(endPoint.paramVector);

		return *this;
	}

	template<typename T>
	inline HTTPEndPointT<T>& HTTPEndPointT<T>::operator=(const HTTPEndPointT<T>&& endPoint) {
		this->type = Utility::toRValue(endPoint.type);
		this->endPointStr = Utility::toRValue(endPoint.endPointStr);
		this->paramVector = Utility::toRValue(endPoint.paramVector);

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
			for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->paramVector.getBegin()); it < this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
				const HTTPParamT<T>* param(this->paramVector.getValueIt(it));

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
	inline HTTPParamT<T>* HTTPEndPointT<T>::setParam(const StringASCII& paramName, const StringASCII& paramValue) {
		HTTPParamT<T>* param(getParam(paramName));

		if ( param ) {
			param->setValue(paramValue);
		} else {
			param = new HTTPParamT<T>(paramName, paramValue);
			this->paramVector.push(param);
		}

		return param;
	}

	template<typename T>
	inline void HTTPEndPointT<T>::setParams(const Vector<HTTPParamT<T>>& paramVector) {
		this->paramVector.clear();
		for ( typename Vector<HTTPParamT<T>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
			const HTTPParamT<T>& param(paramVector.getValueIt(it));

			this->paramVector.push(new HTTPParamT<T>(param));
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
	inline const HTTPParamT<T>* HTTPEndPointT<T>::getParam(const StringASCII& paramName) const {
		return const_cast< HTTPEndPointT<T> * >( this )->getParam(paramName);
	}

	template<typename T>
	inline HTTPParamT<T>* HTTPEndPointT<T>::getParam(const StringASCII& paramName) {
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
			HTTPParamT<T>* param(this->paramVector.getValueIt(it));
			if ( param->getName() == paramName ) {
				return param;
			}
		}
		return NULL;
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
	inline void HTTPEndPointT<T>::copyParamVector(const Vector<HTTPParamT<T>*>& paramVector) {
		for ( typename Vector<HTTPParamT<T>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
			const HTTPParamT<T>* param(paramVector.getValueIt(it));

			this->paramVector.push(new HTTPParamT<T>(*param));
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

				HTTPParamT<T>* newParam(new HTTPParamT<T>(paramNameStr));
				this->paramVector.push(newParam);

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

			HTTPParamT<T>* newParam(new HTTPParamT<T>(paramNameStr, paramValueStr));
			this->paramVector.push(newParam);

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
	inline HTTPParamT<T>* HTTPClientT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		return this->request.setHeaderParam(paramName, paramValue);
	}

	template<typename T>
	inline HTTPResponseT<T> * HTTPClientT<T>::query(typename HTTPEndPointT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& urlParams) {
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

}

#include "HTTPClient.hpp"