include_directories(${inc})

INCLUDE_DIRECTORIES(${IRRLICHT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

set(gravity_src
    main.cpp
)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(gravity
    ${gravity_src}
)

target_link_libraries(gravity
    ${Boost_LIBRARIES}
    ${IRRLICHT_LIBRARY}
    ${OPENGL_LIBRARIES} 
    ${OSX_LIBRARIES}
)
