#include "ParamContainer.h"
template<typename I, typename V>
inline ParamContainerT<I, V>::ParamContainerT() {}

template<typename I, typename V>
inline ParamContainerT<I, V>::ParamContainerT(const ParamContainerT<I, V>& paramContainer) {
	copyParamVector(paramContainer.paramVector);
}

template<typename I, typename V>
inline ParamContainerT<I, V>::ParamContainerT(const ParamContainerT<I, V>&& paramContainer) :
	paramVector(Utility::toRValue(paramContainer.paramVector)),
	paramMap(Utility::toRValue(paramContainer.paramMap)) {

}

template<typename I, typename V>
inline ParamContainerT<I, V>::~ParamContainerT() {
	for ( typename Vector<ParamT<I, V>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
		delete this->paramVector.getValueIt(it);
	}
}

template<typename I, typename V>
inline ParamContainerT<I, V>& ParamContainerT<I, V>::operator=(const ParamContainerT<I, V>& paramContainer) {
	copyParamVector(paramContainer.paramVector);

	return *this;
}

template<typename I, typename V>
inline ParamContainerT<I, V>& ParamContainerT<I, V>::operator=(const ParamContainerT<I, V>&& paramContainer) {
	this->paramVector = Utility::toRValue(endPoint.paramVector);
	this->paramMap = Utility::toRValue(endPoint.paramMap);

	return *this;
}

template<typename I, typename V>
inline ParamT<I, V>* ParamContainerT<I, V>::setParam(const I& paramName, const V& paramValue) {
	ParamT<I, V>* param(getParam(paramName));

	if ( param ) {
		param->setValue(paramValue);
	} else {
		param = new ParamT<I, V>(paramName, paramValue);
		addParam(param);
	}

	return param;
}

template<typename I, typename V>
inline void ParamContainerT<I, V>::setParams(const Vector<ParamT<I, V>>& paramVector) {
	clearParams();
	for ( typename Vector<ParamT<I, V>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
		const ParamT<I, V>& param(paramVector.getValueIt(it));

		addParam(new ParamT<I, V>(param));
	}
}

template<typename I, typename V>
inline void ParamContainerT<I, V>::setParams(const Vector<ParamT<I, V> *>& paramVector) {
	clearParams();
	for ( typename Vector<ParamT<I, V> *>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
		const ParamT<I, V>* param(paramVector.getValueIt(it));

		addParam(new ParamT<I, V>(*param));
	}
}

template<typename I, typename V>
inline bool ParamContainerT<I, V>::removeParam(const I& paramName) {
	RBNode<MapObject<I, ParamT<I, V> *>* paramNode(this->paramMap.getNodeI(paramName));
	if ( paramNode ) {
		ParamT<I, V>* param(paramNode.getValue().getValue());
		this->paramVector.eraseFirst(param);
		this->paramMap.eraseNode(paramNode);

		delete param;

		return true;
	} else {
		return false;
	}
}

template<typename I, typename V>
inline void ParamContainerT<I, V>::clearParams() {
	for ( typename Vector<ParamT<I, V>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
		delete this->paramVector.getValueIt(it);
	}

	this->paramVector.clear();
	this->paramMap.clear();
}

template<typename I, typename V>
inline const ParamT<I, V>* ParamContainerT<I, V>::getParam(const I& paramName) const {
	return const_cast< ParamContainerT<I, V> * >( this )->getParam(paramName);
}

template<typename I, typename V>
inline ParamT<I, V>* ParamContainerT<I, V>::getParam(const I& paramName) {
	ParamT<I, V>** paramP(this->paramMap.getValueI(paramName));
	if ( paramP ) {
		return *paramP;
	}
	return NULL;
}

template<typename I, typename V>
inline const Vector<ParamT<I, V>*>& ParamContainerT<I, V>::getParamVector() const {
	return this->paramVector;
}

template<typename I, typename V>
inline const Map<I, ParamT<I, V>*>& ParamContainerT<I, V>::getParamMap() const {
	return this->paramMap;
}

template<typename I, typename V>
template<typename Stream>
inline bool ParamContainerT<I, V>::read(Stream* stream) {
	Size nbParams;

	if ( !IO::read(stream, &nbParams) ) {
		return false;
	}
	for ( Size i(0); i < nbParams; i++ ) {
		ParamT<I, V>* newParam(new ParamT<I, V>());

		if ( !IO::read(stream, newParam) ) {
			return false;
		}
	}

	return true;
}

template<typename I, typename V>
template<typename Stream>
inline bool ParamContainerT<I, V>::write(Stream* stream) const {
	const Size nbParams(this->paramVector.getSize());

	if ( !IO::write(stream, &nbParams) ) {
		return false;
	}
	for ( typename Vector<ParamT<I, V>*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
		const ParamT<I, V>* param(this->paramVector.getValueIt(it));

		if ( !IO::write(stream, param) ) {
			return false;
		}
	}

	return true;
}

template<typename I, typename V>
inline void ParamContainerT<I, V>::copyParamVector(const Vector<ParamT<I, V>*>& paramVector) {
	this->paramVector.clear();
	this->paramMap.clear();
	for ( typename Vector<ParamT<I, V>>::Iterator it(paramVector.getBegin()); it != paramVector.getEnd(); paramVector.iterate(&it) ) {
		const ParamT<I, V>* param(paramVector.getValueIt(it));

		addParam(new ParamT<I, V>(*param));
	}
}

template<typename I, typename V>
inline void ParamContainerT<I, V>::addParam(ParamT<I, V>* newParam) {
	this->paramVector.push(newParam);
	this->paramMap.insert(newParam->getName(), newParam);
}