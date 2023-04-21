configure_file(cmakevars.h.in cmakevars.h @ONLY)

add_executable(a.out
	main.cpp
	myerror.cpp
	parser.cpp
	token.cpp
)

target_link_libraries(a.out PUBLIC compile_flags)
target_include_directories(a.out PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_BINARY_DIR}/src # cmakevars.h
)
