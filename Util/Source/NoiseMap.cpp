#include <cstring>
#include <noise/exception.h>
#include <NoiseMap.hpp>

using namespace noise::utils;

NoiseMap::NoiseMap()
{
	InitObj();
}

NoiseMap::NoiseMap(int width, int height)
{
	InitObj();
	SetSize(width, height);
}

NoiseMap::NoiseMap(const NoiseMap& rhs)
{
	InitObj();
	CopyNoiseMap(rhs);
}

NoiseMap::~NoiseMap()
{
	delete[] m_pNoiseMap;
}

NoiseMap& NoiseMap::operator=(const NoiseMap& rhs)
{
	CopyNoiseMap(rhs);

	return *this;
}

void NoiseMap::Clear(float value)
{
	if (m_pNoiseMap != NULL)
	{
		for (int y = 0; y < m_height; y++)
		{
			float* pDest = GetSlabPtr(0, y);
			for (int x = 0; x < m_width; x++)
			{
				*pDest++ = value;
			}
		}
	}
}

void NoiseMap::CopyNoiseMap(const NoiseMap& source)
{
	// Resize the Noise map buffer, then copy the slabs from the source Noise
	// map buffer to this Noise map buffer.
	SetSize(source.GetWidth(), source.GetHeight());
	for (int y = 0; y < source.GetHeight(); y++)
	{
		const float* pSource = source.GetConstSlabPtr(0, y);
		float* pDest = GetSlabPtr(0, y);
		std::memcpy(pDest, pSource, (size_t)source.GetWidth() * sizeof(float));
	}

	// Copy the border value as well.
	m_borderValue = source.m_borderValue;
}

void NoiseMap::DeleteNoiseMapAndReset()
{
	delete[] m_pNoiseMap;
	InitObj();
}

float NoiseMap::GetValue(int x, int y) const
{
	if (m_pNoiseMap != NULL)
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			return *(GetConstSlabPtr(x, y));
		}
	}
	// The coordinates specified are outside the Noise map.  Return the border
	// value.
	return m_borderValue;
}

void NoiseMap::InitObj()
{
	m_pNoiseMap = NULL;
	m_height = 0;
	m_width = 0;
	m_stride = 0;
	m_memUsed = 0;
	m_borderValue = 0.0;
}

void NoiseMap::ReclaimMem()
{
	size_t newMemUsage = CalcMinMemUsage(m_width, m_height);
	if (m_memUsed > newMemUsage)
	{
		// There is wasted memory.  Create the smallest buffer that can fit the
		// data and copy the data to it.
		float* pNewNoiseMap = NULL;
		try
		{
			pNewNoiseMap = new float[newMemUsage];
		}
		catch (...)
		{
			throw noise::ExceptionOutOfMemory();
		}
		memcpy(pNewNoiseMap, m_pNoiseMap, newMemUsage * sizeof(float));
		delete[] m_pNoiseMap;
		m_pNoiseMap = pNewNoiseMap;
		m_memUsed = newMemUsage;
	}
}

void NoiseMap::SetSize(int width, int height)
{
	if (width < 0 || height < 0
		|| width > RASTER_MAX_WIDTH || height > RASTER_MAX_HEIGHT)
	{
		// Invalid width or height.
		throw noise::ExceptionInvalidParam();
	}
	else if (width == 0 || height == 0)
	{
		// An empty Noise map was specified.  Delete it and zero out the size
		// member variables.
		DeleteNoiseMapAndReset();
	}
	else
	{
		// A new Noise map size was specified.  Allocate a new Noise map buffer
		// unless the current buffer is large enough for the new Noise map (we
		// don't want costly reallocations going on.)
		size_t newMemUsage = CalcMinMemUsage(width, height);
		if (m_memUsed < newMemUsage)
		{
			// The new size is too big for the current Noise map buffer.  We need to
			// reallocate.
			DeleteNoiseMapAndReset();
			try
			{
				m_pNoiseMap = new float[newMemUsage];
			}
			catch (...)
			{
				throw noise::ExceptionOutOfMemory();
			}
			m_memUsed = newMemUsage;
		}
		m_stride = (int)CalcStride(width);
		m_width = width;
		m_height = height;
	}
}

void NoiseMap::SetValue(int x, int y, float value)
{
	if (m_pNoiseMap != NULL)
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			*(GetSlabPtr(x, y)) = value;
		}
	}
}

void NoiseMap::TakeOwnership(NoiseMap& source)
{
	// Copy the values and the Noise map buffer from the source Noise map to
	// this Noise map.  Now this Noise map pwnz the source buffer.
	delete[] m_pNoiseMap;
	m_memUsed = source.m_memUsed;
	m_height = source.m_height;
	m_pNoiseMap = source.m_pNoiseMap;
	m_stride = source.m_stride;
	m_width = source.m_width;

	// Now that the source buffer is assigned to this Noise map, reset the
	// source Noise map object.
	source.InitObj();
}
