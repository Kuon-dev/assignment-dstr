file(GLOB SOURCES "*.cpp")

# Define a library target for the controllers module
add_library(models STATIC ${SOURCES})

# Add the include directories for the module
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../controllers)
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../views)
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules)

# Link the module against the required libraries
target_link_libraries(models PUBLIC controllers views modules)
