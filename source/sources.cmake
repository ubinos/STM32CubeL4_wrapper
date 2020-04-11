if(INCLUDE__STM32CUBEL4)

	get_filename_component(_tmp_source_dir "${STM32CUBEL4__BASE_DIR}" ABSOLUTE)

	include_directories(${_tmp_source_dir}/Drivers/CMSIS/Include)
	include_directories(${_tmp_source_dir}/Drivers/CMSIS/Device/ST/STM32L4xx/Include)
	include_directories(${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Inc)
	include_directories(${_tmp_source_dir}/Drivers/BSP/Components)
	include_directories(${_tmp_source_dir}/Drivers/BSP/Components/Common)
	include_directories(${_tmp_source_dir}/Utilities)
	include_directories(${_tmp_source_dir}/Utilities/CPU)
	include_directories(${_tmp_source_dir}/Utilities/Fonts)
	include_directories(${_tmp_source_dir}/Utilities/Log)

	if(STM32CUBEL4__USE_HAL_DRIVER)
	
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dfsdm.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c)
		set_source_files_properties(${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c PROPERTIES COMPILE_FLAGS -O3)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c)
		
		if(UBINOS__BSP__BOARD_MODEL STREQUAL "STM32L475EIOT01")
		
			include_directories(${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01)

			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/hts221)
			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/lps22hb)
			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/lis3mdl)
			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/lsm6dsl)

			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_accelero.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_gyro.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_hsensor.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_magneto.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_psensor.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_qspi.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_tsensor.c)
			
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/hts221/hts221.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lis3mdl/lis3mdl.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lps22hb/lps22hb.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lsm6dsl/lsm6dsl.c)

		else()
		
			message(FATAL_ERROR "Unsupported UBINOS__BSP__BOARD_MODEL")
		
		endif()
	
	endif(STM32CUBEL4__USE_HAL_DRIVER)
	
	if(STM32CUBEL4__USE_FULL_LL_DRIVER)
	
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.c)
	
	endif(STM32CUBEL4__USE_FULL_LL_DRIVER)

endif(INCLUDE__STM32CUBEL4)

