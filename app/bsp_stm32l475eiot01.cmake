#
# Copyright (c) 2021 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "bsp", "build_type": "cmake_ubinos", "app": true}

set_cache(UBINOS__UBIK__TICK_TYPE "RTC" STRING)

set_cache(UBINOS__BSP__DTTY_TYPE "EXTERNAL" STRING)
set_cache(STM32CUBEL4__DTTY_STM32_UART_ENABLE TRUE BOOL)
set_cache(STM32CUBEL4__USE_HAL_QSPI TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32l475eiot01.cmake)
include(${PROJECT_LIBRARY_DIR}/STM32CubeL4_wrapper/config/stm32cubel4.cmake)
include(${PROJECT_LIBRARY_DIR}/STM32CubeL4_extension/config/stm32cubel4_extension.cmake)

####

set(INCLUDE__APP TRUE)
set(APP__NAME "bsp")

get_filename_component(_tmp_source_dir "${CMAKE_CURRENT_LIST_DIR}/bsp" ABSOLUTE)

include_directories(${_tmp_source_dir}/arch/arm/cortexm/stm32l475eiot01/Inc)

file(GLOB_RECURSE _tmp_sources
    "${_tmp_source_dir}/*.c"
    "${_tmp_source_dir}/*.cpp"
    "${_tmp_source_dir}/*.cc"
    "${_tmp_source_dir}/*.S")

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_sources})

get_filename_component(_tmp_source_dir "${STM32CUBEL4__BASE_DIR}/Projects/B-L475E-IOT01A/Examples/BSP" ABSOLUTE)

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Src/qspi.c)
set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_source_dir}/Src/sensors.c)

