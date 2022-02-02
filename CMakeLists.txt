cmake_minimum_required(VERSION 3.20)
project(CurvePlotter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets)
if (NOT Qt6_FOUND)
    set(QT_VERSION 5)
else ()
    set(QT_VERSION 6)
endif ()

find_package(Qt${QT_VERSION}Charts)
set(REQUIRED_LIBS Core Gui Widgets )
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Charts)

add_executable(CurvePlotter main.cpp src/CurvePlotterWindow.cpp include/CurvePlotterWindow.hpp include/BaseFunctions.hpp src/CurvePlotterSettings.cpp include/CurvePlotterSettings.hpp resources.qrc src/AboutCurvePlotter.cpp include/AboutCurvePlotter.hpp src/CustomFunctionDialog.cpp include/CustomFunctionDialog.hpp)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wunused -Wa,-mbig-obj")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

include_directories(${CurvePlotter_SOURCE_DIR}/include ${CurvePlotter_SOURCE_DIR}/lib)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
