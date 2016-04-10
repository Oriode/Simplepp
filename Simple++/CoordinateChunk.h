#pragma once


#include "Log.h"
#include "Math.h"
#include "Vector.h"
#include "OrderedMap.h"

template<typename F, typename I, unsigned int size = 1000>
class CoordinateChunk {
public:
	enum class Direction : unsigned int { Right, Left, Top, Bottom, Front, Back };

	CoordinateChunk(const Math::Vec3<I> & position);
	~CoordinateChunk();


	
	const I & getNeighborsDistance(Direction direction) {
		return this -> neighborsDistance[(unsigned int) direction];
	}

	const F & getNeighborsDistanceF(Direction direction) {
		return this -> neighborsDistanceF[(unsigned int) direction];
	}

	CoordinateChunk * getNeighbors(Direction direction) {
		return this -> neightborsChunks[(unsigned int) direction];
	}



	CoordinateChunk * insertChunk(const Math::Vec3<I> & position) {

		Math::Vec3<I> vec3It(position);
		CoordinateChunk * it = this;
		CoordinateChunk * next;
		I distance;
		CoordinateChunk * leftBottomBack = it;


		bool generateRightTopBack = false;
		bool generateLeftTopFront = false;
		bool generateRightBottomFront = false;
		//bool generateRightBottomBack = false;
		//bool generateRightBottomBack = false;
		//bool generateRightBottomBack = false;
		//bool generateRightBottomBack = false;



		//XXXXXXXXXXXXX
		while ( (next = it -> getNeighbors(Direction::Right)) && (distance = it -> getNeighborsDistance(Direction::Right)) <= vec3It.x ) {
			vec3It.x -= distance;
			it = next;
		}
		if ( vec3It.x != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(position.x, 0, 0));

			next = it -> getNeighbors(Direction::Right);
			distance = it -> getNeighborsDistance(Direction::Right) - vec3It.x;

			newChunk -> _setNeighbor(Direction::Right, next, distance );
			newChunk -> _setNeighbor(Direction::Left, it, vec3It.x);

			it  -> 		_setNeighbor(Direction::Right, newChunk, vec3It.x);
			if ( next )
				next  -> 	_setNeighbor(Direction::Left, newChunk, distance);

			it = newChunk;
		}
		CoordinateChunk * rightBottomBack = it;

		//YYYYYYYYYYYY
		while ( ( next = it -> getNeighbors(Direction::Top) ) && ( distance = it -> getNeighborsDistance(Direction::Top) ) <= vec3It.y ) {
			vec3It.y -= distance;
			it = next;
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(position.x, position.y, 0));

			next = it -> getNeighbors(Direction::Top);
			distance = it -> getNeighborsDistance(Direction::Top) - vec3It.y;

			newChunk -> _setNeighbor(Direction::Top, next, distance );
			newChunk -> _setNeighbor(Direction::Bottom, it, vec3It.y);

