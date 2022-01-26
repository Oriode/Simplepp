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
		void parseQuery(const StringASCII::Iterator * itP, const StringASCII::Iterator & endIt);

		void formatQuery(StringASCII* outputStr) const;

		StringASCII protocolStr;

	private:
		///@brief Format the query header using the specified params.
		void formatQueryHeader();

		///@brief Parse the query String and update the header params Vector.
		void parseQueryHeader(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

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
		HTTPResponseT(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

		void parseQuery(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

		StringASCII formatQuery() const;

		void setStatusCode(unsigned int statusCode);
		void setStatusMessage(const StringASCII& statusMessage);

		const unsigned int getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		void parseQueryTitle(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

		void formatQueryTitle(StringASCII* outputStr) const;

		unsigned int statusCode;
		StringASCII statusMessage;

	private:
	};

	using HTTPResponse = HTTPResponseT<int>;

	template<typename T>
	class HTTPRequestT : public HTTPQueryT<T> {
	public:
		HTTPRequest();
		HTTPRequest(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

		void parseQuery(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

		StringASCII formatQuery() const;

		void setMethod(const StringASCII& method);
		void setEndPoint(const StringASCII& endPoint);
		void setEndPoint(const StringASCII& endPoint, const Vector<HTTPParam>& urlParams);

		const StringASCII& getMethod() const;
		const StringASCII& getEndPoint() const;

	protected:
		void parseQueryTitle(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt);

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
	inline void HTTPQueryT<T>::parseQuery(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt) {
		parseQueryHeader(itP, endIt);

		StringASCII::Iterator& it(*itP);
		for ( ; it < endIt; it++ ) {
			if ( *it == StringASCII::ElemType('\n') || *it == StringASCII::ElemType('\r') ) {
				continue;
			}
		}

		this->contentStr = StringASCII(it, Size(endIt - it));
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
	inline void HTTPQueryT<T>::parseQueryHeader(const StringASCII::Iterator* itP, const StringASCII::Iterator& endIt) {
		struct FunctorNewLine {
			bool operator()(const StringASCII::ElemType& c) { return *it != StringASCII::ElemType('\r') && *it != StringASCII::ElemType('\n'); }
		};

		static FunctorNewLine functorNewLine;

		StringASCII::Iterator& it(*itP);
		while ( true ) {
			const StringASCII::Iterator paramNameBeginIt(it);
			for ( ; *it != StringASCII::ElemType(':') && functorNewLine(*it) && it < endIt; it++ );
			const StringASCII::Iterator paramNameEndIt(it);
			for ( ; *it == StringASCII::ElemType(' ') && functorNewLine(*it) && it < endIt; it++ );
			const StringASCII::Iterator paramValueBeginIt(it);
			for ( ; functorNewLine(*it) && it < endIt; it++ );
			const StringASCII::Iterator paramValueEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt || paramValueBeginIt == paramValueEndIt ) {
				error("HTTP header syntax error.");
				break;
			}

			StringASCII newParamName(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));
			StringASCII newParamValue(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			HTTPParamT<T>* newParam(new HTTPParamT<T>(newParamName, newParamValue));

			this->requestHeaderParamVector.push(newParam);

			// End condition.
			if ( *it == StringASCII::ElemType('\r') ) {
				it++;
				if ( *it == StringASCII::ElemType('\n') ) {
					it++;
				}
				if ( *it == StringASCII::ElemType('\r') ) {
					it++;
					if ( *it == StringASCII::ElemType('\n') ) {
						it++;
					}
					break;
				}
				continue;
			}
		}

	}

}

#include "HTTPClient.hpp"