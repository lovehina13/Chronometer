add_library(Chronometer SHARED Chronometer.cpp)

target_include_directories(Chronometer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS Chronometer EXPORT ${CMAKE_PROJECT_NAME}Targets DESTINATION lib)
# install(FILES ${CMAKE_SOURCE_DIR}/include/MyProject/Chronometer/Chronometer.h
#     DESTINATION include/MyProject/Chronometer)
