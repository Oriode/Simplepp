#pragma once


#include "Math.h"

template<typename T = float>
class CoordinateSystemObject {
public:
	CoordinateSystemObject();
	~CoordinateSystemObject();

	

	const Vec3<T> & getCoordinate() const;


protected:
	void setCoordinate(const Vec3<T> & v);

private:
	Vec3<T> coordinate;


};

