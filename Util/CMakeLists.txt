ADD_LIBRARY(Noise.Util
        noiseutils.cpp
        Source/GradientColor.cpp
        Source/Image.cpp
        Source/NoiseMap.cpp)

# Set the compiler mark to C++17
SET_PROPERTY(TARGET Noise.Util PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES(Noise.Util PUBLIC Noise)
TARGET_INCLUDE_DIRECTORIES(Noise.Util PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:/Include/>
        )