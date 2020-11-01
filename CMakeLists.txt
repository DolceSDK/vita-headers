cmake_minimum_required(VERSION 3.13)

set(ARCH "arm-dolce-eabi" CACHE STRING "Target architecture")
set(CMAKE_INSTALL_PREFIX "$ENV{DOLCESDK}" CACHE PATH "Install prefix")

if(DEFINED ENV{DOLCESDK})
  set(_LIBS_GEN "$ENV{DOLCESDK}/bin/dolce-libs-gen")
else()
  set(_LIBS_GEN "dolce-libs-gen")
endif()
set(LIBS_GEN "${_LIBS_GEN}" CACHE STRING "libs-gen command")

include(ProcessorCount)
ProcessorCount(_NPROC)
if(_NPROC EQUAL 0)
  set(_NPROC 1)
endif()
set(NPROC "${_NPROC}" CACHE STRING "Number of processors")

project(dolcesdk-target-headers LANGUAGES NONE)

# build and install stubs

set(STUBS_DIR stubs)
set(DB_FILE "${CMAKE_SOURCE_DIR}/db.yml")
set(DB_365_FILE "${CMAKE_SOURCE_DIR}/db_365.yml")

add_custom_command(OUTPUT "${STUBS_DIR}"
  DEPENDS "${DB_FILE}" "${DB_365_FILE}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${STUBS_DIR}"
  COMMAND "${LIBS_GEN}" "${DB_FILE}" "${STUBS_DIR}/cex-3600"
  COMMAND "${LIBS_GEN}" "${DB_365_FILE}" "${STUBS_DIR}/cex-3650"
)

add_custom_target(prepare-stubs
  DEPENDS "${STUBS_DIR}"
  COMMENT "Preparing stubs"
)

add_custom_target(build-stubs
  COMMAND make -C "${STUBS_DIR}/cex-3600" -j "${NPROC}"
  COMMAND make -C "${STUBS_DIR}/cex-3650" -j "${NPROC}"
  COMMENT "Building stubs with ${NPROC} jobs"
)

add_dependencies(build-stubs prepare-stubs)

add_custom_target(install-stubs
  COMMAND make -C "${STUBS_DIR}/cex-3600" install
  COMMAND make -C "${STUBS_DIR}/cex-3650" install
  COMMENT "Install stubs"
)

add_dependencies(install-stubs build-stubs)

# download and install binary blobs

set(BLOBS_DIR blobs)

add_custom_command(OUTPUT "${BLOBS_DIR}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${BLOBS_DIR}"
  COMMAND curl -LO "https://github.com/DolceSDK/artifacts/archive/target.tar.gz"
  COMMAND tar xzf target.tar.gz --strip-components=1 --directory="${BLOBS_DIR}"
)

add_custom_target(download-blobs
  DEPENDS "${BLOBS_DIR}"
  COMMENT "Downloading blobs"
)

add_custom_target(install-blobs
  COMMAND make -C "${BLOBS_DIR}" install
  COMMENT "Installing blobs"
)

add_dependencies(install-blobs download-blobs)

# install headers and NIDs

install(DIRECTORY include/ DESTINATION "${ARCH}/include")
install(FILES db.yml db_365.yml DESTINATION share)
