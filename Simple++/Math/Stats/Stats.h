#pragma once

#include "../Distance.h"
#include "../Logical.h"
#include "../Interval.h"
#include "../../Vector.h"

namespace Math {

	namespace Stats {

		template<typename FakeType>
		class StatsT {
		public:

		};

		template<typename T>
		class Cluster {
		public:
			Cluster();

			void setMean(const T& mean);
			const T& getMean() const;
			T& getMean();

			template<typename DistanceFunc = Math::Compare::DistanceFunc>
			Math::Compare::Distance getDistance(const T & v, const DistanceFunc& distanceFunc = DistanceFunc()) const;

			void addData(const T& data, const Math::Compare::Distance distance);

			const Vector<T> & getData() const;
			Vector<T> & getData();

			template<typename CompareFunc = Math::Logical::Less>
			void updateMinMax(const CompareFunc& compareFunc = CompareFunc());

			const Math::Interval<T>& getMinMaxInterval() const;

			Math::Compare::Distance getDistanceMean() const;

			void clear();

		private:
			T mean;
			Vector<T> dataVector;
			Math::Interval<T> minMaxInterval;
			Math::Compare::Distance distanceSum;
		};

		template<typename T>
		inline Cluster<T>::Cluster() :
			distanceSum(0)
		{
		}

		template<typename T>
		inline void Cluster<T>::setMean(const T& mean) {
			this->mean = mean;
		}

		template<typename T>
		inline const T& Cluster<T>::getMean() const {
			return this->mean;
		}

		template<typename T>
		inline T& Cluster<T>::getMean() {
			return this->mean;
		}

		template<typename T>
		template<typename DistanceFunc>
		inline Math::Compare::Distance Cluster<T>::getDistance(const T& v, const DistanceFunc& distanceFunc) const {
			static_assert( Utility::isBase<Math::Compare::DistanceFunc, DistanceFunc>::value, "DistanceFunc type should be a derived of Math::Compare::DistanceFunc." );
			return distanceFunc.getDistance(v, this->mean);
		}

		template<typename T>
		inline void Cluster<T>::addData(const T& data, const Math::Compare::Distance distance) {
			this->dataVector.push(data);
			this->distanceSum += distance;
		}

		template<typename T>
		inline const Vector<T>& Cluster<T>::getData() const {
			return this->dataVector;
		}

		template<typename T>
		inline Vector<T>& Cluster<T>::getData() {
			return this->dataVector;
		}

		template<typename T>
		template<typename CompareFunc>
		inline void Cluster<T>::updateMinMax(const CompareFunc& compareFunc) {
			this->minMaxInterval = getMinMax<T, CompareFunc>(this->dataVector, compareFunc);
		}

		template<typename T>
		inline const Math::Interval<T>& Cluster<T>::getMinMaxInterval() const {
			return this->minMaxInterval;
		}

		template<typename T>
		inline Math::Compare::Distance Cluster<T>::getDistanceMean() const {
			if ( this->dataVector.getSize() > Size(0) ) {
				return this->distanceSum / Math::Compare::Distance(this->dataVector.getSize());
			} else {
				return Utility::TypesInfos<Math::Compare::Distance>::getMax();
			}
		}

		template<typename T>
		inline void Cluster<T>::clear() {
			this->dataVector.clear();
			this->distanceSum = Math::Compare::Distance(0);
		}

		template<typename T, typename CompareFunc = Math::Logical::Less>
		static Math::Interval<T> getMinMax(const Vector<T>& vector, const CompareFunc& compareFunc = CompareFunc());

		template<typename T, typename DistanceFunc = Math::Compare::DistanceFunc, typename CompareFunc = Math::Logical::Less>
		static Vector<Cluster<T>> computeKMeans(const Vector<T> & vector, const Size k, const Size nbLoops = Size(10), const Size nbRngLoops = Size(10), const DistanceFunc& distanceFunc = DistanceFunc(), const CompareFunc& compareFunc = CompareFunc());

