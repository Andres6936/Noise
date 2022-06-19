
#ifndef NOISE_GRADIENTPOINT_HPP
#define NOISE_GRADIENTPOINT_HPP

namespace noise::utils
{
	/// Defines a point used to build a color gradient.
	///
	/// A color gradient is a list of gradually-changing colors.  A color
	/// gradient is defined by a list of <i>gradient points</i>.  Each
	/// gradient point has a position and a color.  In a color gradient, the
	/// colors between two adjacent gradient points are linearly interpolated.
	///
	/// The ColorGradient class defines a color gradient by a list of these
	/// objects.
	struct GradientPoint
	{

		/// The position of this gradient point.
		double pos {};

		/// The color of this gradient point.
		Color color {};

	};
}

#endif //NOISE_GRADIENTPOINT_HPP
