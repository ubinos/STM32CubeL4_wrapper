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
	if(STM32CUBEL4__USE_HAL_USBD)
		include_directories(${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc)
		include_directories(${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc)
	endif(STM32CUBEL4__USE_HAL_USBD)

	if(STM32CUBEL4__USE_HAL_DRIVER)

		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c)
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
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_lptim.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pcd.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pcd_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_fmc.c)
		if(STM32CUBEL4__USE_HAL_USBD)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usb.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c)
		endif(STM32CUBEL4__USE_HAL_USBD)

		if(STM32CUBEL4__USE_HAL_QSPI)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.c)
		endif(STM32CUBEL4__USE_HAL_QSPI)

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
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_tsensor.c)
			if(STM32CUBEL4__USE_HAL_QSPI)
				set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_qspi.c)
			endif(STM32CUBEL4__USE_HAL_QSPI)

			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/hts221/hts221.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lis3mdl/lis3mdl.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lps22hb/lps22hb.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/lsm6dsl/lsm6dsl.c)

		elseif(UBINOS__BSP__BOARD_MODEL STREQUAL "STM32L476GEVAL")

			include_directories(${_tmp_source_dir}/Drivers/BSP/STM32L476G_EVAL)

			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/stmpe1600)
			include_directories(${_tmp_source_dir}/Drivers/BSP/Components/stmpe811)

			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/STM32L476G_EVAL/stm32l476g_eval.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/STM32L476G_EVAL/stm32l476g_eval_io.c)

			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/stmpe1600/stmpe1600.c)
			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/Components/stmpe811/stmpe811.c)

		elseif(UBINOS__BSP__BOARD_MODEL STREQUAL "NUCLEOL476RG")

			include_directories(${_tmp_source_dir}/Drivers/BSP/STM32L4xx_Nucleo)

			set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/BSP/STM32L4xx_Nucleo/stm32l4xx_nucleo.c)

		else()

			message(FATAL_ERROR "Unsupported UBINOS__BSP__BOARD_MODEL")

		endif()

	endif(STM32CUBEL4__USE_HAL_DRIVER)

	if(STM32CUBEL4__USE_FULL_LL_DRIVER)

		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.c)

	endif(STM32CUBEL4__USE_FULL_LL_DRIVER)

	if(STM32CUBEL4__USE_FREERTOS)

		include_directories(${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F)
		include_directories(${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source)
		include_directories(${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS)
		include_directories(${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/include)

		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/list.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/queue.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/timers.c)

		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c)
		set(PROJECT_SOURCES ${PROJECT_SOURCES} ${_tmp_source_dir}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c)

	endif(STM32CUBEL4__USE_FREERTOS)

endif(INCLUDE__STM32CUBEL4)

