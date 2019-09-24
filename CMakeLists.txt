cmake_minimum_required(VERSION 3.10)

project(compiler)

add_executable(chap1 chap1/main.c
        chap1/slp.c
        chap1/slp.h
        chap1/util.c
        chap1/util.h
        chap1/prog1.c
        chap1/prog1.h)

add_executable(chap2 chap2/driver.c
        chap2/errormsg.c
        chap2/errormsg.h
        chap2/tokens.h
        chap2/util.h
        chap2/util.c
        )
#        chap2/lex.yy.c)

add_executable(chap3 chap3/util.c
        chap3/util.h
        chap3/errormsg.c
        chap3/errormsg.h
        chap3/parsetest.c
        )
#       chap3/lex.yy.c
#       chap3/y.tab.h
#       chap3/y.tab.c