include_directories(.)

add_executable(
  offline_proof vote/offline_proof.cpp vote/utils.cpp vote/utils.hpp
)
target_link_libraries(
  offline_proof

  snark
)
target_include_directories(
  offline_proof

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
)

add_library(
  ourzklib SHARED

  test_libsnark.cpp 
  vote/trusted_setup.cpp 
  vote/online_verify.cpp 
  vote/utils.cpp 
  vote/utils.hpp
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
