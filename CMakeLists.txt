cmake_minimum_required(VERSION 3.16)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 17)

# cartella include con i .h
include_directories(include)

# --- Main executable ---
add_executable(main
        src/main.cpp
        src/GestoreTransazioni.cpp
        src/Transazione.cpp
        src/Ingresso.cpp
        src/Uscita.cpp
)

# metti main in bin/
set_target_properties(main PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# --- GoogleTest setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Test executable ---
add_executable(tests
        tests/Test.cpp
        src/GestoreTransazioni.cpp
        src/Transazione.cpp
        src/Ingresso.cpp
        src/Uscita.cpp
)

set_target_properties(tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
