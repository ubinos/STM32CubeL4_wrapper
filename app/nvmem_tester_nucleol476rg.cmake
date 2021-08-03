#
# Copyright (c) 2021 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN  0x08000000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH  0x000E0000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN 0x080E0000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH 0x00020000 STRING)

set_cache(UBINOS__UBIDRV__INCLUDE_NVMEM TRUE BOOL)

set_cache(UBINOS__UBIK__TICK_TYPE "RTC" STRING)

set_cache(UBINOS__BSP__DTTY_TYPE "EXTERNAL" STRING)
set_cache(STM32CUBEL4__DTTY_STM32_UART_ENABLE TRUE BOOL)

set_cache(UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER "3" STRING)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nucleol476rg.cmake)
include(${PROJECT_LIBRARY_DIR}/stm32cubel4_wrapper/config/stm32cubel4.cmake)
include(${PROJECT_LIBRARY_DIR}/stm32cubel4_extension/config/stm32cubel4_extension.cmake)

####

set(INCLUDE__APP TRUE)
set(APP__NAME "nvmem_tester")

get_filename_component(_tmp_source_dir "${CMAKE_CURRENT_LIST_DIR}/nvmem_tester" ABSOLUTE)

file(GLOB_RECURSE _tmp_sources
    "${_tmp_source_dir}/*.c"
    "${_tmp_source_dir}/*.cpp"
    "${_tmp_source_dir}/*.S"
    "${_tmp_source_dir}/*.s")

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_sources})

include_directories(${_tmp_source_dir}/arch/arm/cortexm/nucleol476rg/Inc)

