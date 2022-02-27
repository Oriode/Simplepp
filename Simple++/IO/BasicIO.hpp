
namespace IO {

	template<typename T>
	template<typename Stream>
	bool BasicIOT<T>::read(Stream* stream) {
		_assert(stream->isOpen());
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool BasicIOT<T>::write(Stream* stream) const {
		_assert(stream->isOpen());
		return true;
	}

}