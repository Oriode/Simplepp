#include "Url.h"
namespace Network {

	template<typename T>
	inline UrlT<T>::UrlT() {}

	template<typename T>
	inline UrlT<T>::UrlT(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector) :
		type(type),
		hostname(hostname),
		endPointStr(endPointStr) {
		setParams(paramVector);
	}

	template<typename T>
	inline UrlT<T>::UrlT(const UrlT<T>& url) :
		ParamContainerT<StringASCII, StringASCII>(url),
		type(url.type),
		hostname(url.hostname),
		endPointStr(url.endPointStr) {}

	template<typename T>
	inline UrlT<T>::UrlT(const UrlT<T>&& url) :
		ParamContainerT<StringASCII, StringASCII>(Utility::toRValue(url)),
		type(Utility::toRValue(url.type)),
		hostname(Utility::toRValue(url.hostname)),
		endPointStr(Utility::toRValue(url.endPointStr)) {}

	template<typename T>
	inline UrlT<T>::~UrlT() {

	}

	template<typename T>
	inline UrlT<T>& UrlT<T>::operator=(const UrlT<T>& url) {
		ParamContainerT<StringASCII, StringASCII>::operator=(url);
		this->type = url.type;
		this->hostname = url.hostname;
		this->endPointStr = url.endPointStr;

		return *this;
	}

	template<typename T>
	inline UrlT<T>& UrlT<T>::operator=(const UrlT<T>&& url) {
		ParamContainerT<StringASCII, StringASCII>::operator=(Utility::toRValue(url));
		this->type = Utility::toRValue(url.type);
		this->hostname = Utility::toRValue(url.hostname);
		this->endPointStr = Utility::toRValue(url.endPointStr);

		return *this;
	}

	template<typename T>
	inline bool UrlT<T>::parse(const StringASCII& str) {
		StringASCII::IsEndIterator endFunc(endPoint.getEnd());
		String::Iterator it(endPoint.getBegin());

		return parse(&it, endFunc);
	}

	template<typename T>
	inline StringASCII UrlT<T>::format() const {
		StringASCII outputStr;
		outputStr.reserve(1024);

		format(&outputStr);

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::format(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << getTypeString(this->type);
		str << StringASCII::ElemType(':');
		str << StringASCII::ElemType('/');
		str << StringASCII::ElemType('/');
		str << this->hostname;
		str << this->endPointStr;

		if ( this->paramVector.getSize() > Size(0) ) {
			str << StringASCII::ElemType('?');
			formatParams(&str);
		}
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatParams() const {
		StringASCII outputStr;
		outputStr.reserve(256);

		formatParams(&outputStr);

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::formatParams(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

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

	template<typename T>
	inline void UrlT<T>::setType(const typename UrlT<T>::Type type) {
		this->type = type;
	}

	template<typename T>
	inline void UrlT<T>::setHostname(const StringASCII& hostname) {
		this->hostname = hostname;
	}

	template<typename T>
	inline void UrlT<T>::setEndPoint(const StringASCII& endPoint) {
		this->endPointStr = endPoint;
	}

	template<typename T>
	inline typename UrlT<T>::Type UrlT<T>::getType() const {
		return this->type;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getHostname() const {
		return this->hostname;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getEndPoint() const {
		return this->endPointStr;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getTypeString(typename UrlT<T>::Type type) {
		static const StringASCII typeStrTable[] = { StringASCII("http"), StringASCII("https") };
		unsigned char typeIndex(static_cast< unsigned char >( type ));
		if ( typeIndex < sizeof(typeStrTable) ) {
			return typeStrTable[ typeIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename UrlT<T>::Type UrlT<T>::getType(const StringASCII& typeStr) {
		switch ( typeStr ) {
			case getTypeString(Type::HTTP):
				{
					return Type::HTTP;
				}
			case getTypeString(Type::HTTPS):
				{
					return Type::HTTPS;
				}
			default:
				{
					return Type::Unknown;
				}
		}
	}

	template<typename T>
	inline bool UrlT<T>::read(IO::SimpleFileStream* fileStream) {
		if ( !ParamContainerT<StringASCII, StringASCII>::read(fileStream) ) {
			return false;
		}
		unsigned char typeChar;
		if ( !IO::read(fileStream, &typeChar) ) {
			return false;
		}
		this->type = static_cast< UrlT<T>::Type >( typeChar );
		if ( !IO::read(fileStream, &this->hostname) ) {
			return false;
		}
		if ( !IO::read(fileStream, &this->endPointStr) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool UrlT<T>::write(IO::SimpleFileStream* fileStream) const {
		if ( !ParamContainerT<StringASCII, StringASCII>::write(fileStream) ) {
			return false;
		}
		unsigned char typeChar(static_cast< unsigned char >( this->type ));
		if ( !IO::write(fileStream, &typeChar) ) {
			return false;
		}
		if ( !IO::write(fileStream, &this->hostname) ) {
			return false;
		}
		if ( !IO::write(fileStream, &this->endPointStr) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline UrlT<T>::UrlT(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		parse(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool UrlT<T>::parse(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		struct FunctorProtocol {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType(':') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorHostname {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('/') || *it == StringASCII::ElemType('?') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorEndPoint {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('?') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('=') || *it == StringASCII::ElemType('&') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamValue {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('&') || endFunc(it); }

			const EndFunc& endFunc;
		};

		FunctorProtocol functorProtocol(endFunc);
		FunctorHostname functorHostname(endFunc);
		FunctorEndPoint functorEndPoint(endFunc);
		FunctorParamName functorParamName(endFunc);
		FunctorParamValue functorParamValue(endFunc);

		const StringASCII::ElemType*& it(*itP);

		const StringASCII::ElemType* protocolStrBeginIt(it);
		for ( ; !functorProtocol(it); it++ );
		const StringASCII::ElemType* protocolStrEndIt(it);

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

		const StringASCII::ElemType* hostnameStrBeginIt(it);
		for ( ; !functorHostname(it); it++ );
		const StringASCII::ElemType* hostnameStrEndIt(it);

		const StringASCII::ElemType* endPointStrBeginIt(it);
		for ( ; !functorEndPoint(it); it++ );
		const StringASCII::ElemType* endPointStrEndIt(it);

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
			const StringASCII::ElemType* paramNameBeginIt(it);
			for ( ; !functorParamName(it); it++ );
			const StringASCII::ElemType* paramNameEndIt(it);

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

			const StringASCII::ElemType* paramValueBeginIt(it);
			for ( ; !functorParamValue(it); it++ );
			const StringASCII::ElemType* paramValueEndIt(it);

			StringASCII paramValueStr(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			addParam(new HTTPParam(paramNameStr, paramValueStr));

			if ( !endFunc(it) ) {
				break;
			}
		}

		return true;
	}

}