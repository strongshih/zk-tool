include_directories(.)

add_library(
  ourzklib SHARED

  ourzklib.cpp
)
target_link_libraries(
  ourzklib

  snark
)
target_include_directories(
  ourzklib

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
)
