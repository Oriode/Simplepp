#pragma once

#include "../Vector.h"
#include "TLSConnection.h"

namespace Network {

	template<typename T>
	class HTTPParamT {
	public:
		HTTPParamT(const StringASCII & name);
		HTTPParamT(const StringASCII& name, const StringASCII& value);

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

		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPEndPointT(const StringASCII::Iterator* itP, const EndFunc & endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parse(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII format() const;
		void format(StringASCII* outputStr);

		HTTPParamT<T>* setParam(const StringASCII& paramName, const StringASCII& paramValue);
		void setType(const Type type);
		void setEndPoint(const StringASCII& endPoint);

		const HTTPParamT<T>* getParam(const StringASCII& paramName) const;
		HTTPParamT<T>* getParam(const StringASCII& paramName);
		Type getType() const;
		const StringASCII& getEndPoint() const;

		static StringASCII& getTypeString(Type type);
		static Type getType(const StringASCII& typeStr);

	private:
		Vector<HTTPParamT<T>*> paramVector;
		Type type;
		StringASCII endPointStr;

	};

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
		bool parseQuery(const StringASCII::Iterator * itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQuery(StringASCII* outputStr) const;

		StringASCII protocolStr;

	private:
		///@brief Format the query header using the specified params.
		void formatQueryHeader();

		///@brief Parse the query String and update the header params Vector.
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryHeader(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		Vector<HTTPParamT<T>*> requestHeaderParamVector;

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
		HTTPResponseT(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr);

		void setStatusCode(unsigned int statusCode);
		void setStatusMessage(const StringASCII& statusMessage);

		const unsigned int getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		unsigned int statusCode;
		StringASCII statusMessage;

	private:
	};

	using HTTPResponse = HTTPResponseT<int>;

	template<typename T>
	class HTTPRequestT : public HTTPQueryT<T> {
	public:
		HTTPRequestT();
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPRequestT(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr);

		void setMethod(const StringASCII& method);
		void setEndPoint(const StringASCII& endPoint);
		void setEndPoint(const StringASCII& endPoint, const Vector<HTTPParam>& urlParams);

		const StringASCII& getMethod() const;
		const StringASCII& getEndPoint() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::Iterator* itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		StringASCII formatEndPoint(const StringASCII& endPoint, const Vector<HTTPParam>& urlParams);

		StringASCII methodStr;
		StringASCII endPoint;
	};

	template<typename T>
	class HTTPClientT {
	public:
		HTTPClientT();

		HTTPParamT<T>* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		HTTPResponseT<T> query(const StringASCII& endPoint, const Vector<HTTPParam>& urlParams) const;

	private:
		///@brief Generate a request using an endpoint and the defined header params.
		///@param endPoint End point to be requested.
		///@return Request ready to be sent to the server.
		StringASCII createRequestGET(const StringASCII& endPoint) const;

		HTTPRequestT<T> request;
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
	inline HTTPQueryT<T>::HTTPQueryT() {}

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->requestHeaderParamVector.getBegin()); it != this->requestHeaderParamVector.getEnd(); this->requestHeaderParamVector.iterate(&it) ) {
			delete this->requestHeaderParamVector.getValueIt(it);
		}
	}

