file(GLOB SOURCES "*.cpp")

# Define a library target for the controllers module
add_library(views STATIC ${SOURCES})

# Add the include directories for the module
target_include_directories(views PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../controllers)
target_include_directories(views PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../modules)
target_include_directories(views PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../models)

# Link the module against the required libraries
target_link_libraries(views PUBLIC controllers modules models)
