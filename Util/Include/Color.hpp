
#ifndef NOISE_COLOR_HPP
#define NOISE_COLOR_HPP

#include <cstdint>

namespace noise::utils
{

	/// Defines a color.
	///
	/// A color object contains four 8-bit channels: red, green, blue, and an
	/// alpha (transparency) channel.  Channel values range from 0 to 255.
	///
	/// The alpha channel defines the transparency of the color.  If the alpha
	/// channel has a value of 0, the color is completely transparent.  If the
	/// alpha channel has a value of 255, the color is completely opaque.
	class Color
	{

	public:

		/// Constructor.
		Color() = default;

		/// Constructor.
		///
		/// @param r Value of the red channel.
		/// @param g Value of the green channel.
		/// @param b Value of the blue channel.
		/// @param a Value of the alpha (transparency) channel.
		Color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
				std::uint8_t a) : red(r), green(g), blue(b), alpha(a)
		{
		}

		/// Value of the alpha (transparency) channel.
		std::uint8_t alpha{ };

		/// Value of the blue channel.
		std::uint8_t blue{ };

		/// Value of the green channel.
		std::uint8_t green{ };

		/// Value of the red channel.
		std::uint8_t red{ };

	};
}

#endif //NOISE_COLOR_HPP
