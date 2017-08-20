project(PiQt)
cmake_minimum_required(VERSION 3.0.0)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:/Qt/Qt5.9.1/5.9.1/msvc2017_64)
else()
    set(CMAKE_PREFIX_PATH /Users/tuckerstrausbaugh/Qt/5.9.1/clang_64)
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

qt5_wrap_ui(ui MainWindow.ui)

set(SOURCE
    main.cpp
    MainWindow.cpp
    Display.cpp
)

set(HEADER
    MainWindow.h
    Display.h
)

include_directories(PiQt
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(PiQt
    ${SOURCE}
    ${HEADER}
	${ui}
)

target_link_libraries(PiQt
    Qt5::Widgets
    ${OPENGL_LIBRARIES}
)
