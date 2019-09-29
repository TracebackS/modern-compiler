set(CHAP chap2)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
		COMMAND lex ${CMAKE_CURRENT_SOURCE_DIR}/tiger.lex
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		DEPENDS tiger.lex
		COMMENT "generate lexer")

add_executable(${CHAP}
		driver.c
		errormsg.c
		errormsg.h
		tokens.h
		util.h
		util.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${CHAP} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
