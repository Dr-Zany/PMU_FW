set(TARGET_NAME ads8681x)

file(GLOB CPP
  *.cpp
)

add_library(${TARGET_NAME} ${CPP})
