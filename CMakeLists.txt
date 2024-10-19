cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(leetcode)


set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
# 临时变量 为了子cmake继承使用 在子cmake内部再配置保存位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# 寻找库 在构建的时候再链接 (因为有的子项目可能不用)
find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${PROJECT_INCLUDE_DIRS})

#=======================================================================
set(EXCLUDED_DIRECTORIES 1434)
#=======================================================================


# 获取所有子项目的目录
file(GLOB SUB_PROJECTS "${PROJECT_SOURCE_DIR}/projects/*")

# 遍历每个子项目并添加
foreach (SUB_PROJECT ${SUB_PROJECTS})
    if (IS_DIRECTORY ${SUB_PROJECT})
        # 获取最后一个/后的名称 方便使用 EXCLUDED_DIRECTORIES 进行排除
        get_filename_component(LAST_PART ${SUB_PROJECT} NAME)
        if (NOT LAST_PART IN_LIST EXCLUDED_DIRECTORIES)
            # 设置子项目的名称（使用文件夹名称）
            set(PROJECT_NAME ${LAST_PART})
            project(${PROJECT_NAME})

            # 如果有，设置sub project的私有include的文件夹
            set(SUBPROJECT_INCLUDE_DIRS ${SUB_PROJECT}/include)
            include_directories(${SUBPROJECT_INCLUDE_DIRS})

            # 收集所有.cpp源文件
            file(GLOB_RECURSE SOURCE_FILES ${SUB_PROJECT}/src/*.cpp)

            # 为每个子项目添加一个可执行文件
            add_executable(${PROJECT_NAME} ${SOURCE_FILES})

            # 添加依赖
            target_link_libraries(${PROJECT_NAME} fmt::fmt)
            target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)
            target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

            # 记录需要测试的文件
            list(APPEND TEST_TARGETS ${PROJECT_NAME})
        endif ()
    endif ()
endforeach ()

# 添加自定义目标来运行所有Catch2的测试
add_custom_target(run_all_tests
        COMMAND ${CMAKE_COMMAND} -E echo "Running all Catch2 tests..."
        )

# 遍历每个可执行文件，添加到run_all_tests中
foreach (TEST_TARGET ${TEST_TARGETS})
    add_custom_command(TARGET run_all_tests POST_BUILD
            COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_TARGET}
            WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
            COMMENT "Running tests for ${TEST_TARGET}"
            VERBATIM
            )
endforeach ()
