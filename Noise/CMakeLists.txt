ADD_LIBRARY(Noise
        Source/noisegen.cpp
        Source/latlon.cpp

        Source/module/abs.cpp
        Source/module/billow.cpp
        Source/module/cache.cpp
        Source/module/clamp.cpp
        Source/module/curve.cpp
        Source/module/displace.cpp
        Source/module/invert.cpp
        Source/module/min.cpp
        Source/module/multiply.cpp
        Source/module/power.cpp
        Source/module/rotatepoint.cpp
        Source/module/scalepoint.cpp
        Source/module/spheres.cpp
        Source/module/translatepoint.cpp
        Source/module/voronoi.cpp
        Source/module/add.cpp
        Source/module/blend.cpp
        Source/module/checkerboard.cpp
        Source/module/const.cpp
        Source/module/cylinders.cpp
        Source/module/exponent.cpp
        Source/module/max.cpp
        Source/module/modulebase.cpp
        Source/module/perlin.cpp
        Source/module/ridgedmulti.cpp
        Source/module/scalebias.cpp
        Source/module/select.cpp
        Source/module/terrace.cpp
        Source/module/turbulence.cpp

        Source/model/cylinder.cpp
        Source/model/line.cpp
        Source/model/plane.cpp
        Source/model/sphere.cpp
        )

# Set the compiler mark to C++17
SET_PROPERTY(TARGET Noise PROPERTY CXX_STANDARD 17)
TARGET_INCLUDE_DIRECTORIES(Noise
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:/Include/>
        )