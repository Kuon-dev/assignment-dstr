
# Add the subdirectories for each component of the project
#add_subdirectory(controllers)
#add_subdirectory(models)
#add_subdirectory(modules)
#add_subdirectory(views)

# Add the executable for the main program
#add_executable(main main.cpp)

# Link the main program to the libraries
#target_link_libraries(main models views modules)
cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 11)

# Add subdirectories for each component of the project
add_subdirectory(src/controllers)
add_subdirectory(src/models)
add_subdirectory(src/modules)
add_subdirectory(src/views)

# Add an executable for the main program
add_executable(main src/main.cpp)

# Link the main program to the libraries
target_link_libraries(main models views modules)

# Add subdirectories for the views component
#add_subdirectory(src/views/admin)
#add_subdirectory(src/views/user)

# Link the views component to the libraries
#target_link_libraries(views admin user)

target_sources(controllers PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/controllers/FavouritesController.cpp")
target_sources(controllers PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/controllers/FeedbackController.cpp")
target_sources(controllers PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/controllers/MemberController.cpp")
target_sources(controllers PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/controllers/UniversityController.cpp")

target_sources(models PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/models/Favourites.cpp")
target_sources(models PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/models/University.cpp")
target_sources(models PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/models/Feedback.cpp")
target_sources(models PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/models/Member.cpp")

# Add the ViewMainMenu.cpp file to the views library
target_sources(views PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/views/ViewMainMenu.cpp")


add_custom_command(TARGET main POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
	   ${CMAKE_SOURCE_DIR}/Database/Universities.csv
	   $<TARGET_FILE_DIR:main>/Database/Universities.csv)

add_custom_command(TARGET main POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
	   ${CMAKE_SOURCE_DIR}/Database/FavUni.csv
	   $<TARGET_FILE_DIR:main>/Database/FavUni.csv)

add_custom_command(TARGET main POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
	   ${CMAKE_SOURCE_DIR}/Database/Users.csv
	   $<TARGET_FILE_DIR:main>/Database/Users.csv)

add_custom_command(TARGET main POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
	   ${CMAKE_SOURCE_DIR}/Database/FavUni.csv
	   $<TARGET_FILE_DIR:main>/Database/FeedbackDatabase.csv)

