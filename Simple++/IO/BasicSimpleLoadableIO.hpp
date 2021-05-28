namespace IO {

	template<typename T>
	BasicSimpleLoadableIOT<T>::BasicSimpleLoadableIOT() {
	}

	template<typename T>
	BasicSimpleLoadableIOT<T>::~BasicSimpleLoadableIOT() {
	}

	template<typename T>
	bool BasicSimpleLoadableIOT<T>::read(SimpleFileStream * fileStream) {
		unload();
		lock();
		setLoading(true);

		if (onRead(fileStream)) {
			setLoading(false);
			setLoaded(true);
			unlock();
			return true;
		}
		else {
			setLoading(false);
			setLoaded(false);
			unlock();
			return false;
		}
	}

	template<typename T>
	bool BasicSimpleLoadableIOT<T>::write(SimpleFileStream * fileStream) {
		lock();
		_assert(isLoaded());
		if (!onWrite(fileStream)) {
			unlock();
			return false;
		}
		unlock();
		return true;
	}

	template<typename T>
	bool BasicSimpleLoadableIOT<T>::onRead(SimpleFileStream* fileStream) {
		return BasicSimpleIO::read(fileStream);
	}

	template<typename T>
	bool BasicSimpleLoadableIOT<T>::onWrite(SimpleFileStream* fileStream) const {
		return BasicSimpleIO::write(fileStream);
	}

}