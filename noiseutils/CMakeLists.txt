ADD_LIBRARY(Noise.Util noiseutils.cpp)

TARGET_LINK_LIBRARIES(Noise.Util PUBLIC Noise)
TARGET_INCLUDE_DIRECTORIES(Noise.Util
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:/include/>
        )