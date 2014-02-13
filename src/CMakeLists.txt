cmake_minimum_required(VERSION 2.6.2)
if ("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
   cmake_policy(VERSION 2.8.4)
else ()
   cmake_policy(VERSION 2.6)
endif ()

set(PROJECT Manipulator)
project(${PROJECT})

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall")


find_package(CGAL COMPONENTS Qt4)
include(${CGAL_USE_FILE})

set(QT_USE_QTXML TRUE)
set(QT_USE_QTMAIN TRUE)
set(QT_USE_QTSCRIPT TRUE)
set(QT_USE_QTOPENGL TRUE)

find_package(Qt4)
include(${QT_USE_FILE})

set(SOURCES
    main.cpp
    mainwindow.cpp 
    polygon.cpp
    robot.cpp
    movableobject.cpp
    obstacles.cpp
    criticalcurves.cpp
    graph.cpp)
set(HEADERS
    mainwindow.h
    polygon.h
    robot.h
    movableobject.h
    obstacles.h
    criticalcurves.h
    graph.h)

set(EXECUTABLE manipulator)
add_executable(${EXECUTABLE} ${SOURCES} ${HEADERS})
add_to_cached_list(CGAL_EXECUTABLE_TARGETS ${EXECUTABLE})
# Link with Qt libraries
target_link_libraries(${EXECUTABLE} ${QT_LIBRARIES})
# Link with CGAL
target_link_libraries(${EXECUTABLE} ${CGAL_LIBRARIES}  ${CGAL_3RD_PARTY_LIBRARIES})

