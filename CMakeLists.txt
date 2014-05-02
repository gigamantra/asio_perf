cmake_minimum_required(VERSION 2.8)


############################################
# General Environment configuration
############################################


# Root directory for our project headers
include_directories(./src)


# Include the boost headers and libs
# update according to your system
IF(WIN32)
	include_directories(D:/usr/local/include)
	link_directories(D:/usr/local/lib/boost)
ELSE()
	include_directories(/usr/local/include)
	link_directories(/usr/local/lib)
ENDIF()


#Main "solution"
project(asio_perf)


#For GCC we need to set a few things like c++11 support, 64 bit arch
#On windows we just need to use the appropriate generator for cmake
if(CMAKE_COMPILER_IS_GNUCC)
	# Initialize CXXFLAGS.
	set (PROJECT_TYPE "CXX")
	set(CMAKE_CXX_FLAGS "-std=c++11 -m64")
endif()


###############################################
#Main projects
###############################################


# lib_common project
file(GLOB COMMON_SOURCE src/lib_common/*.*) 
add_library(lib_common STATIC ${COMMON_SOURCE})
install(TARGETS lib_common DESTINATION lib)


# rest service project
file(GLOB REST_SVC_SOURCE src/rest_svc/*.*) 
add_executable(rest_svc ${REST_SVC_SOURCE})

if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(rest_svc lib_common libboost_system.a)
else()
	target_link_libraries(rest_svc lib_common)
endif()

install(TARGETS rest_svc DESTINATION bin)


# rest client project
file(GLOB REST_CLIENT_SOURCE src/rest_client/*.*) 
add_executable(rest_client ${REST_CLIENT_SOURCE})

if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(rest_client lib_common libboost_system.a)
else()
	target_link_libraries(rest_client lib_common)
endif()

install(TARGETS rest_client DESTINATION bin)


#########################################
#test projects
#########################################

# lib_common test harness
file(GLOB TEST_COMMON_SOURCE test/lib_common/*.*) 
add_executable(test_lib_common ${TEST_COMMON_SOURCE})

if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_lib_common lib_common libboost_system.a libboost_test_exec_monitor.a)
else()
	target_link_libraries(test_lib_common lib_common)
endif()

install(TARGETS test_lib_common DESTINATION lib)


# Rest service test harness
file(GLOB TEST_REST_SVC_SOURCE test/rest_svc/*.*)
add_executable(test_rest_svc ${TEST_REST_SVC_SOURCE})

if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_rest_svc lib_common libboost_system.a libboost_test_exec_monitor.a)
else()
	target_link_libraries(test_rest_svc lib_common)
endif()

install(TARGETS test_rest_svc DESTINATION bin)


# Rest client project
file(GLOB TEST_REST_CLIENT_SOURCE test/rest_client/*.*)
add_executable(test_rest_client ${TEST_REST_CLIENT_SOURCE})

if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_rest_client lib_common libboost_system.a libboost_test_exec_monitor.a)
else()
	target_link_libraries(test_rest_client lib_common)
endif()

install(TARGETS test_rest_client DESTINATION bin)
