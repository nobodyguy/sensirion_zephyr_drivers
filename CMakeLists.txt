# SPDX-License-Identifier: Apache-2.0

# Point to this project's root directory.
set(SENSIRION_DRIVERS_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Sensirion drivers module root directory")

# Subdirectories
add_subdirectory(drivers)

# Include headers
zephyr_include_directories(drivers)