		template<typename T, typename CompareFunc>
		Math::Interval<T> getMinMax(const Vector<T>& vector, const CompareFunc& compareFunc) {
			Math::Interval<T> minMaxInterval;

			if ( vector.getSize() == Size(0) ) {
				minMaxInterval.setBegin(T());
				minMaxInterval.setEnd(T());
			}

			minMaxInterval.setBegin(vector.getValueI(Size(0)));
			minMaxInterval.setEnd(vector.getValueI(Size(0)));

			for ( Size i(1); i < vector.getSize(); i++ ) {
				const T& v(vector.getValueI(i));

				if ( compareFunc(v, minMaxInterval.getBegin()) ) {
					minMaxInterval.setBegin(v);
				} else if ( compareFunc(minMaxInterval.getEnd(), v) ) {
					minMaxInterval.setEnd(v);
				}
			}

			return minMaxInterval;
		}

		template<typename T, typename DistanceFunc, typename CompareFunc>
		Vector<Cluster<T>> computeKMeans(const Vector<T>& vector, const Size k, const Size nbLoops, const Size nbRngLoops, const DistanceFunc& distanceFunc, const CompareFunc& compareFunc) {
			Vector<Vector<Cluster<T>>> clusterVectorVector(nbRngLoops);

			if ( vector.getSize() == Size(0) ) {
				return clusterVectorVector.getFirst();
			}

			Math::Interval<T> minMaxInterval(getMinMax<T, CompareFunc>(vector));
			const T range(minMaxInterval.getSize());

			for ( Size rngLoopI(0); rngLoopI < clusterVectorVector.getSize(); rngLoopI++ ) {
				Vector<Cluster<T>> & clusterVector(clusterVectorVector.getValueI(rngLoopI));

				clusterVector.resize(k);

				// Set the mean randomly.
				for ( Size clusterI(0); clusterI < clusterVector.getSize(); clusterI++ ) {
					Cluster<T>& cluster(clusterVector.getValueI(clusterI));

					cluster.setMean(minMaxInterval.getBegin() + Math::randomF() * range);
				}

				for ( Size loopI(0); loopI < nbLoops; loopI++ ) {

					if ( loopI > Size(0) ) {
						// Re-compute the mean for every cluster.
						for ( Size clusterI(0); clusterI < clusterVector.getSize(); clusterI++ ) {
							Cluster<T>& cluster(clusterVector.getValueI(clusterI));

							T clusterNewMean(0);

							for ( Size i(0); i < cluster.getData().getSize(); i++ ) {
								const T& v(cluster.getData().getValueI(i));

								clusterNewMean += v;
							}
							clusterNewMean /= T(cluster.getData().getSize());
							cluster.setMean(clusterNewMean);

							// Clear the cluster.
							cluster.clear();
						}
					}

					// Get the distance for every cluster mean and dispatch values acordingly.
					for ( Size i(0); i < vector.getSize(); i++ ) {
						const T& v(vector.getValueI(i));

						Math::Compare::Distance distanceMin(Utility::TypesInfos<Math::Compare::Distance>::getMax());
						Size clusterMinI(0);

						for ( Size clusterI(0); clusterI < clusterVector.getSize(); clusterI++ ) {
							Cluster<T>& cluster(clusterVector.getValueI(clusterI));

							const T distance(cluster.getDistance(v, distanceFunc));
							if ( distance < distanceMin ) {
								distanceMin = distance;
								clusterMinI = clusterI;
							}
						}

						clusterVector.getValueI(clusterMinI).addData(v, distanceMin);
					}

				}

			}

			Size bestClusterVectorI(0);
			Math::Compare::Distance bestClusterVectorDistance(Utility::TypesInfos<Math::Compare::Distance>::getMax());
			for ( Size clusterVectorI(0); clusterVectorI < clusterVectorVector.getSize(); clusterVectorI++ ) {
				Vector<Cluster<T>>& clusterVector(clusterVectorVector.getValueI(clusterVectorI));

				Math::Compare::Distance clusterVectorDistance(0);

				for ( Size clusterI(0); clusterI < clusterVector.getSize(); clusterI++ ) {
					Cluster<T>& cluster(clusterVector.getValueI(clusterI));

					clusterVectorDistance += cluster.getDistanceMean();
				}

				clusterVectorDistance /= Math::Compare::Distance(clusterVector.getSize());

				if ( clusterVectorDistance < bestClusterVectorDistance ) {
					bestClusterVectorDistance = clusterVectorDistance;
					bestClusterVectorI = clusterVectorI;
				}

			}

			return clusterVectorVector.getValueI(bestClusterVectorI);

		}

}

}