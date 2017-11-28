SET(ssd_sources
    ../isosurface/MarchingCubes.hpp
    ../isosurface/MarchingCubes.inl
    ../isosurface/DualMarchingCubes.hpp
    ../isosurface/DualMarchingCubes.inl
    ../isosurface/MAT.hpp
    ../isosurface/MAT.inl
    HRTimer.hpp
    Settings.hpp
    run_ssd.hpp
    ssd_recon.cpp
    test.cpp
)   
ADD_LIBRARY(ssd_recon SHARED ${ssd_sources})
TARGET_LINK_LIBRARIES(ssd_recon dgp octree)
INSTALL(TARGETS ssd_recon DESTINATION ${CMAKE_INSTALL_PREFIX})
