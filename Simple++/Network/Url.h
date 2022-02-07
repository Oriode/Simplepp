#pragma once

#include "../ParamContainer.h"
#include "BasicNetwork.h"

namespace Network {

	template<typename T>
	class UrlT : public ParamContainerT<StringASCII, StringASCII> {
	public:
		enum class Type : unsigned char {
			HTTP,
			HTTPS,
			Unknown
		};

		UrlT();
		UrlT(typename UrlT<T>::Type type, const StringASCII& hostname);
		UrlT(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector);

		template<typename EndFunc = StringASCII::IsEndIterator>
		UrlT(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		UrlT(const UrlT<T>& url);
		UrlT(const UrlT<T>&& url);

		~UrlT();

		UrlT<T>& operator=(const UrlT<T>& url);
		UrlT<T>& operator=(const UrlT<T>&& url);

		bool parse(const StringASCII& str);
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parse(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		bool parseParams(const StringASCII& str);
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseParams(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII format() const;
		void format(StringASCII* outputStr) const;

		StringASCII formatWOParams() const;
		void formatWOParams(StringASCII* outputStr) const;

		StringASCII formatParams() const;
		void formatParams(StringASCII* outputStr) const;

		void setType(const typename UrlT<T>::Type type);
		void setHostname(const StringASCII& hostname);
		void setEndPoint(const StringASCII& endPoint);

		typename UrlT<T>::Type getType() const;
		const StringASCII& getHostname() const;
		const StringASCII& getEndPoint() const;

		static const StringASCII& getTypeString(typename UrlT<T>::Type type);
		static typename UrlT<T>::Type getType(const StringASCII& typeStr);

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(IO::SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(IO::SimpleFileStream* fileStream) const;

	private:
		Type type;
		StringASCII hostname;
		StringASCII endPointStr;

	};

	using Url = UrlT<int>;

}

#include "Url.hpp"