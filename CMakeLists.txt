cmake_minimum_required(VERSION 3.20)
project(CurvePlotter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Charts)
set(QT_VERSION 5)

set(REQUIRED_LIBS Core Gui Widgets )
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt5::Charts)

add_executable(CurvePlotter main.cpp src/CurvePlotterWindow.cpp include/CurvePlotterWindow.hpp include/BaseFunctions.hpp src/CurvePlotterSettings.cpp include/CurvePlotterSettings.hpp resources.qrc src/AboutCurvePlotter.cpp include/AboutCurvePlotter.hpp)

include_directories(${CurvePlotter_SOURCE_DIR}/include)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

