cmake_minimum_required(VERSION 3.21.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MINIMUM_REQUIRED_VERSION ON)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# Fetch dependencies
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(	json
	GIT_REPOSITORY	https://github.com/nlohmann/json
	GIT_TAG		v3.10.1
	GIT_PROGRESS	FALSE
	)

message("Fetching JSON...")
FetchContent_MakeAvailable(json)
include_directories(${json_SOURCE_DIR}/single_include/nlohmann)
message("Fetching JSON - complete")

project(Login_System VERSION 1.0)
set(SRC_FILES  src/loginSystem.cpp src/user.cpp src/userInput.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES} )
#target_link_libraries(${PROJECT_NAME} json wsock32 ws2_32)