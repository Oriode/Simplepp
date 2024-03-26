#pragma once

#include "../String.h"
#include "../ParamContainer.h"
#include "Url.h"
#include "Network.h"
#include "HTTPQuery.h"

namespace Network {

	template<typename T>
	class HTTPRequestT : public HTTPQueryT<T> {
	public:
		typedef typename UrlT<T>::Sheme Type;

		enum class Verb : unsigned char {
			GET,
			POST,
			DEL,
			PUT,
			Unknown
		};

		HTTPRequestT();
		HTTPRequestT( typename HTTPRequestT<T>::Verb verb, const UrlT<T>& url );
		HTTPRequestT( typename HTTPRequestT<T>::Verb verb, typename UrlT<T>::Sheme type, const StringASCII& hostname );
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPRequestT( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		StringASCII formatQuery() const;
		void formatQuery( StringASCII* outputStr ) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		void formatQueryTitle( StringASCII* outputStr ) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryContent( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		void setVerb( typename HTTPRequestT<T>::Verb method );
		void setUrl( const UrlT<T>& url );

		///@brief	Set the URI of this request. (The part right of the hostname and before the params).
		void setPath( const StringASCII& pathStr );

		void setUrlParams( const Vector<HTTPParam>& paramVector );
		
		typename HTTPRequestT<T>::Verb getVerb() const;
		const UrlT<T>& getUrl() const;

		static const StringASCII& getVerbStr( typename HTTPRequestT<T>::Verb verb );
		static typename HTTPRequestT<T>::Verb getVerb( const StringASCII& verbStr );

		static const StringASCII verbStrTable[];

	protected:
		void initHostParam();
		void initParams();
		void updateHostParamValue();

		Verb verb;
		UrlT<T> url;

		HTTPParam* hostParam;
	};

	using HTTPRequest = HTTPRequestT<int>;

}

#include "HTTPRequest.hpp"

