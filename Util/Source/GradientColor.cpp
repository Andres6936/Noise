#include <cstdint>
#include <cassert>
#include <noise/exception.h>
#include <noise/misc.h>
#include <GradientColor.hpp>


using namespace noise::utils;

// Performs linear interpolation between two 8-bit channel values.
inline std::uint8_t BlendChannel(const std::uint8_t channel0,
		const std::uint8_t channel1, float alpha)
{
	float c0 = (float)channel0 / 255.0;
	float c1 = (float)channel1 / 255.0;
	return (std::uint8_t)(((c1 * alpha) + (c0 * (1.0f - alpha))) * 255.0f);
}

// Performs linear interpolation between two colors and stores the result
// in out.
inline void LinearInterpColor(const Color& color0, const Color& color1,
		float alpha, Color& out)
{
	out.alpha = BlendChannel(color0.alpha, color1.alpha, alpha);
	out.blue = BlendChannel(color0.blue, color1.blue, alpha);
	out.green = BlendChannel(color0.green, color1.green, alpha);
	out.red = BlendChannel(color0.red, color1.red, alpha);
}


GradientColor::GradientColor()
{
	m_pGradientPoints = NULL;
}

GradientColor::~GradientColor()
{
	delete[] m_pGradientPoints;
}

void GradientColor::AddGradientPoint(double gradientPos,
		const Color& gradientColor)
{
	// Find the insertion point for the new gradient point and insert the new
	// gradient point at that insertion point.  The gradient point array will
	// remain sorted by gradient position.
	int insertionPos = FindInsertionPos(gradientPos);
	InsertAtPos(insertionPos, gradientPos, gradientColor);
}

void GradientColor::Clear()
{
	delete[] m_pGradientPoints;
	m_pGradientPoints = NULL;
	m_gradientPointCount = 0;
}

int GradientColor::FindInsertionPos(double gradientPos)
{
	int insertionPos;
	for (insertionPos = 0; insertionPos < m_gradientPointCount;
		 insertionPos++)
	{
		if (gradientPos < m_pGradientPoints[insertionPos].pos)
		{
			// We found the array index in which to insert the new gradient point.
			// Exit now.
			break;
		}
		else if (gradientPos == m_pGradientPoints[insertionPos].pos)
		{
			// Each gradient point is required to contain a unique gradient
			// position, so throw an exception.
			throw noise::ExceptionInvalidParam();
		}
	}
	return insertionPos;
}

const Color& GradientColor::GetColor(double gradientPos) const
{
	assert (m_gradientPointCount >= 2);

	// Find the first element in the gradient point array that has a gradient
	// position larger than the gradient position passed to this method.
	int indexPos;
	for (indexPos = 0; indexPos < m_gradientPointCount; indexPos++)
	{
		if (gradientPos < m_pGradientPoints[indexPos].pos)
		{
			break;
		}
	}

	// Find the two nearest gradient points so that we can perform linear
	// interpolation on the color.
	int index0 = ClampValue(indexPos - 1, 0, m_gradientPointCount - 1);
	int index1 = ClampValue(indexPos, 0, m_gradientPointCount - 1);

	// If some gradient points are missing (which occurs if the gradient
	// position passed to this method is greater than the largest gradient
	// position or less than the smallest gradient position in the array), get
	// the corresponding gradient color of the nearest gradient point and exit
	// now.
	if (index0 == index1)
	{
		m_workingColor = m_pGradientPoints[index1].color;
		return m_workingColor;
	}

	// Compute the alpha value used for linear interpolation.
	double input0 = m_pGradientPoints[index0].pos;
	double input1 = m_pGradientPoints[index1].pos;
	double alpha = (gradientPos - input0) / (input1 - input0);

	// Now perform the linear interpolation given the alpha value.
	const Color& color0 = m_pGradientPoints[index0].color;
	const Color& color1 = m_pGradientPoints[index1].color;
	LinearInterpColor(color0, color1, (float)alpha, m_workingColor);
	return m_workingColor;
}

void GradientColor::InsertAtPos(int insertionPos, double gradientPos,
		const Color& gradientColor)
{
	// Make room for the new gradient point at the specified insertion position
	// within the gradient point array.  The insertion position is determined by
	// the gradient point's position; the gradient points must be sorted by
	// gradient position within that array.
	GradientPoint* newGradientPoints;
	newGradientPoints = new GradientPoint[m_gradientPointCount + 1];
	for (int i = 0; i < m_gradientPointCount; i++)
	{
		if (i < insertionPos)
		{
			newGradientPoints[i] = m_pGradientPoints[i];
		}
		else
		{
			newGradientPoints[i + 1] = m_pGradientPoints[i];
		}
	}
	delete[] m_pGradientPoints;
	m_pGradientPoints = newGradientPoints;
	++m_gradientPointCount;

	// Now that we've made room for the new gradient point within the array, add
	// the new gradient point.
	m_pGradientPoints[insertionPos].pos = gradientPos;
	m_pGradientPoints[insertionPos].color = gradientColor;
}
