
# Add the subdirectories for each component of the project
add_subdirectory(controllers)
add_subdirectory(models)
add_subdirectory(modules)
add_subdirectory(views)

# Add the executable for the main program
add_executable(main main.cpp)

# Link the main program to the libraries
target_link_libraries(main models views modules)
