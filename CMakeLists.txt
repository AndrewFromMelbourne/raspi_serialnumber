cmake_minimum_required(VERSION 2.6)
project(raspi_serialnumber)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#--------------------------------------------------------------------------

add_executable(serialnumber_cpuinfo serialnumber_cpuinfo.c)

#--------------------------------------------------------------------------

add_executable(serialnumber_sysfs serialnumber_sysfs.c)

#--------------------------------------------------------------------------

add_executable(serialnumber_mailbox serialnumber_mailbox.c)

#--------------------------------------------------------------------------

add_executable(serialnumber_vcgencmd_using_bcm_host serialnumber_vcgencmd_using_bcm_host.c)
target_link_libraries(serialnumber_vcgencmd_using_bcm_host bcm_host)

#--------------------------------------------------------------------------

add_executable(serialnumber_vcgencmd_via_ioctl serialnumber_vcgencmd_via_ioctl.c)
