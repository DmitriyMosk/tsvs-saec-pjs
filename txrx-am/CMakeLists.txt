cmake_minimum_required(VERSION 3.10)

project(txrx_am LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

### Setup include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

### Link required libraries
find_package(PkgConfig REQUIRED) 

if(PkgConfig_FOUND)
    message(STATUS "PkgConfig found")

    # Find SoapySDR
    pkg_check_modules(SOAPYSDR REQUIRED SoapySDR)
    include_directories(${SOAPYSDR_INCLUDE_DIRS})
    link_directories(${SOAPYSDR_LIBRARY_DIRS})
    add_definitions(${SOAPYSDR_CFLAGS_OTHER})

    # Find HackRF
    pkg_check_modules(HACKRF REQUIRED libhackrf)
    include_directories(${HACKRF_INCLUDE_DIRS})
    link_directories(${HACKRF_LIBRARY_DIRS})
    add_definitions(${HACKRF_CFLAGS_OTHER})
endif(PkgConfig_FOUND)

file(GLOB_RECURSE MY_LD_FILES_buffer src/buffer/*.cpp) 
file(GLOB_RECURSE MY_LD_FILES_device src/device/*.cpp) 
file(GLOB_RECURSE MY_LD_FILES_phys   src/phy/*.cpp)

set(SOME_LD 
    ${MY_LD_FILES_buffer}
    ${MY_LD_FILES_device}
    ${MY_LD_FILES_phys}
)

message(STATUS "Include files")
foreach(SOME_LD_L ${SOME_LD})
    message(STATUS ${SOME_LD_L})
endforeach()

add_executable(${PROJECT_NAME} 
    ${SOME_LD}
    src/app/txrx.cpp
)
target_link_libraries(${PROJECT_NAME} ${SOAPYSDR_LIBRARIES} ${HACKRF_LIBRARIES})
