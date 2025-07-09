cmake_minimum_required(VERSION 3.15)
project(demo CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# 1. nlohmann/json 라이브러리 추가
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# 2. cpp-httplib 라이브러리 추가
FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG v0.15.3
)
FetchContent_MakeAvailable(httplib)


add_executable(demo main.cpp)

# 3. 라이브러리 링크
target_link_libraries(demo PRIVATE httplib::httplib nlohmann_json::nlohmann_json)