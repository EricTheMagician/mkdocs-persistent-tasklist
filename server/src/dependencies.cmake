include(FetchContent)

# get httplib
set(HTTPLIB_COMPILE ON)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.10.1 
)

# get sqlite orm
set(SQLITE_ORM_ENABLE_CXX_17 ON)
FetchContent_Declare(sqlite_orm
  GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
  GIT_TAG        v1.7.1
)

FetchContent_MakeAvailable(httplib sqlite_orm)

# add_subdirectory(${sqlite_orm_SOURCE_DIR} ${sqlite_orm_BINARY_DIR})
