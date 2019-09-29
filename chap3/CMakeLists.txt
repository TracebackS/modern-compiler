set(CHAP chap3)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h
		COMMAND yacc -dv ${CMAKE_CURRENT_SOURCE_DIR}/tiger.grm
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		DEPENDS tiger.grm
		COMMENT "generate parser")

add_executable(${CHAP}
		util.c
		util.h
		errormsg.c
		errormsg.h
		parsetest.c
		lex.yy.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_sources(${CHAP} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h)
