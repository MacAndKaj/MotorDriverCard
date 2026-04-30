####################################################
# Copyright (c) 2024 M. Kajdak. All rights reserved.
####################################################

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(ut)
endif()
