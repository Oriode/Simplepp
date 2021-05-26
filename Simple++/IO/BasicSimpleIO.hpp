
namespace IO {

	template<typename T>
	bool BasicSimpleIOT<T>::read(SimpleFileStream* fileStream) {
		_assert(fileStream->isOpen());
		return true;
	}

	template<typename T>
	bool BasicSimpleIOT<T>::write(SimpleFileStream* fileStream) const {
		_assert(fileStream->isOpen());
		return true;
	}

}