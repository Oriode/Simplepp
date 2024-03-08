template<typename I, typename V>
ParamT<I, V>::ParamT() {

}

template<typename I, typename V>
inline ParamT<I, V>::ParamT(const I& name) :
	name(name) {}

template<typename I, typename V>
inline ParamT<I, V>::ParamT(const I& name, const V& value) :
	name(name),
	value(value) {}

template<typename I, typename V>
inline ParamT<I, V>::ParamT(const ParamT<I, V>& param) :
	name(param.name),
	value(param.value) {}

template<typename I, typename V>
ParamT<I, V>::ParamT(const ParamT<I, V>&& param) :
	name(Utility::toRValue(param.name)),
	value(Utility::toRValue(param.value)) {

}

template<typename I, typename V>
ParamT<I, V>& ParamT<I, V>::operator=(const ParamT<I, V>& param) {
	this->name = param.name;
	this->value = param.value;

	return *this;
}

template<typename I, typename V>
ParamT<I, V>& ParamT<I, V>::operator=(const ParamT<I, V>&& param) {
	this->name = Utility::toRValue(param.name);
	this->value = Utility::toRValue(param.value);

	return *this;
}

template<typename I, typename V>
inline bool ParamT<I, V>::operator<(const ParamT<I, V>& param) const {
	return this->name < param.name;
}

template<typename I, typename V>
void ParamT<I, V>::setName(const I& name) {
	this->name = name;
}

template<typename I, typename V>
inline void ParamT<I, V>::setValue(const V& value) {
	this->value = value;
}

template<typename I, typename V>
inline const I& ParamT<I, V>::getName() const {
	return this->name;
}

template<typename I, typename V>
inline const V& ParamT<I, V>::getValue() const {
	return this->value;
}

template<typename I, typename V>
template<typename Stream>
bool ParamT<I, V>::read( Stream * stream, int verbose ) {
	if ( !IO::read( stream, &this -> name, verbose - 1 ) ) {
		return false;
	}
	if ( !IO::read( stream, &this -> value, verbose - 1 ) ) {
		return false;
	}
	return true;
}

template<typename I, typename V>
template<typename Stream>
bool ParamT<I, V>::write(Stream* stream) const {
	if ( !IO::write(stream, &this -> name) )
		return false;
	if ( !IO::write(stream, &this -> value) )
		return false;
	return true;
}