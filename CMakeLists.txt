cmake_minimum_required(VERSION 3.24)
project(lang)

set(CMAKE_CXX_STANDARD 17)

add_executable(lang src/main.cpp src/FileUtils.h src/Parser.cpp src/Parser.h src/Interpreter.cpp src/Interpreter.h src/InterpreterBuilder.cpp src/InterpreterBuilder.h)

set_target_properties(lang PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        )