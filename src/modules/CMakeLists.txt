file(GLOB SOURCES "*.cpp")

# Define a library target for the controllers module
add_library(modules STATIC ${SOURCES})

# Add the include directories for the module
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../controllers)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../views)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../models)

# Link the module against the required libraries
target_link_libraries(modules PUBLIC controllers views models)
