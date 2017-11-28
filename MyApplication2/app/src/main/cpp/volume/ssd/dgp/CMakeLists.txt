SET(dgp_sources 
    BBox.cpp
    BBox.h
    inttypes.h
    PointXYZ.hpp
    PointXYZNormal.hpp
    PointXYZRGB.hpp
    PointXYZRGBNormal.hpp
    ply.c
    ply.h
    PointReader.hpp
    PointReader.inl
    PlyWriter.hpp
    PlyWriter.inl
)
ADD_LIBRARY(dgp ${dgp_sources})
