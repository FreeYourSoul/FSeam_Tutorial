cmake_minimum_required(VERSION 3.5)
project(testing CXX)

set (CMAKE_CXX_STANDARD 17)

find_package(FSeam)

# required as we are going to launch the test via CTest
enable_testing()

######################## FIRST TEST : Compile class Mocking ###################################

## Create an executable containing the code we want to test
add_executable(classMock_Example_target
        ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/ClassesToMock.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/ClassesToMock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/ClassToTest.hh)
include_directories(classMock_Example_target ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example)

##
## In This example we give the target that contains the code we want to test, if the target contains a main (if it is an executable)
## it is required to provide the name path of the file providing this main (in order to remove it from the compilation) via the Argument MAIN_FILE
##
## This method is particularly useful as fast to implement (no need to explicitly specify the files to compile)
## it is a time consuming method that compile file that are not obviously needed for the test (usage of ccache is recommended to save time)
##
addFSeamTests(
        DESTINATION_TARGET testFSeam_1 # FSeam testing binary target created for this testcase
        TARGET_AS_SOURCE classMock_Example_target
        MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/main.cpp
        TST_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/test/MockSpecificInstanceTestCase.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/test/MockUsingDefaultTestCase.cpp
        TO_MOCK
            ${CMAKE_CURRENT_SOURCE_DIR}/ClassMock_Example/ClassesToMock.hh)


######################## SECOND TEST : Compile static/free function Mocking ###################

## Create an executable containing the code we want to test
add_library(static-Free_FunctionMock_Example_target
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/StaticFunction.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/StaticFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/FreeFunction.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/FreeFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/ClassToTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/ClassToTest.hh)
include_directories(static-Free_FunctionMock_Example_target ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/)

##
## In This example is similar to the previous one but use a library target
## (no need to specify a main to remove from the compilation)
##
addFSeamTests(
    DESTINATION_TARGET testFSeam_2 # FSeam testing binary target created for this testcase
    TARGET_AS_SOURCE static-Free_FunctionMock_Example_target
    TST_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/test/MockFreeFunctionTestCase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/test/MockStaticFunctionTestCase.cpp
    TO_MOCK
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/FreeFunction.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/StaticFunction.hh)

##
## Another way to compile the same test as above
## In This example we directly specify where is the include folders and what are the source to compile
## In case of big project, using this method make you able to only compile what you want to test
##
addFSeamTests(
    DESTINATION_TARGET testFSeam_3 # FSeam testing binary target created for this testcase
    FILES_AS_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/ClassToTest.cpp
    FOLDER_INCLUDES  ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include
    TST_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/test/MockFreeFunctionTestCase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/test/MockStaticFunctionTestCase.cpp
    TO_MOCK
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/FreeFunction.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Static-Free_FunctionMock_Example/include/StaticFunction.hh)

