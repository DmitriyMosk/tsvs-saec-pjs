cmake_minimum_required(VERSION 3.20)
project(txrx_am LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка путей
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
include_directories(
    ${INCLUDE_DIR}
    ${INCLUDE_DIR}/buffer/impl
)

# Поиск зависимостей
find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)

if(PkgConfig_FOUND)
    pkg_check_modules(SOAPYSDR REQUIRED SoapySDR)
    include_directories(${SOAPYSDR_INCLUDE_DIRS})
    link_directories(${SOAPYSDR_LIBRARY_DIRS})

    pkg_check_modules(HACKRF REQUIRED libhackrf)
    include_directories(${HACKRF_INCLUDE_DIRS})
    link_directories(${HACKRF_LIBRARY_DIRS})
endif()

# Библиотека буфера
add_library(buffer STATIC
    src/buffer/DoubleBuffer.cpp # Файл с явными инстанциациями
)

# Исполняемый файл
add_executable(${PROJECT_NAME}
    src/app/txrx.cpp
    ${MY_LD_FILES_device}
    ${MY_LD_FILES_phys}
)

# Линковка
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    buffer
    fmt::fmt
    ${SOAPYSDR_LIBRARIES}
    ${HACKRF_LIBRARIES}
)

# Явные инстанциации
target_compile_definitions(buffer PRIVATE
    -DTPL_EXPLICIT_INSTANTIATION
)
