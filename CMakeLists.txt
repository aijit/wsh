PROJECT(wsh)

cmake_minimum_required(VERSION 3.0...3.25)

MESSAGE(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# module directories
SET(BASH
        ${CMAKE_CURRENT_SOURCE_DIR}/bash_src)
SET(BUILTINS
        ${CMAKE_CURRENT_SOURCE_DIR}/bash_src/builtins)
SET(LIB
        ${CMAKE_CURRENT_SOURCE_DIR}/bash_src/lib)
SET(DUMMY
        ${CMAKE_CURRENT_SOURCE_DIR}/dum_inc)


# global header include search path
INCLUDE_DIRECTORIES(
        ${DUMMY}
        ${LIB}
        ${LIB}/posixheaders
        ${BUILTINS}
        ${BASH}/include
        ${BASH})

# defines
STRING(TIMESTAMP BUILD_TIME "%s")
ADD_DEFINITIONS(
        -DNDEBUG -DWIN32 -D_CONSOLE -DProgram=bash
        -DINITIALIZE_SIGLIST
        -DPREFER_STDARG
        -DHAVE_SYS_PARAM_H -DHAVE_MEMPCPY -DHAVE_RAISE
        -DHANDLE_SIGNALS -DVOID_SIGHANDLER -DRETSIGTYPE=void
        -DHAVE_STDINT_H -DHAVE_GETCWD
        -DHAVE_UNISTD_H -DHAVE_STDLIB_H -DHAVE_LIMITS_H
        -DHAVE_RESOURCE -DHAVE_SYS_PARAM -DHAVE_DIRENT_H
        -DVOID_SIGHANDLER -DBROKEN_SIGSUSPEND -DHAVE_GETHOSTNAME
        -DMKFIFO_MISSING -DNO_DEV_TTY_JOB_CONTROL -DNO_SBRK_DECL
        -DPGRP_PIPE -DTERMIOS_MISSING -DHAVE_DUP2
        -DHAVE_STRERROR -DHAVE_DIRENT -DHAVE_STRING_H
        -DHAVE_STRCHR -DSHELL -DHAVE_ALLOCA
        -DHAVE_STRCASECMP
        -DHAVE_ALLOCA_H -D__NT_VC__ -D__NT_EGC__
        -DBUILDVERSION=${BUILD_TIME}
)

# global library search path
LINK_DIRECTORIES(
        ${CMAKE_BINARY_DIR})

# library targets
SET(DEP_LIBS glob readline termcap tilde intl)
FOREACH (lib ${DEP_LIBS})
    SET(ldir ${LIB}/${lib})
    FILE(GLOB HEADER_FILES ${ldir}/*.h)
    FILE(GLOB SOURCE_FILES ${ldir}/*.c)
    LIST(REMOVE_ITEM SOURCE_FILES ${LIB}/glob/glob_loop.c)
    LIST(REMOVE_ITEM SOURCE_FILES ${LIB}/glob/sm_loop.c)
    LIST(REMOVE_ITEM SOURCE_FILES ${LIB}/readline/emacs_keymap.c)
    LIST(REMOVE_ITEM SOURCE_FILES ${LIB}/readline/complete.c)
    STRING(REPLACE "${LIB}/${lib}/" "" SOURCE_LIST "${SOURCE_FILES}")
    MESSAGE(STATUS "lib/${lib}\n${SOURCE_LIST}\n")
    ADD_LIBRARY(${lib} ${HEADER_FILES} ${SOURCE_FILES})
    TARGET_COMPILE_DEFINITIONS(${lib} PRIVATE -DIN_LIBINTL)
ENDFOREACH ()

# executable targets
SET(WSH bash)
FILE(GLOB SOURCE_FILES
        ${BASH}/*.c
        ${DUMMY}/*.c
        ${BUILTINS}/*.c)
FILE(GLOB HEADER_FILES
        ${BASH}/*.h
        ${DUMMY}/*.h
        ${BUILTINS}/*.h)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/vprint.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/signames.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/endian.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/jobs.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/newversion.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BASH}/y.tab.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BUILTINS}/mkbuiltins.c)
LIST(REMOVE_ITEM SOURCE_FILES ${BUILTINS}/psize.c)
STRING(REPLACE "${BASH}/" "" SOURCE_LIST "${SOURCE_FILES}")
STRING(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" SOURCE_LIST "${SOURCE_LIST}")
MESSAGE(STATUS "${WSH}\n${SOURCE_LIST}\n")
ADD_EXECUTABLE(
        ${WSH} ${HEADER_FILES} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(
        ${WSH} ${DEP_LIBS})

# test command
ADD_CUSTOM_TARGET(test
        COMMAND cmd /c cp ${CMAKE_BINARY_DIR}/${WSH}.exe shelltools/bash.exe
        COMMAND cmd /c cp ${CMAKE_BINARY_DIR}/${WSH}.exe shelltools/sh.exe
        COMMAND cd shelltools && cmd /c start_bash.bat "cd ../testcases; . ./runtests.sh" && cd ..
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )