find_package(Boost.Hana QUIET)
if (NOT Boost.Hana_FOUND)
    find_package(Boost 1.61.0 REQUIRED)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/jegpTargets.cmake)
