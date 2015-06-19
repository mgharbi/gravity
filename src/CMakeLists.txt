include_directories(${inc})

INCLUDE_DIRECTORIES(${IRRLICHT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

set(gravity_sources
    main.cpp
)

set(gravity_resources
    ${res}/map-20kdm2.pk3
)
SET_SOURCE_FILES_PROPERTIES(
    ${gravity_resources}
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(
    gravity
    MACOSX_BUNDLE
    ${gravity_sources}
    ${gravity_resources}
)

target_link_libraries(gravity
    ${Boost_LIBRARIES}
    ${IRRLICHT_LIBRARY}
    ${OPENGL_LIBRARIES} 
    ${OSX_LIBRARIES}
)
