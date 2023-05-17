cmake_minimum_required(VERSION 3.8.0)

set(PATCH_VERSION 1 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)

# cli
add_executable(${PROJECT_NAME} ${SRC_H} ${SRC_CPP} main.cpp)

# deb
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT example@example.com)
include (CPack)
