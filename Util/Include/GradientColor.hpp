
#ifndef NOISE_GRADIENTCOLOR_HPP
#define NOISE_GRADIENTCOLOR_HPP

#include <Color.hpp>
#include <GradientPoint.hpp>

namespace noise::utils
{
	/// Defines a color gradient.
	///
	/// A color gradient is a list of gradually-changing colors.  A color
	/// gradient is defined by a list of <i>gradient points</i>.  Each
	/// gradient point has a position and a color.  In a color gradient, the
	/// colors between two adjacent gradient points are linearly interpolated.
	///
	/// To add a gradient point to the color gradient, pass its position and
	/// color to the AddGradientPoint() method.
	///
	/// To retrieve a color from a specific position in the color gradient,
	/// pass that position to the GetColor() method.
	///
	/// This class is a useful tool for coloring height maps based on
	/// elevation.
	///
	/// <b>Gradient example</b>
	///
	/// Suppose a gradient object contains the following gradient points:
	/// - -1.0 maps to black.
	/// - 0.0 maps to white.
	/// - 1.0 maps to red.
	///
	/// If an application passes -0.5 to the GetColor() method, this method
	/// will return a gray color that is halfway between black and white.
	///
	/// If an application passes 0.25 to the GetColor() method, this method
	/// will return a very light pink color that is one quarter of the way
	/// between white and red.
	class GradientColor
	{

	public:

		/// Constructor.
		GradientColor();

		/// Destructor.
		~GradientColor();

		/// Adds a gradient point to this gradient object.
		///
		/// @param gradientPos The position of this gradient point.
		/// @param gradientColor The color of this gradient point.
		///
		/// @pre No two gradient points have the same position.
		///
		/// @throw Noise::ExceptionInvalidParam See the precondition.
		///
		/// It does not matter which order these gradient points are added.
		void AddGradientPoint(double gradientPos,
				const Color& gradientColor);

		/// Deletes all the gradient points from this gradient object.
		///
		/// @post All gradient points from this gradient object are deleted.
		void Clear();

		/// Returns the color at the specified position in the color gradient.
		///
		/// @param gradientPos The specified position.
		///
		/// @returns The color at that position.
		const Color& GetColor(double gradientPos) const;

		/// Returns a pointer to the array of gradient points in this object.
		///
		/// @returns A pointer to the array of gradient points.
		///
		/// Before calling this method, call GetGradientPointCount() to
		/// determine the number of gradient points in this array.
		///
		/// It is recommended that an application does not store this pointer
		/// for later use since the pointer to the array may change if the
		/// application calls another method of this object.
		const GradientPoint* GetGradientPointArray() const
		{
			return m_pGradientPoints;
		}

		/// Returns the number of gradient points stored in this object.
		///
		/// @returns The number of gradient points stored in this object.
		int GetGradientPointCount() const
		{
			return m_gradientPointCount;
		}

	private:

		/// Determines the array index in which to insert the gradient point
		/// into the internal gradient-point array.
		///
		/// @param gradientPos The position of this gradient point.
		///
		/// @returns The array index in which to insert the gradient point.
		///
		/// @pre No two gradient points have the same input value.
		///
		/// @throw Noise::ExceptionInvalidParam See the precondition.
		///
		/// By inserting the gradient point at the returned array index, this
		/// object ensures that the gradient-point array is sorted by input
		/// value.  The code that maps a value to a color requires a sorted
		/// gradient-point array.
		int FindInsertionPos(double gradientPos);

		/// Inserts the gradient point at the specified position in the
		/// internal gradient-point array.
		///
		/// @param insertionPos The zero-based array position in which to
		/// insert the gradient point.
		/// @param gradientPos The position of this gradient point.
		/// @param gradientColor The color of this gradient point.
		///
		/// To make room for this new gradient point, this method reallocates
		/// the gradient-point array and shifts all gradient points occurring
		/// after the insertion position up by one.
		///
		/// Because this object requires that all gradient points in the array
		/// must be sorted by the position, the new gradient point should be
		/// inserted at the position in which the order is still preserved.
		void InsertAtPos(int insertionPos, double gradientPos,
				const Color& gradientColor);

		/// Number of gradient points.
		int m_gradientPointCount;

		/// Array that stores the gradient points.
		GradientPoint* m_pGradientPoints;

		/// A color object that is used by a gradient object to store a
		/// temporary value.
		mutable Color m_workingColor;
	};
}

#endif //NOISE_GRADIENTCOLOR_HPP
