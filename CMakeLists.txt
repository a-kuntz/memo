cmake_minimum_required(VERSION 3.15)

project(Memorizer)

## configuration ##############################################################

enable_testing()

## dependencies ###############################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Conan)

conan_cmake_run(REQUIRES
	gtest/1.8.1@bincrafters/stable
	BASIC_SETUP
	BUILD missing
)

find_package(GTest REQUIRED)

## components #################################################################

add_subdirectory(lib)
add_subdirectory(test)
