configure_file(cmakevars.h.in cmakevars.h @ONLY)

add_executable(bitcalc
	main.cpp
	myerror.cpp
	parser.cpp
	token.cpp
)

target_link_libraries(bitcalc PUBLIC compile_flags)
target_include_directories(bitcalc PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_BINARY_DIR}/src # cmakevars.h
)

install(TARGETS bitcalc DESTINATION bin)
