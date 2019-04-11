add_definitions(-std=c++11)
set(TARGET data_structure)
aux_source_directory(. DIR_SRC)
add_executable(${TARGET} ${DIR_SRC})