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
		UrlT( const StringASCII& url );
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

		template<typename S = StringASCII>
		S format() const;

		template<typename S = StringASCII>
		void format( S* outputStr ) const;

		template<typename S = StringASCII>
		S formatWOParams() const;

		template<typename S = StringASCII>
		void formatWOParams( S* outputStr ) const;

		template<typename S = StringASCII>
		S formatPathWOParams() const;

		template<typename S = StringASCII>
		void formatPathWOParams( S* outputStr ) const;

		template<typename S = StringASCII>
		S formatPathAndParams() const;

		template<typename S = StringASCII>
		void formatPathAndParams( S* outputStr ) const;

		template<typename S = StringASCII>
		S formatParams() const;

		template<typename S = StringASCII>
		static S formatParams( const Vector<HTTPParam*>& paramVector );

		template<typename S = StringASCII>
		static S formatParams( const Vector<HTTPParam>& paramVector );

		template<typename S = StringASCII>
		void formatParams( S* outputStr ) const;

		template<typename S = StringASCII>
		static void formatParams( S* outputStr, const Vector<HTTPParam*>& paramVector );

		template<typename S = StringASCII>
		static void formatParams( S* outputStr, const Vector<HTTPParam>& paramVector );

		void setType( const typename UrlT<T>::Sheme sheme );
		void setHostname( const StringASCII& hostname );
		void setPath( const StringASCII& pathStr );

		typename UrlT<T>::Sheme getSheme() const;
		const StringASCII& getHostname() const;
		const StringASCII& getPath() const;

		static const StringASCII& getShemeStr( typename UrlT<T>::Sheme sheme );
		static typename UrlT<T>::Sheme getSheme( const StringASCII& shemeStr );

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

		template<typename S = String>
		S toString() const;

		///@brief	Url encode converting all the specials characters to url safe ones.
		static StringASCII encode( const StringASCII& str );

		static const StringASCII typeStrTable[];

	private:
		Sheme sheme;
		StringASCII hostname;
		StringASCII pathStr;

	};

	using Url = UrlT<int>;

}

#include "Url.hpp"