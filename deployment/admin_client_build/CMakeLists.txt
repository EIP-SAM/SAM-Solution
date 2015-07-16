##
## CMakeLists.txt for SAM-Solution
##
## Made by Nicolas Chauvin
## Email <chauvin.nico@gmail.com>
##
## Started on  Wed Jul 15 01:11:51 2015 Nicolas Chauvin
## Last update Thu Jul 16 21:05:16 2015 Nicolas Chauvin
##

cmake_minimum_required(VERSION 2.8.11)

project(SAM-Solution)
set(EXECUTABLE_NAME admin_client)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Set source directories
set(	PROJECT_ROOT_DIR	../.. )
set(	SOURCE_ROOT_DIR		${PROJECT_ROOT_DIR}/source )
set(	COMMON_DIR		${SOURCE_ROOT_DIR}/common )
set(	ADMIN_CLIENT_DIR	${SOURCE_ROOT_DIR}/admin_client )

# Set include directories
include_directories(${COMMON_DIR})

# Tell CMake to create the executable
add_executable(

	# Executable name
	${EXECUTABLE_NAME}

	# Source files
	${ADMIN_CLIENT_DIR}/main.cpp
)

# Use the Widgets module from Qt 5.
target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets)