			it  -> 		_setNeighbor(Direction::Top, newChunk, vec3It.y);
			if ( next )
				next  -> 	_setNeighbor(Direction::Bottom, newChunk, distance);
			it = newChunk;
			generateRightTopBack = true;
		}
		CoordinateChunk * rightTopBack = it;
		//ZZZZZZZZZZZ
		while ( ( next = it -> getNeighbors(Direction::Front) ) && ( distance = it -> getNeighborsDistance(Direction::Front) ) <= vec3It.z ) {
			vec3It.z -= distance;
			it = next;
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(position);

			next = it -> getNeighbors(Direction::Front);
			distance = it -> getNeighborsDistance(Direction::Front) - vec3It.z;

			newChunk -> _setNeighbor(Direction::Front, next, distance );
			newChunk -> _setNeighbor(Direction::Back, it, vec3It.z);

			it  -> 		_setNeighbor(Direction::Front, newChunk, vec3It.z);
			if ( next )
				next  -> 	_setNeighbor(Direction::Back, newChunk, distance);
			it = newChunk;
		} else {
			//The chunk we wanted to add already exists...LOL
			return it;
		}
		CoordinateChunk * rightTopFront = it;
		//Now the new chunk is created, we have to create the two other path


		//Roll back on the right bottom back chunk and fill the other axis
		it = rightBottomBack;
		vec3It.x = I(0);
		vec3It.y = position.y;
		vec3It.z = position.z;
		while ( it -> getNeighbors(Direction::Front) && it -> getNeighborsDistance(Direction::Front) <= vec3It.z ) {
			vec3It.z -= it -> getNeighborsDistance(Direction::Front);
			it = it -> getNeighbors(Direction::Front);
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(position.x, 0, position.z));

			next = it -> getNeighbors(Direction::Front);
			distance = it -> getNeighborsDistance(Direction::Front) - vec3It.z;

			newChunk -> _setNeighbor(Direction::Front, next, distance );
			newChunk -> _setNeighbor(Direction::Back, it, vec3It.z);

			it  -> 		_setNeighbor(Direction::Front, newChunk, vec3It.z);
			if ( next )
				next  -> 	_setNeighbor(Direction::Back, newChunk, distance );
			it = newChunk;
			generateRightBottomFront = true;
		}
		CoordinateChunk * rightBottomFront = it;



		while ( it -> getNeighbors(Direction::Top) && it -> getNeighborsDistance(Direction::Top) <= vec3It.y) {
			vec3It.y -= it -> getNeighborsDistance(Direction::Top);
			it = it -> getNeighbors(Direction::Top);
		}
		next = it -> getNeighbors(Direction::Top);
		distance = it -> getNeighborsDistance(Direction::Top) - vec3It.y;

		rightTopFront -> _setNeighbor(Direction::Top, next, distance);
		rightTopFront -> _setNeighbor(Direction::Bottom, it, vec3It.y);

		it  -> 		_setNeighbor(Direction::Top, rightTopFront, vec3It.y);
		if ( next )
			next  -> 	_setNeighbor(Direction::Bottom, rightTopFront, distance);




		it = leftBottomBack;
		vec3It.x = position.x;
		vec3It.y = position.y;
		vec3It.z = position.z;

		while ( it -> getNeighbors(Direction::Top) && it -> getNeighborsDistance(Direction::Top) <= vec3It.y ) {
			vec3It.y -= it -> getNeighborsDistance(Direction::Top);
			it = it -> getNeighbors(Direction::Top);
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(0, position.y, 0));

			next = it -> getNeighbors(Direction::Top);
			distance = it -> getNeighborsDistance(Direction::Top) - vec3It.y;

			newChunk -> _setNeighbor(Direction::Top, next, distance );
			newChunk -> _setNeighbor(Direction::Bottom, it, vec3It.y);

			it  -> 		_setNeighbor(Direction::Top, newChunk, vec3It.y);
			if ( next )
				next  -> 	_setNeighbor(Direction::Bottom, newChunk, distance);
			it = newChunk;

		}
		CoordinateChunk * leftTopBack = it;



		if ( generateRightTopBack ) {

			while ( it -> getNeighbors(Direction::Right) && it -> getNeighborsDistance(Direction::Right) <= vec3It.x ) {
				vec3It.x -= it -> getNeighborsDistance(Direction::Right);
				it = it -> getNeighbors(Direction::Right);
			}
			next = it -> getNeighbors(Direction::Right);
			distance = it -> getNeighborsDistance(Direction::Right) - vec3It.x;

			rightTopBack -> _setNeighbor(Direction::Right, next, distance);
			rightTopBack -> _setNeighbor(Direction::Left, it, vec3It.x);

			it  -> 		_setNeighbor(Direction::Right, rightTopBack, vec3It.x);
			if ( next )
				next  -> 	_setNeighbor(Direction::Left, rightTopBack, distance);

		}
		
			

		it = leftTopBack;
		vec3It.x = position.x;
		vec3It.y = I(0);
		vec3It.z = position.z;

		while ( it -> getNeighbors(Direction::Front) && it -> getNeighborsDistance(Direction::Front) <= vec3It.z ) {
			vec3It.z -= it -> getNeighborsDistance(Direction::Front);
			it = it -> getNeighbors(Direction::Front);
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(0, position.y, position.z));

			next = it -> getNeighbors(Direction::Front);
			distance = it -> getNeighborsDistance(Direction::Front) - vec3It.z;

			newChunk -> _setNeighbor(Direction::Front, next, distance );
			newChunk -> _setNeighbor(Direction::Back, it, vec3It.z);

			it  -> 		_setNeighbor(Direction::Front, newChunk, vec3It.z);
			if ( next )
				next  -> 	_setNeighbor(Direction::Back, newChunk, distance );
			it = newChunk;
			generateLeftTopFront = true;
		}
		CoordinateChunk * leftTopFront = it;



		while ( it -> getNeighbors(Direction::Right) && it -> getNeighborsDistance(Direction::Right) <= vec3It.x ) {
			vec3It.x -= it -> getNeighborsDistance(Direction::Right);
			it = it -> getNeighbors(Direction::Right);
		}
		next = it -> getNeighbors(Direction::Right);
		distance = it -> getNeighborsDistance(Direction::Right) - vec3It.x;

		rightTopFront -> _setNeighbor(Direction::Right, next, distance);
		rightTopFront -> _setNeighbor(Direction::Left, it, vec3It.x);

		it  -> 		_setNeighbor(Direction::Right, rightTopFront, vec3It.x);
		if ( next )
			next  -> 	_setNeighbor(Direction::Left, rightTopFront, distance);
			





		it = leftBottomBack;
		vec3It.x = position.x;
		vec3It.y = position.y;
		vec3It.z = position.z;
		while ( it -> getNeighbors(Direction::Front) && it -> getNeighborsDistance(Direction::Front) <= vec3It.z ) {
			vec3It.z -= it -> getNeighborsDistance(Direction::Front);
			it = it -> getNeighbors(Direction::Front);
		}
		if ( vec3It.y != 0 ) {
			CoordinateChunk * newChunk = it -> _insertChunk(Math::Vec3<I>(0, 0, position.z));

			next = it -> getNeighbors(Direction::Front);
			distance = it -> getNeighborsDistance(Direction::Front) - vec3It.z;

			newChunk -> _setNeighbor(Direction::Front, next, distance);
			newChunk -> _setNeighbor(Direction::Back, it, vec3It.z);

			it  -> 		_setNeighbor(Direction::Front, newChunk, vec3It.z);
			if ( next )
				next  -> 	_setNeighbor(Direction::Back, newChunk, distance);
			it = newChunk;
		}

		CoordinateChunk * leftBottomFront = it;


		if ( generateRightBottomFront ) {
			while ( it -> getNeighbors(Direction::Right) && it -> getNeighborsDistance(Direction::Right) <= vec3It.x ) {
				vec3It.x -= it -> getNeighborsDistance(Direction::Right);
				it = it -> getNeighbors(Direction::Right);
			}

			next = it -> getNeighbors(Direction::Right);
			distance = it -> getNeighborsDistance(Direction::Right) - vec3It.x;

			rightBottomFront -> _setNeighbor(Direction::Right, next, distance);
			rightBottomFront -> _setNeighbor(Direction::Left, it, vec3It.x);

			it  -> 		_setNeighbor(Direction::Right, rightBottomFront, vec3It.x);
			if ( next )
				next  -> 	_setNeighbor(Direction::Left, rightBottomFront, distance);


		}







		if ( generateLeftTopFront || true ) {

			it = leftBottomFront;
			vec3It.x = position.x;
			vec3It.y = position.y;
			vec3It.z = I(0);

			while ( it -> getNeighbors(Direction::Top) && it -> getNeighborsDistance(Direction::Top) <= vec3It.y ) {
				vec3It.y -= it -> getNeighborsDistance(Direction::Top);
				it = it -> getNeighbors(Direction::Top);
			}
			next = it -> getNeighbors(Direction::Top);
			distance = it -> getNeighborsDistance(Direction::Top) - vec3It.y;

			leftTopFront -> _setNeighbor(Direction::Top, next, distance);
			leftTopFront -> _setNeighbor(Direction::Bottom, it, vec3It.y);

			it  -> 		_setNeighbor(Direction::Top, leftTopFront, vec3It.y);
			if ( next )
				next  -> 	_setNeighbor(Direction::Bottom, leftTopFront, distance);

		}
		

			


		
		return rightTopFront;

	}
	
	/*
	CoordinateChunk * setObjectPosition(CoordinateSystemObject<F> * object, const Math::Vec3<F> & newPosition) {

		return NULL;
	
	}
	*/

	const Math::Vec3<I> & getPosition() const {
		return this -> position;
	}

	
private:
	
	CoordinateChunk * _insertChunk(const Math::Vec3<I> & position) {
		return new CoordinateChunk(position);
	}
	void _setNeighbor(Direction direction, CoordinateChunk * chunk, I distance) {
		this -> neightborsChunks[(unsigned int) direction] = chunk;
		this -> neighborsDistance[(unsigned int) direction] = distance;
		this -> neighborsDistanceF[(unsigned int) direction] = F(distance) * F(size);
	}


	Math::Vec3<I> position;
	I neighborsDistance[6];
	F neighborsDistanceF[6];

	CoordinateChunk * neightborsChunks[6];

	static const Math::Vec3<F> neighborsBias[6];


};



#include "CoordinateChunk.hpp"