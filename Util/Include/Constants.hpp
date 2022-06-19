
#ifndef NOISE_CONSTANTS_HPP
#define NOISE_CONSTANTS_HPP

namespace noise::utils
{
	/// The maximum width of a raster.
	const int RASTER_MAX_WIDTH = 32767;

	/// The maximum height of a raster.
	const int RASTER_MAX_HEIGHT = 32767;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	// The raster's stride length must be a multiple of this constant.
	const int RASTER_STRIDE_BOUNDARY = 4;

#endif

	/// Number of meters per point in a Terragen terrain (TER) file.
	const double DEFAULT_METERS_PER_POINT = 30.0;

	/// Same as the DEFAULT_METERS_PER_POINT constant, but for us
	/// canuckleheads.
	const double DEFAULT_METRES_PER_POINT = DEFAULT_METERS_PER_POINT;
}

#endif //NOISE_CONSTANTS_HPP
