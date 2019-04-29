cmake_minimum_required(VERSION 3.1)
project(qpalm)

find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)
find_package(SuiteSparse REQUIRED)

file(GLOB QPALM_SRC
	${PROJECT_SOURCE_DIR}/src/validate.c
	${PROJECT_SOURCE_DIR}/src/util.c
	${PROJECT_SOURCE_DIR}/src/termination.c
	${PROJECT_SOURCE_DIR}/src/scaling.c
	${PROJECT_SOURCE_DIR}/src/qpalm.c
	${PROJECT_SOURCE_DIR}/src/newton.c
	${PROJECT_SOURCE_DIR}/src/linesearch.c
	${PROJECT_SOURCE_DIR}/src/lin_alg.c
	${PROJECT_SOURCE_DIR}/src/cholmod_interface.c)

file(GLOB QPALM_H
	${PROJECT_SOURCE_DIR}/include/validate.h
	${PROJECT_SOURCE_DIR}/include/util.h
	${PROJECT_SOURCE_DIR}/include/types.h
	${PROJECT_SOURCE_DIR}/include/termination.h
	${PROJECT_SOURCE_DIR}/include/scaling.h
	${PROJECT_SOURCE_DIR}/include/qpalm.h
	${PROJECT_SOURCE_DIR}/include/newton.h
	${PROJECT_SOURCE_DIR}/include/linesearch.h
	${PROJECT_SOURCE_DIR}/include/lin_alg.h
	${PROJECT_SOURCE_DIR}/include/global_opts.h
	${PROJECT_SOURCE_DIR}/include/constants.h
  ${PROJECT_SOURCE_DIR}/include/cholmod_interface.h
)



add_library(qpalm ${QPALM_SRC} ${QPALM_H})

target_include_directories(qpalm
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
		$<INSTALL_INTERFACE:${INCLUDE_PREFIX}/qpalm>
    ${SUITESPARSE_INCLUDE_DIR}

)
target_link_libraries(qpalm blas lapack ${SUITESPARSE_LIB})
set_property(TARGET qpalm PROPERTY C_STANDARD 99)

install(TARGETS qpalm EXPORT qpalmConfig
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin)

install(FILES ${QPALM_H} DESTINATION "${INCLUDE_PREFIX}/qpalm")


install(EXPORT qpalmConfig DESTINATION cmake)
