
# List all the source files in the current directory
file(GLOB SOURCES "*.cpp")

# Define a library target for the controllers module
add_library(controllers STATIC ${SOURCES})

# Add the include directories for the module
target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../models)
target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../views)
target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules)

# Link the module against the required libraries
target_link_libraries(controllers PUBLIC models views modules)
