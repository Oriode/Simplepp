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
		typedef typename UrlT<T>::Type Type;

		enum class Method : unsigned char {
			GET,
			POST,
			DEL,
			Unknown
		};

		HTTPRequestT();
		HTTPRequestT( const UrlT<T>& url );
		HTTPRequestT( typename UrlT<T>::Type type, const StringASCII& hostname );
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

		void setMethod( typename HTTPRequestT<T>::Method method );
		void setEndPoint( const UrlT<T>& url );
		void setEndPoint( const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector );
		void setEndPoint( typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector );
		void setEndPoint( const StringASCII& endPointStr );

		typename HTTPRequestT<T>::Method getMethod() const;
		const UrlT<T>& getEndPoint() const;

		static const StringASCII& getMethodString( typename HTTPRequestT<T>::Method method );
		static typename HTTPRequestT<T>::Method getMethod( const StringASCII& methodStr );

		static const StringASCII methodStrTable[];

	protected:
		void initHostParam();
		void initParams();
		void updateHostParamValue();

		Method method;
		UrlT<T> url;

		HTTPParam* hostParam;
	};

	using HTTPRequest = HTTPRequestT<int>;

}

#include "HTTPRequest.hpp"

