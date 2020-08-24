ADD_EXECUTABLE(ComplexPlanet complexplanet.cpp)
TARGET_LINK_LIBRARIES(ComplexPlanet PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(TextureGranite texturegranite.cpp)
TARGET_LINK_LIBRARIES(TextureGranite PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(TextureJade texturejade.cpp)
TARGET_LINK_LIBRARIES(TextureJade PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(TextureSky texturesky.cpp)
TARGET_LINK_LIBRARIES(TextureSky PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(TextureSlime textureslime.cpp)
TARGET_LINK_LIBRARIES(TextureSlime PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(TextureWood texturewood.cpp)
TARGET_LINK_LIBRARIES(TextureWood PRIVATE Noise Noise.Util)

ADD_EXECUTABLE(Worms worms.cpp)
TARGET_LINK_LIBRARIES(Worms PRIVATE Noise Noise.Util)