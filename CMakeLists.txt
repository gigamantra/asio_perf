cmake_minimum_required(VERSION 2.8)

include_directories(./src)


# Include headers and libs via environment variables
# so that boost is available if possible.
# If you are unable to do so - modify the following
# with the path relevant to your environment.
include_directories(D:/usr/local/include)
link_directories(D:/usr/local/lib/boost)
	
#Main "solution"
project(asio_perf)

# Initialize CXXFLAGS.
set (PROJECT_TYPE "CXX")
if(CMAKE_COMPILER_IS_GNUCC)
set(CMAKE_CXX_FLAGS                "-std=c++11")
endif()


#Main projects
# lib_common project
file(GLOB COMMON_SOURCE src/lib_common/*.*) 
add_library(lib_common STATIC ${COMMON_SOURCE})
install(TARGETS lib_common DESTINATION lib)

# rest service project
file(GLOB REST_SVC_SOURCE src/rest_svc/*.*) 
add_executable(rest_svc ${REST_SVC_SOURCE})
target_link_libraries(rest_svc lib_common)
install(TARGETS rest_svc DESTINATION bin)

# rest client project
file(GLOB REST_CLIENT_SOURCE src/rest_client/*.*) 
add_executable(rest_client ${REST_CLIENT_SOURCE})
target_link_libraries(rest_client lib_common)
install(TARGETS rest_client DESTINATION bin)


#test projects
# lib_common project
file(GLOB TEST_COMMON_SOURCE test/lib_common/*.*) 
add_executable(test_lib_common ${TEST_COMMON_SOURCE})
target_link_libraries(test_lib_common lib_common)
install(TARGETS test_lib_common DESTINATION lib)

# Rest service project
file(GLOB TEST_REST_SVC_SOURCE test/rest_svc/*.*)
add_executable(test_rest_svc ${TEST_REST_SVC_SOURCE})
install(TARGETS test_rest_svc DESTINATION bin)

# Rest client project
file(GLOB TEST_REST_CLIENT_SOURCE test/rest_client/*.*)
add_executable(test_rest_client ${TEST_REST_CLIENT_SOURCE})
install(TARGETS test_rest_client DESTINATION bin)
