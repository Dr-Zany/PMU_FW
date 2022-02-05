set(TARGET_NAME main)

if (TARGET tinyusb_device)

file(GLOB CPP
  *.cpp
)

add_executable(${TARGET_NAME} ${CPP})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

pico_enable_stdio_usb(${TARGET_NAME} 0)
pico_enable_stdio_uart(${TARGET_NAME} 1)
pico_add_extra_outputs(${TARGET_NAME})

target_link_libraries(${TARGET_NAME} pico_stdlib hardware_spi)

elseif(PICO_ON_DEVICE)
  message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()