// billow.h
//
// Copyright (C) 2004 Jason Bevins
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (License.md) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//

#ifndef NOISE_MODULE_BILLOW_H
#define NOISE_MODULE_BILLOW_H

#include "modulebase.h"

namespace noise::module
{

	/// @addtogroup libnoise
	/// @{

	/// @addtogroup modules
	/// @{

	/// @addtogroup generatormodules
	/// @{

    /// Default frequency for the Noise::module::Billow Noise module.
    const double DEFAULT_BILLOW_FREQUENCY = 1.0;

    /// Default lacunarity for the the Noise::module::Billow Noise module.
    const double DEFAULT_BILLOW_LACUNARITY = 2.0;

    /// Default number of octaves for the the Noise::module::Billow Noise
    /// module.
    const int DEFAULT_BILLOW_OCTAVE_COUNT = 6;

    /// Default persistence value for the the Noise::module::Billow Noise
    /// module.
    const double DEFAULT_BILLOW_PERSISTENCE = 0.5;

    /// Default Noise quality for the the Noise::module::Billow Noise module.
    const noise::NoiseQuality DEFAULT_BILLOW_QUALITY = QUALITY_STD;

    /// Default Noise seed for the the Noise::module::Billow Noise module.
    const int DEFAULT_BILLOW_SEED = 0;

    /// Maximum number of octaves for the the Noise::module::Billow Noise
    /// module.
    const int BILLOW_MAX_OCTAVE = 30;

    /// Noise module that outputs three-dimensional "billowy" Noise.
    ///
    /// @image html modulebillow.png
    ///
    /// This Noise module generates "billowy" Noise suitable for clouds and
    /// rocks.
    ///
    /// This Noise module is nearly identical to Noise::module::Perlin except
    /// this Noise module modifies each octave with an absolute-value
    /// function.  See the documentation of Noise::module::Perlin for more
    /// information.
    class Billow: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default frequency is set to
        /// Noise::module::DEFAULT_BILLOW_FREQUENCY.
        ///
        /// The default lacunarity is set to
        /// Noise::module::DEFAULT_BILLOW_LACUNARITY.
        ///
        /// The default number of octaves is set to
        /// Noise::module::DEFAULT_BILLOW_OCTAVE_COUNT.
        ///
        /// The default persistence value is set to
        /// Noise::module::DEFAULT_BILLOW_PERSISTENCE.
        ///
        /// The default seed value is set to
        /// Noise::module::DEFAULT_BILLOW_SEED.
        Billow ();

        /// Returns the frequency of the first octave.
        ///
        /// @returns The frequency of the first octave.
        double GetFrequency () const
        {
          return m_frequency;
        }

        /// Returns the lacunarity of the billowy Noise.
        ///
        /// @returns The lacunarity of the billowy Noise.
        /// 
        /// The lacunarity is the frequency multiplier between successive
        /// octaves.
        double GetLacunarity () const
        {
          return m_lacunarity;
        }

        /// Returns the quality of the billowy Noise.
        ///
        /// @returns The quality of the billowy Noise.
        ///
        /// See Noise::NoiseQuality for definitions of the various
        /// coherent-Noise qualities.
        noise::NoiseQuality GetNoiseQuality () const
        {
          return m_noiseQuality;
        }

        /// Returns the number of octaves that generate the billowy Noise.
        ///
        /// @returns The number of octaves that generate the billowy Noise.
        ///
        /// The number of octaves controls the amount of detail in the billowy
        /// Noise.
        int GetOctaveCount () const
        {
          return m_octaveCount;
        }

        /// Returns the persistence value of the billowy Noise.
        ///
        /// @returns The persistence value of the billowy Noise.
        ///
        /// The persistence value controls the roughness of the billowy Noise.
        double GetPersistence () const
        {
          return m_persistence;
        }

        /// Returns the seed value used by the billowy-Noise function.
        ///
        /// @returns The seed value.
        int GetSeed () const
        {
          return m_seed;
        }

		int GetSourceModuleCount() const override
		{
			return 0;
		}

		double GetValue(double x, double y, double z) const override;

        /// Sets the frequency of the first octave.
        ///
        /// @param frequency The frequency of the first octave.
        void SetFrequency (double frequency)
        {
          m_frequency = frequency;
        }

        /// Sets the lacunarity of the billowy Noise.
        ///
        /// @param lacunarity The lacunarity of the billowy Noise.
        /// 
        /// The lacunarity is the frequency multiplier between successive
        /// octaves.
        ///
        /// For best results, set the lacunarity to a number between 1.5 and
        /// 3.5.
        void SetLacunarity (double lacunarity)
        {
          m_lacunarity = lacunarity;
        }

        /// Sets the quality of the billowy Noise.
        ///
        /// @param noiseQuality The quality of the billowy Noise.
        ///
        /// See Noise::NoiseQuality for definitions of the various
        /// coherent-Noise qualities.
        void SetNoiseQuality (noise::NoiseQuality noiseQuality)
        {
          m_noiseQuality = noiseQuality;
        }

        /// Sets the number of octaves that generate the billowy Noise.
        ///
        /// @param octaveCount The number of octaves that generate the billowy
        /// Noise.
        ///
        /// @pre The number of octaves ranges from 1 to
        /// Noise::module::BILLOW_MAX_OCTAVE.
        ///
        /// @throw Noise::ExceptionInvalidParam An invalid parameter was
        /// specified; see the preconditions for more information.
        ///
        /// The number of octaves controls the amount of detail in the billowy
        /// Noise.
        ///
        /// The larger the number of octaves, the more time required to
        /// calculate the billowy-Noise value.
        void SetOctaveCount (int octaveCount)
        {
          if (octaveCount < 1 || octaveCount > BILLOW_MAX_OCTAVE) {
            throw noise::ExceptionInvalidParam ();
          }
          m_octaveCount = octaveCount;
        }

        /// Sets the persistence value of the billowy Noise.
        ///
        /// @param persistence The persistence value of the billowy Noise.
        ///
        /// The persistence value controls the roughness of the billowy Noise.
        ///
        /// For best results, set the persistence value to a number between
        /// 0.0 and 1.0.
        void SetPersistence (double persistence)
        {
          m_persistence = persistence;
        }

        /// Sets the seed value used by the billowy-Noise function.
        ///
        /// @param seed The seed value.
        void SetSeed (int seed)
        {
          m_seed = seed;
        }

      protected:

        /// Frequency of the first octave.
        double m_frequency;

        /// Frequency multiplier between successive octaves.
        double m_lacunarity;

        /// Quality of the billowy Noise.
        noise::NoiseQuality m_noiseQuality;

        /// Total number of octaves that generate the billowy Noise.
        int m_octaveCount;

        /// Persistence value of the billowy Noise.
        double m_persistence;

        /// Seed value used by the billowy-Noise function.
        int m_seed;

    };

    /// @}

    /// @}

    /// @}

  }

#endif
