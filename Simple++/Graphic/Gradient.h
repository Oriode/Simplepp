///@file Gradient.h
///@brief Gradient Class
///@author Clément Gerber
///@date 19/04/16 (DMY)


#pragma once
#include "../Math/Math.h"
#include "BasicGraphic.h"
#include "../IO/FileStream.h"




namespace Graphic {


	namespace Gradient {

		///@brief A point in a gradient
		///@tparam C Type for one color.
		template<typename C = ColorRGBA<unsigned char>>
		class Point {
		public:
			///@brief Empty constructor
			Point();

			///@brief Create a Point for a Gradient initialized with a position and a color
			///@param position Floating number between 0 and 1 representing the position on the gradient.
			///@param color Color of this point.
			Point( float position, const C & color );

			///@brief set the position of this point.
			///@param position new position.
			void setPosition( float position );

			///@brief Copy constructor
			Point( const Point & ) = default;

			///@brief Copy operator
			Point & operator=( const Point & ) = default;

			///@brief get the Position of this point
			///@return The position of this point (value between 0.0 and 1.0)
			float getPosition() const;

			///@brief set the color of this point
			///@param color new color.
			void setColor( const C & color );


			///@brief get the color of this point
			///@return Color
			const C & getColor() const;

			///@brief get the color of this point cast to the float format
			///@return Color
			const typename C::ColorFloat & getColorFloat() const;


		private:
			C color;
			typename C::ColorFloat colorFloat;
			float position;			//between 0 and 1
		};






		///@brief Represent a 2D Gradient for 2D image processing.
		template<typename C, typename InterFunc = Math::InterpolationFunc::Linear>
		class Template : public IO::BasicIO {
		public:
			///@brief destructor
			~Template();

			///@brief add a point to this gradient.
			void addPoint( float position, const C & color );

			///@brief get the number of points of this gradient.
			///@return Number of points of this gradient.
			Size getNumPoints() const;


			///@brief Operator [] to direct access points inside this gradient.
			///@param i index of the points (in the order added first is 0)
			Point<C> & operator[]( Size i );

			///@brief Operator [] to direct access points inside this gradient.
			///@param i index of the points (in the order added first is 0)
			const Point<C> & operator[]( Size i ) const;


			///@brief Compute the interpolation of every color of this gradient in an 1D array
			///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			///@param begin beginning of the interpolation (between 0.0 and 1.0)
			///@param end ending of the interpolation (between 0.0 and 1.0)
			template<size_t N, typename InterFunc2 = InterFunc>
			void computeInterpolation( C( &buffer )[N], const InterFunc2 & functor = InterFunc(), float begin = 0.0f, float end = 1.0f ) const;

			///@brief Compute the interpolation of every color of this gradient in an 1D array
			///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			///@param begin beginning of the interpolation (between 0.0 and 1.0)
			///@param end ending of the interpolation (between 0.0 and 1.0)
			template<typename InterFunc2 = InterFunc>
			void computeInterpolation( C * buffer, size_t size, const InterFunc2 & functor = InterFunc(), float begin = 0.0f, float end = 1.0f ) const;

			///@brief Compute the interpolation of every color of this gradient in an 1D array
			///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
			///@param begin beginning of the interpolation (between 0.0 and 1.0)
			///@param end ending of the interpolation (between 0.0 and 1.0)
			void computeInterpolation( C * buffer, size_t size, float begin = 0.0f, float end = 1.0f ) const;


			///@brief read from a file stream
			///@param stream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool read( Stream * stream, int verbose = 0 );

			///@brief write this object as binary into a file stream
			///@param stream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool write( Stream * stream ) const;

		protected:
			///@brief Create a new gradient.
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			Template( const InterFunc & functor = InterFunc() );

			///@brief Copy constructor
			///@param gradient Gradient to be copied
			Template( const Template & gradient );

			///@brief Move constructor
			///@param gradient Gradient to be moved
			Template( Template && gradient );

