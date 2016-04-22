///@file Gradient.h
///@brief Gradient Class
///@author Clément Gerber
///@date 19/04/16 (DMY)


#pragma once
#include "Math.h"
#include "BasicGraphic.h"
#include "InterpolationFunc.hpp"




namespace Graphic {

	///@brief A point in a gradient
	///@template C Type for one color.
	template<typename C = ColorRGBA<unsigned char>>
	class GradientPoint {
	public:

		///@brief Create a Point for a Gradient initialized with a position and a color
		///@param position Floating number between 0 and 1 representing the position on the gradient.
		///@param color Color of this point.
		GradientPoint(float position, const C & color);

		///@brief set the position of this point.
		///@param position new position.
		void setPosition(float position);


		///@brief get the Position of this point
		///@return The position of this point (value between 0.0 and 1.0)
		float getPosition() const;

		///@brief set the color of this point
		///@param color new color.
		void setColor(const C & color);


		///@brief get the color of this point
		///@return Color
		const C & getColor() const;
		

	private:
		C color;
		float position;			//between 0 and 1
	};



	

	

	///@brief Represent a 2D Gradient for 2D image processing.
	template<typename C, typename Func = InterpolationFunc::Linear>
	class Gradient {
	public:
		///@brief Create a new gradient.
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		Gradient(const Func & functor = Func());

		///@brief destructor
		~Gradient();

		///@brief add a point to this gradient.
		void addPoint(float position, const C & color);

		///@brief get the number of points of this gradient.
		///@return Number of points of this gradient.
		typename Vector<GradientPoint<C> *>::Size getNumPoints() const;


		///@brief Operator [] to direct access points inside this gradient.
		///@param i index of the points (in the order added first is 0)
		GradientPoint<C> & operator[](typename Vector<GradientPoint<C> *>::Size i);


		///@brief Compute the interpolation of every color of this gradient in an 1D array
		///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		template<size_t N, typename Func2 = Func>
		void computeInterpolation(C(&buffer)[N], const Func2 & functor = Func()) const;

		///@brief Compute the interpolation of every color of this gradient in an 1D array
		///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		template<typename Func2 = Func>
		void computeInterpolation(C * buffer, size_t size, const Func2 & functor = Func()) const;

		///@brief Compute the interpolation of every color of this gradient in an 1D array
		///@param out kernel Already allocated buffer to be filled with the interpolation of this gradient.
		void computeInterpolation(C * buffer, size_t size) const;
	private:
		Vector<GradientPoint<C> * > pointsVector;
		Func functor;
	};


	template<typename C, typename Func = InterpolationFunc::Linear>
	class GradientHorizontal : public Gradient<C, Func> {
	public:
		///@brief Create a new Horizontal gradient.
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		GradientHorizontal(const Func & functor = Func());

	private:


	};

	template<typename C, typename Func = InterpolationFunc::Linear>
	class GradientVertical : public Gradient<C, Func> {
	public:
		///@brief Create a new Horizontal gradient.
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		GradientVertical(const Func & functor = Func());

	private:



	};


	template<typename C, typename Func = InterpolationFunc::Linear>
	class GradientRadial : public Gradient<C, Func> {
		public:
			///@brief Create a new Radial Gradient
			///@param center Point of the center relatively of the surface applied (between 0 and 1)
			///@param radius Radius horizontal and vertical relatively to the size of the surface applied (between 0 and 1)
			///@param functor Functor used to interpolate the colors overloaded with :
			///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
			GradientRadial(const Math::Vec2<float> & center = Math::Vec2<float>(0.5f), const Math::Vec2<float> & radius = Math::Vec2<float>(1.0f), const Func & functor = Func());


			///@brief Set the center of the radial gradient (between 0 and 1)
			///@param center Center of the radial gradient (between 0 and 1)
			void setCenter(const Math::Vec2<float> & center);


			///@brief get the center of this gradient
			///@return Center
			const Math::Vec2<float> & getCenter() const;


			///@brief set the radius
			///@param radius Radius of this radial gradient relatively of the size of the surface (between 0 and 1)
			void setRadius(const Math::Vec2<float> & radius);


			///@brief get the radius of this gradient
			///@return Radius of this gradient
			const Math::Vec2<float> & getRadius() const;



	private:
		Math::Vec2<float> center;
		Math::Vec2<float> radius;
	};





	template<typename C, typename Func = InterpolationFunc::Linear>
	class GradientLinear : public Gradient<C, Func> {
	public:
		///@brief Create a new Linear Gradient
		///@param angle Angle in degree
		///@p point of this gradient.
		///@param length Length of this gradient (0 mean auto computed)
		///@param functor Functor used to interpolate the colors overloaded with :
		///				template<typename C> inline C operator()(const C & color1, const C & color2, float x) const;
		GradientLinear(float angle, const Math::Vec2<float> & p = Math::Vec2<float>::null, unsigned int length = 0, const Func & functor = Func());

		///@brief set the angle of this linear gradient
		///@param angle Angle in Degree of this gradient (0 mean left to right) then it's anti clockwise
		void setAngle(float angle);

		///@brief set the starting point of this gradient
		///@param p Point (between 0 and 1)
		void setPoint(const Math::Vec2<float> & p);

		///brief set the length of this linear gradient
		///param length Length in pixels (0 mean auto computed)
		void setLength(unsigned int length);

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
	private:
		unsigned int length;
		Math::Vec2<float> p;
		float angle;
		float angleRad;
	};

	


	


	


	

}


#include "Gradient.hpp"


