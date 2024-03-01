#pragma once

#include "../ParamContainer.h"
#include "BasicNetwork.h"

namespace Network {

	template<typename T>
	class UrlT : public ParamContainerT<StringASCII, StringASCII> {
	public:
		enum class Sheme : unsigned char {
			HTTP,
			HTTPS,
			Unknown
		};

		UrlT();
		UrlT( const StringASCII & url );
		UrlT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname );
		UrlT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector );

		template<typename EndFunc = StringASCII::IsEndIterator>
		UrlT( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		UrlT( const UrlT<T>& url );
		UrlT( const UrlT<T>&& url );

		~UrlT();

		UrlT<T>& operator=( const UrlT<T>& url );
		UrlT<T>& operator=( const UrlT<T>&& url );

		bool parse( const StringASCII& str );
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parse( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		bool parseParams( const StringASCII& str );
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseParams( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL );

		StringASCII format() const;
		void format( StringASCII* outputStr ) const;

		StringASCII formatWOParams() const;
		void formatWOParams( StringASCII* outputStr ) const;

		StringASCII formatEndPointWOParams() const;
		void formatEndPointWOParams( StringASCII* outputStr ) const;

		StringASCII formatEndPoint() const;
		void formatEndPoint( StringASCII* outputStr ) const;

		StringASCII formatParams() const;
		static StringASCII formatParams( const Vector<HTTPParam*>& paramVector );
		static StringASCII formatParams( const Vector<HTTPParam>& paramVector );
		void formatParams( StringASCII* outputStr ) const;
		static void formatParams( StringASCII* outputStr, const Vector<HTTPParam*>& paramVector );
		static void formatParams( StringASCII* outputStr, const Vector<HTTPParam>& paramVector );

		void setType( const typename UrlT<T>::Sheme sheme );
		void setHostname( const StringASCII& hostname );
		void setUri( const StringASCII& endPoint );

		typename UrlT<T>::Sheme getSheme() const;
		const StringASCII& getHostname() const;
		const StringASCII& getUri() const;

		static const StringASCII& getShemeStr( typename UrlT<T>::Sheme sheme );
		static typename UrlT<T>::Sheme getSheme( const StringASCII& typeStr );

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream* stream );

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream* stream ) const;

		static const StringASCII typeStrTable[];

	private:
		Sheme sheme;
		StringASCII hostname;
		StringASCII uriStr;

	};

	using Url = UrlT<int>;

}

#include "Url.hpp"