			///@brief Copy operator
			///@param gradient Gradient to be copied
			///@return reference to THIS
			Template & operator=( const Template & gradient );

			///@brief Move operator
			///@param gradient Gradient to be moved
			///@return reference to THIS
			Template & operator=( Template && gradient );
		private:
			void _updateOrdered();
			void _unload();
			void _clear();
			void _copy( const Template & fontEffect );
			void _move( Template && fontEffect );

			Vector<Point<C> * > pointsVector;
			Vector<Point<C> * > pointsVectorOrdered;

			bool isOrdered;

			InterFunc functor;
		};


		template<typename C, typename InterFunc = Math::InterpolationFunc::Linear>
		class Horizontal : public Template<C, InterFunc> {
		public:
			///@brief Create a new Horizontal gradient.
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			Horizontal( const InterFunc & functor = InterFunc() );

			///@brief Copy constructor
			///@param gradientHorizontal Gradient to be copied
			Horizontal( const Horizontal & gradientHorizontal );

			///@brief Move constructor
			///@param gradientHorizontal Gradient to be moved
			Horizontal( Horizontal && gradientHorizontal );

			///@brief Copy operator
			///@param gradientHorizontal Gradient to be copied
			///@return reference to THIS
			Horizontal & operator=( const Horizontal & gradientHorizontal );

			///@brief Move operator
			///@param gradientHorizontal Gradient to be moved
			///@return reference to THIS
			Horizontal & operator=( Horizontal && gradientHorizontal );

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@return Computed index.
			static int computeIndex( const Math::Vec2<GSize> & p );

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@return Computed index.
			static int computeIndex( const Graphic::Point & p, int maxIndex );
		private:


		};




		template<typename C, typename InterFunc = Math::InterpolationFunc::Linear>
		class Vertical : public Template<C, InterFunc> {
		public:
			///@brief Create a new Horizontal gradient.
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			Vertical( const InterFunc & functor = InterFunc() );

			///@brief Copy constructor
			///@param gradientVertical Gradient to be copied
			Vertical( const Vertical & gradientVertical );

			///@brief Move constructor
			///@param gradientVertical Gradient to be moved
			Vertical( Vertical && gradientVertical );

			///@brief Copy operator
			///@param gradientVertical Gradient to be copied
			///@return reference to THIS
			Vertical & operator=( const Vertical & gradientVertical );

			///@brief Move operator
			///@param gradientVertical Gradient to be moved
			///@return reference to THIS
			Vertical & operator=( Vertical && gradientVertical );

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@return Computed index.
			static int computeIndex( const Math::Vec2<GSize> & p );

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@return Computed index.
			static int computeIndex( const Graphic::Point & p, int maxIndex );


		private:



		};


		template<typename C, typename InterFunc = Math::InterpolationFunc::Linear>
		class Radial : public Template<C, InterFunc> {
		public:
			///@brief Create a new Radial Gradient
			///@param center Point of the center relatively of the surface applied (between 0 and 1)
			///@param radius Radius horizontal and vertical relatively to the size of the surface applied (between 0 and 1)
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			Radial( const Math::Vec2<float> & center = Math::Vec2<float>( 0.5f ), const Math::Vec2<float> & radius = Math::Vec2<float>( 1.0f ), const InterFunc & functor = InterFunc() );

			///@brief Copy constructor
			///@param gradientRadial Gradient to be copied
			Radial( const Radial & gradientRadial );

			///@brief Move constructor
			///@param gradientRadial Gradient to be moved
			Radial( Radial && gradientRadial );

			///@brief Copy operator
			///@param gradientRadial Gradient to be copied
			///@return reference to THIS
			Radial & operator=( const Radial & gradientRadial );

			///@brief Move operator
			///@param gradientRadial Gradient to be moved
			///@return reference to THIS
			Radial & operator=( Radial && gradientRadial );

