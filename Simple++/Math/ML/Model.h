#pragma once

#include "../../Utility.h"
#include "ActivationFunc.h"

namespace Math {

	namespace ML {

		namespace Model {

			class BasicModel {
			public:
				constexpr BasicModel() {};

				///@brief Number of layers of the network.
				static constexpr Size nbLayers = 2;

				///@brief Table [nbLayers][2] representing for each layer the number of input (features) and output (neurons). The number of input of a layer should fit the number of output of the previous one.
				static constexpr Size m[ 2 ][ 2 ] = {
					{2,2},	// {NbIn, NbOut}
					{2,2}	// {NbIn, NbOut}
				};

				///@brief Type of the activation function of the hidden layers.
				typedef Math::ML::ActivationFunc::ReLU HiddenActivationFunc;
				///@brief Type of the activation function of the last layer.
				typedef Math::ML::ActivationFunc::Linear ActivationFunc;

				///@brief Data chunk size ued in stochastic gradient descent.
				static constexpr Size dataChunkSize = 16;
			};

		}

	}

}