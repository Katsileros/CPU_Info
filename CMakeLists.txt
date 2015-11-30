MESSAGE( STATUS )
MESSAGE( STATUS "==============CPUINFO CMAKELISTS.TXT==============")
MESSAGE( STATUS )

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

PROJECT(cpu_info)

MESSAGE( STATUS ${LIB_INCLUDE_DIR} )

add_executable( cpu_info cpuinfo.cpp )

MESSAGE( STATUS )
MESSAGE( STATUS "==============CPUINFO CMAKELISTS.TXT EXITING==============")
MESSAGE( STATUS )
