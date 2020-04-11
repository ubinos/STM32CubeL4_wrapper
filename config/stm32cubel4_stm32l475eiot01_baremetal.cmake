include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32l475eiot01_baremetal.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/stm32cubel4.cmake)

####

get_filename_component(_tmp_source_dir "${STM32CUBEL4__BASE_DIR}" ABSOLUTE)

include_directories(${_tmp_source_dir}/Projects/B-L475E-IOT01A/Examples/BSP/Inc)


