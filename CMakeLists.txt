cmake_minimum_required(VERSION 3.13)
project(m17test)

add_subdirectory("libcorrect/")

file(GLOB_RECURSE SRC "src/*.cpp" "lib/*.cpp")

add_executable(m17test ${SRC})

target_include_directories(m17test PRIVATE "lib/")
target_include_directories(m17test PUBLIC "libcorrect/include")
target_link_libraries(m17test PUBLIC correct_static)

if(WIN32)
    target_compile_options(m17test PRIVATE /std:c++17)

    target_link_directories(m17test PRIVATE "C:/Program Files/codec2/lib")
    target_include_directories(m17test PRIVATE "C:/Program Files/codec2/include/")
    target_link_libraries(m17test PRIVATE libcodec2)
else()
    target_compile_options(m17test PRIVATE -Wall -pedantic)
endif()

# cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"