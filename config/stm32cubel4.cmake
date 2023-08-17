set(INCLUDE__STM32CUBEL4 TRUE)
set(PROJECT_UBINOS_LIBRARIES ${PROJECT_UBINOS_LIBRARIES} stm32cubel4_wrapper)

set_cache_default(STM32CUBEL4__BASE_DIR "${PROJECT_LIBRARY_DIR}/stm32cubel4_v01.15.00" STRING "stm32cubel4 project base dir")

set_cache_default(STM32CUBEL4__USE_HAL_DRIVER TRUE BOOL "Use STM32 Cube L4 HAL Driver")

set_cache_default(STM32CUBEL4__USE_FULL_LL_DRIVER FALSE BOOL "Use STM32 Cube L4 Full Low Level Driver")

set_cache_default(STM32CUBEL4__USE_STM32L475_DISCOVERY FALSE BOOL "Use STM32 Cube L4 STM32L475 Discovery")

set_cache_default(STM32CUBEL4__USE_HAL_QSPI FALSE BOOL "Use STM32 Cube L4 HAL QSPI Driver")

set_cache_default(STM32CUBEL4__USE_HAL_USBD FALSE BOOL "Use STM32 Cube L4 HAL USB Device Driver")

####

set(_tmp_all_flags "")

if(STM32CUBEL4__USE_HAL_DRIVER)
    set(_tmp_all_flags "${_tmp_all_flags} -DUSE_HAL_DRIVER")
endif()

if(STM32CUBEL4__USE_FULL_LL_DRIVER)
    set(_tmp_all_flags "${_tmp_all_flags} -DUSE_FULL_LL_DRIVER")
endif()

if(STM32CUBEL4__USE_STM32L475_DISCOVERY)
    set(_tmp_all_flags "${_tmp_all_flags} -DUSE_STM32L475_DISCOVERY")
endif()

set(CMAKE_ASM_FLAGS "${_tmp_all_flags} ${CMAKE_ASM_FLAGS}")
set(CMAKE_C_FLAGS   "${_tmp_all_flags} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${_tmp_all_flags} ${CMAKE_CXX_FLAGS}")