			///@brief Set the center of the radial gradient (between 0 and 1)
			///@param center Center of the radial gradient (between 0 and 1)
			void setCenter( const Math::Vec2<float> & center );


			///@brief get the center of this gradient
			///@return Center
			const Math::Vec2<float> & getCenter() const;


			///@brief set the radius
			///@param radius Radius of this radial gradient relatively of the size of the surface (between 0 and 1)
			void setRadius( const Math::Vec2<float> & radius );


			///@brief get the radius of this gradient
			///@return Radius of this gradient
			const Math::Vec2<float> & getRadius() const;

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@return Computed index.
			int computeIndex( const Math::Vec2<float> & p, int maxIndex ) const;


			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@param radius Radius of the gradient (between 0.0 and 1.0)
			///@return Computed index.
			static int computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & radius );

			///@brief read from a file stream
			///@param stream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool read( Stream * stream, int verbose = 0 );

			///@brief write this object as binary into a file stream
			///@param stream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool write( Stream * stream ) const;

		private:
			Math::Vec2<float> center;
			Math::Vec2<float> radius;
		};






		template<typename C, typename InterFunc = Math::InterpolationFunc::Linear>
		class Linear : public Template<C, InterFunc> {
		public:
			///@brief Create a new Linear Gradient
			///@param angle Angle in degree
			///@p point of this gradient.
			///@param length Length of this gradient (0 mean auto computed)
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			Linear( float angle, const Math::Vec2<float> & p = Math::Vec2<float>::null, unsigned int length = 0, const InterFunc & functor = InterFunc() );

			///@brief Copy constructor
			///@param gradientLinear Gradient to be copied
			Linear( const Linear & gradientLinear );

			///@brief Move constructor
			///@param gradientLinear Gradient to be moved
			Linear( Linear && gradientLinear );

			///@brief Copy operator
			///@param gradientLinear Gradient to be copied
			///@return reference to THIS
			Linear & operator=( const Linear & gradientLinear );

			///@brief Move operator
			///@param gradientLinear Gradient to be moved
			///@return reference to THIS
			Linear & operator=( Linear && gradientLinear );

			///@brief set the angle of this linear gradient
			///@param angle Angle in Degree of this gradient (0 mean left to right) then it's anti clockwise
			void setAngle( float angle );

			///@brief set the starting point of this gradient
			///@param p Point (between 0 and 1)
			void setPoint( const Math::Vec2<float> & p );

			///brief set the length of this linear gradient
			///param length Length in pixels (0 mean auto computed)
			void setLength( unsigned int length );

			///@brief get the angle of this gradient
			///@return angle in degree
			float getAngle() const;

			///@brief get the angle of this gradient
			///@return angle in radians
			float getAngleRad() const;

			///@brief get the point of this gradient
			///@return point (between 0 and 1)
			const Math::Vec2<float> & getPoint() const;

			///@brief get the length of this gradient
			///@return Length in pixels
			unsigned int getLength() const;

			///@brief get the unitary vector representing the direction of this gradient.
			///@return Unitary vector
			const Math::Vec2<float> & getDirection() const;

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@return Computed index.
			int computeIndex( const Math::Vec2<float> & p, int maxIndex ) const;

			///@brief Compute the index in the interpolated array
			///@param p Point relative of this gradient.
			///@param maxIndex maximal value of an interpolation table index.
			///@param direction Unitary vector representing the direction if this gradient.
			///@return Computed index.
			static int computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & direction );


			///@brief read from a file stream
			///@param stream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool read( Stream * stream, int verbose = 0 );

			///@brief write this object as binary into a file stream
			///@param stream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			template<typename Stream>
			bool write( Stream * stream ) const;
		private:
			unsigned int length;
			Math::Vec2<float> p;
			float angle;
			float angleRad;
			Math::Vec2<float> v;
		};
	}
}


#include "Gradient.hpp"


