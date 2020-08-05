project(opengl-drag-example)

cmake_minimum_required(VERSION 3.16)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Qpid CONFIG REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
include_directories(${Qpid_INCLUDE_DIRS})

add_executable(cube cube.cpp)
target_link_libraries(cube ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(cube-example-new cube-example-new.cpp)
target_link_libraries(cube-example-new ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(drag-example drag-example.cpp)
target_link_libraries(drag-example ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(drag-cube drag-cube.cpp)
target_link_libraries(drag-cube ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(drag-subscriber drag-subscriber.cpp)
target_link_libraries(drag-subscriber ${Qpid_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)

add_executable(drag-publisher drag-publisher.cpp)
target_link_libraries(drag-publisher ${Qpid_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
