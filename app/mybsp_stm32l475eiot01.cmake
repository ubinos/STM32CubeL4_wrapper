#
# Copyright (c) 2021 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32l475eiot01.cmake)

include(${PROJECT_LIBRARY_DIR}/stm32cubel4_wrapper/config/stm32cubel4.cmake)

####

set(INCLUDE__APP TRUE)
set(APP__NAME "mybsp")

get_filename_component(_tmp_source_dir "${CMAKE_CURRENT_LIST_DIR}/mybsp" ABSOLUTE)

file(GLOB_RECURSE _tmp_sources
    "${_tmp_source_dir}/*.c"
    "${_tmp_source_dir}/*.cpp"
    "${_tmp_source_dir}/*.S"
    "${_tmp_source_dir}/*.s")

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_sources})

get_filename_component(_tmp_source_dir "${STM32CUBEL4__BASE_DIR}/Projects/B-L475E-IOT01A/Examples/BSP" ABSOLUTE)

include_directories(${_tmp_source_dir}/Inc)

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Src/qspi.c)
set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Src/sensors.c)

get_filename_component(_tmp_source_dir "${STM32CUBEL4__BASE_DIR}" ABSOLUTE)

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_qspi.c)
set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.c)