	template<typename T>
	inline HTTPParamT<T>* HTTPQueryT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		HTTPParamT<T>* param(getHeaderParam(paramName));
		if ( param ) {
			param->setValue(paramValue);
		} else {
			HTTPParamT<T>* newParam(new HTTPParamT<T>(paramName, paramValue));
			this->requestHeaderParamVector.push(newParam);
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
		for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->requestHeaderParamVector.getBegin()); it != this->requestHeaderParamVector.getEnd(); this->requestHeaderParamVector.iterate(&it) ) {
			const HTTPParamT<T>* param(this->requestHeaderParamVector.getValueIt(it));

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
	inline bool HTTPQueryT<T>::parseQuery(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		if ( !parseQueryHeader(itP, endFunc) ) {
			return false;
		}

		StringASCII::Iterator& it(*itP);
		for ( ; ( *it == StringASCII::ElemType('\n') || *it == StringASCII::ElemType('\r') ) && endFunc(it); it++ );

		const StringASCII::Iterator contentStrBeginIt(it);
		for ( ; endFunc(it); it++ );
		this->contentStr = StringASCII(contentStrBeginIt, Size(it - contentStrBeginIt));

		return true;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQuery(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->headerStr;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
		str << this->contentStr;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryHeader() {
		if ( this->bHeaderNeedFormat ) {

			this->headerStr.clear();

			for ( typename Vector<HTTPParamT<T>*>::Iterator it(this->requestHeaderParamVector.getBegin()); it != this->requestHeaderParamVector.getEnd(); this->requestHeaderParamVector.iterate(&it) ) {
				const HTTPParamT<T>* param(this->requestHeaderParamVector.getValueIt(it));

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
	inline bool HTTPQueryT<T>::parseQueryHeader(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorParamName(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType(':') && * it == StringASCII::ElemType(' ') && *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it == StringASCII::ElemType(' ') && *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && endFunc(it); }

			const EndFunc& endFunc
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorParamName functorParamName(endFunc);
		static FunctorSpace functorSpace(endFunc);

		StringASCII::Iterator& it(*itP);
		while ( true ) {
			// Skip spaces.
			for ( ; functorSpace(it); it++ );

			const StringASCII::Iterator paramNameBeginIt(it);
			for ( ; functorParamName(it); it++ );
			const StringASCII::Iterator paramNameEndIt(it);

			if ( *it == StringASCII::ElemType(':') ) {
				it++;
			}

			// Skip spaces.
			for ( ; functorSpace(it); it++ );

			const StringASCII::Iterator paramValueBeginIt(it);
			for ( ; functorNewLine(it); it++ );
			const StringASCII::Iterator paramValueEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt || paramValueBeginIt == paramValueEndIt ) {
				error("HTTP header syntax error.");
				return false;
			}

			StringASCII newParamName(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));
			StringASCII newParamValue(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			HTTPParamT<T>* newParam(new HTTPParamT<T>(newParamName, newParamValue));

			this->requestHeaderParamVector.push(newParam);

			// End condition.
			if ( *it == StringASCII::ElemType('\r') && endFunc(it) ) {
				it++;
				if ( *it == StringASCII::ElemType('\n') && endFunc(it) ) {
					it++;
				}
				if ( *it == StringASCII::ElemType('\r') && endFunc(it) ) {
					it++;
					if ( *it == StringASCII::ElemType('\n') && endFunc(it) ) {
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
	inline HTTPResponseT<T>::HTTPResponseT(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQuery(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
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
	inline void HTTPResponseT<T>::formatQuery(StringASCII* outputStr) {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusCode(unsigned int statusCode) {
		this->statusCode = statusCode;
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusMessage(const StringASCII& statusMessage) {
		this->statusMessage = statusMessage;
	}

	template<typename T>
	inline const unsigned int HTTPResponseT<T>::getStatusCode() const {
		return this->statusCode;
	}

	template<typename T>
	inline const StringASCII& HTTPResponseT<T>::getStatusMessage() const {
		return this->statusMessage;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQueryTitle(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && it < endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord(const EndFunc& endFunc) :
				endFunc(endFunc){}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType(' ') && *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it == StringASCII::ElemType(' ') && *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n') && endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorWord functorWord(endFunc);
		static FunctorSpace functorSpace(endFunc);

		StringASCII::Iterator& it(*itP);
		// Skip spaces.
		for ( ; functorSpace(it); it++ );

		const StringASCII::Iterator protocolStrBeginIt(it);
		for ( ; functorWord(it); it++ );
		const StringASCII::Iterator protocolStrEndIt(it);

		// Skip spaces.
		for ( ; functorSpace(it); it++ );

		Size statusCode(StringASCII::toULongLong(&it, 10, functorWord));

		// Skip spaces.
		for ( ; functorSpace(it); it++ );

		const StringASCII::Iterator statusMessageBeginIt(it);
		for ( ; functorWord(it); it++ );
		const StringASCII::Iterator statusMessageEndIt(it);

		// Skip up to end line.
		for ( ; functorNewLine(it); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType('\r') && endFunc(it) ) {
			it++;
			if ( *it == StringASCII::ElemType('\n') && endFunc(it) ) {
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
	inline HTTPRequestT<T>::HTTPRequestT(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQuery(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		if ( !parseQueryTitle(itP, endFunc) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery(itP, endFunc) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline StringASCII HTTPRequestT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		formatQuery(&outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQuery(StringASCII* outputStr) {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::setMethod(const StringASCII& method) {
		this->methodStr = method;
	}

	template<typename T>
	inline HTTPEndPointT<T>::HTTPEndPointT() {}

	template<typename T>
	inline StringASCII HTTPEndPointT<T>::format() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		format(&outputStr);
	}

	template<typename T>
	inline void HTTPEndPointT<T>::format(StringASCII* outputStr) {
		StringASCII& str(*outputStr);

		str << getTypeString(this->type);
		str << StringASCII::ElemType(':');
		str << StringASCII::ElemType('/');
		str << StringASCII::ElemType('/');
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
	template<typename EndFunc>
	inline HTTPEndPointT<T>::HTTPEndPointT(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		parse(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPEndPointT<T>::parse(const StringASCII::Iterator* itP, const EndFunc& endFunc) {
		struct FunctorProtocol {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType(':') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorEndPoint {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType('?') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType('=') && *it != StringASCII::ElemType('&') && endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamValue {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::Iterator it) { return *it != StringASCII::ElemType('&') && endFunc(it); }

			const EndFunc& endFunc;
		};

		FunctorProtocol functorProtocol(endFunc);
		FunctorEndPoint functorEndPoint(endFunc);
		FunctorParamName functorParamName(endFunc);
		FunctorParamValue functorParamValue(endFunc);

		StringASCII::Iterator& it(*itP);

		const StringASCII::Iterator protocolStrBeginIt(it);
		for ( ; functorProtocol(it); it++ );
		const StringASCII::Iterator protocolStrEndIt(it);

		if ( protocolStrBeginIt == protocolStrEndIt || !endFunc(it) ) {
			error("EndPoint syntax error : no protocol.");
			return false;
		}

		// Skip :
		it++;

		// Skip /
		for ( ; *it == StringASCII::ElemType('/') && endFunc(it); it++ );

		const StringASCII::Iterator endPointStrBeginIt(it);
		for ( ; functorEndPoint(it); it++ );
		const StringASCII::Iterator endPointStrEndIt(it);

		if ( endPointStrBeginIt == endPointStrEndIt ) {
			error("EndPoint syntax error : no end point.");
			return false;
		}

		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));
		StringASCII endPointStr(endPointStrBeginIt, Size(endPointStrEndIt - endPointStrBeginIt));

		this->type = getType(protocolStr.toLower());

		if ( this->type == Type::Unknown ) {
			error("EndPoint syntax error : unknown protocol.");
			return false;
		}

		this->endPointStr = endPointStr;
		this->paramVector.clear();

		if ( !endFunc(it) ) {
			return true;
		}

		// Skip ?
		it++;

		// Parse the params
		while ( true ) {
			const StringASCII::Iterator paramNameBeginIt(it);
			for ( ; functorParamName(it); it++ );
			const StringASCII::Iterator paramNameEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt ) {
				error("EndPoint syntax error : param name missing.");
				return false;
			}

			StringASCII paramNameStr(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));

			if ( !functorParamValue(it) ) {

				HTTPParamT<T>* newParam(new HTTPParamT<T>(paramNameStr));
				this->paramVector.push(newParam);

				if ( !endFunc(it) ) {
					break;
				}

				if ( !functorParamValue(it) ) {
					// Skip &
					it++;
					continue;
				}
			}

			// Skip =
			it++;

			const StringASCII::Iterator paramValueBeginIt(it);
			for ( ; functorParamValue(it); it++ );
			const StringASCII::Iterator paramValueEndIt(it);

			StringASCII paramValueStr(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			HTTPParamT<T>* newParam(new HTTPParamT<T>(paramNameStr, paramValueStr));
			this->paramVector.push(newParam);

			if ( !endFunc(it) ) {
				break;
			}
		}

		return true;
	}

}

#include "HTTPClient.hpp"