include_directories(${inc})

INCLUDE_DIRECTORIES(${IRRLICHT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})

set(gravity_sources
    main.cpp
)

set(gravity_resources
    ${res}/spaceship.zip
    ${res}/Earth.zip
)

SET_SOURCE_FILES_PROPERTIES(
    ${gravity_resources}
    PROPERTIES
    HEADER_FILE_ONLY ON
    MACOSX_PACKAGE_LOCATION Resources/
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
    ${BULLET_LIBRARIES}
    ${OPENGL_LIBRARIES} 
    ${OSX_LIBRARIES}
)
