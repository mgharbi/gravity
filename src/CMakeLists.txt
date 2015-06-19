include_directories(${inc})

INCLUDE_DIRECTORIES(${IRRLICHT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

set(gravity_sources
    main.cpp
)

set(gravit_resources
)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(
    gravity
    MACOSX_BUNDLE
    ${gravity_sources}
    ${gravit_resources}
)

target_link_libraries(gravity
    ${Boost_LIBRARIES}
    ${IRRLICHT_LIBRARY}
    ${OPENGL_LIBRARIES} 
    ${OSX_LIBRARIES}
)
