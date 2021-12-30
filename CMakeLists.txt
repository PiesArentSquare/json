cmake_minimum_required(VERSION 3.5)

project(Pson)

add_library(pson SHARED
    src/jsonobject.cpp
    src/jsonarray.cpp
    src/jsonvalue.cpp
    src/json.cpp
    src/jsonutil.cpp
    src/jsonserializer.cpp
    src/jsonparser.cpp
)
target_compile_features(pson PUBLIC cxx_std_17)
target_include_directories(pson PUBLIC include)

# add_executable(tests tests/tests.cpp )
# target_include_directories(tests PUBLIC include)
# target_link_libraries(tests libpson)
