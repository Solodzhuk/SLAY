# Поиск всех файлов с исходным кодом автоматически
file(GLOB_RECURSE SOURCES *.hpp *.cpp)

# Тип библиотеки определяется опцией cmake "BUILD_SHARED_LIBS"
# По умолчанию STATIC
add_library(${PROJECT_NAME} ${SOURCES})

# Собирайте с этими опциями чтобы было больше предупреждений   ----там всё переписывать придётся(----
# target_compile_options(${PROJECT_NAME} PRIVATE
    # $<$<CXX_COMPILER_ID:GNU,CLANG>:-Wall -Wextra -pedantic -Wshadow -Wconversion -Wsign-conversion -Wno-missing-field-initializers>
    # $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)