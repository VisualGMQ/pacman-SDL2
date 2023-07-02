cmake_minimum_required(VERSION 3.10)

project(
    Pacman
    VERSION 1.0.0
    LANGUAGES CXX C
)

include(cmake/utility.cmake)
if (NOT EMSCRIPTEN)
    include(cmake/FindSDL2.cmake)
endif()
include(cmake/copydll.cmake)

IsMSVCBackend(is_msvc_backend)

set(GAME_NAME Pacman)

aux_source_directory(src SRC)
add_executable(${GAME_NAME} ${SRC})
target_include_directories(${GAME_NAME} PRIVATE include)
if (NOT EMSCRIPTEN)
    target_link_libraries(${GAME_NAME} PRIVATE SDL2)
endif()
target_compile_features(${GAME_NAME} PRIVATE cxx_std_17)

if (${is_msvc_backend})
    target_link_options(${GAME_NAME} PRIVATE $<IF:$<CONFIG:Release>,/SUBSYSTEM:WINDOWS,/SUBSYSTEM:CONSOLE>)
endif()

if (EMSCRIPTEN)
    message("-- build for wasm")
    CopyResForWASM(${GAME_NAME})    # NOTE: em++ work under ${CMAKE_BINARY_DIR}, so we copy resources dir to there for resources path correctly
    set(USE_SDL "-sUSE_SDL=2" )
    set(PRELOAD "--preload-file resources --use-preload-plugins")
    set(OTHER_FLAGS "-s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_SDL}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_SDL}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_SDL} ${PRELOAD} ${OTHER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

CopyDLL(${GAME_NAME})

install(PROGRAMS $<TARGET_FILE:${GAME_NAME}>
DESTINATION "${CMAKE_BINARY_DIR}/${GAME_NAME}-${PROJECT_VERSION}")
install(DIRECTORY resources
DESTINATION "${CMAKE_BINARY_DIR}/${GAME_NAME}-${PROJECT_VERSION}")
install(FILES $CACHE{SDL2_DYNAMIC_LIB_DIR}/SDL2.dll
DESTINATION "${CMAKE_BINARY_DIR}/${GAME_NAME}-${PROJECT_VERSION}")