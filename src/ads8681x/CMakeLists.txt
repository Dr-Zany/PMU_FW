set(TARGET_NAME ads8681x)

file(GLOB CPP
  *.cpp
)

add_library(${TARGET_NAME} ${CPP})

target_link_libraries(${TARGET_NAME} pico_stdlib hardware_spi)
target_include_directories(${TARGET_NAME} PUBLIC 
  ./
)