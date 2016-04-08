
template<typename F, typename I, unsigned int size>
CoordinateChunk<F,I,size>::CoordinateChunk(const Math::Vec3<I> & position) {
	this -> position = position;
	for ( unsigned int i = 0; i < 6; i++ ) {
		//this -> neighborsDistance[i] = 1;
		//this -> neighborsDistanceF[i] = F(size);
		this -> neightborsChunks[i] = NULL;
	}
}

template<typename F, typename I, unsigned int size>
CoordinateChunk<F, I, size>::~CoordinateChunk() {

}
