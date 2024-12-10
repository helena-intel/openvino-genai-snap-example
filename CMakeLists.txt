cmake_minimum_required(VERSION 3.23)
project(OpenVINOExampleProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(OpenVINOGenAI REQUIRED)
add_executable(openvinodemo openvinodemo.cpp)
target_link_libraries(openvinodemo PRIVATE openvino::genai)

set_target_properties(openvinodemo PROPERTIES INSTALL_RPATH "$ORIGIN")
set_target_properties(openvinodemo PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

set(lib_directory "openvino_genai/runtime/lib/intel64")
set(tbb_directory "openvino_genai/runtime/3rdparty/tbb/lib")

install(TARGETS openvinodemo RUNTIME DESTINATION .)
install(FILES
      "${lib_directory}/libopenvino.so"
      "${lib_directory}/libopenvino.so.2024.5.0"
      "${lib_directory}/libopenvino.so.2450"
      "${lib_directory}/libopenvino_ir_frontend.so.2024.5.0"
      "${lib_directory}/libopenvino_ir_frontend.so.2450"
      "${lib_directory}/libopenvino_intel_cpu_plugin.so"
      "${lib_directory}/libopenvino_genai.so.2024.5.0.0"
      "${lib_directory}/libopenvino_genai.so.2450"
      "${lib_directory}/libopenvino_genai.so"
      "${lib_directory}/libopenvino_tokenizers.so"
      "${lib_directory}/libcore_tokenizers.so"
      "${tbb_directory}/libtbb.so.12"
      "${tbb_directory}/libtbb.so.12.13"
      "${tbb_directory}/libtbb.so"
      "${tbb_directory}/libtbbmalloc.so"
      "${tbb_directory}/libtbbmalloc.so.2"
      "${tbb_directory}/libtbbmalloc.so.2.13"
      "${tbb_directory}/libtbbmalloc_proxy.so"
      "${tbb_directory}/libtbbmalloc_proxy.so.2"
      "${tbb_directory}/libtbbmalloc_proxy.so.2.13"
      "${tbb_directory}/libtbbbind_2_5.so"
      "${tbb_directory}/libtbbbind_2_5.so.3"
      "${tbb_directory}/libtbbbind_2_5.so.3.13"
      "${tbb_directory}/libhwloc.so.15.6.4"
      "${tbb_directory}/libhwloc.so.15"
      "${tbb_directory}/libhwloc.so"
DESTINATION .)
