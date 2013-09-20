file(GLOB subdir_srcs "*.cpp")
file(GLOB subdir_headers "*.h")

set(helloFile "scripts/helloWorld.cpp")
set(world "world.cpp")

# Does not compile due to subdir_srcs not being implemented

# compile libraries
add_library(libworld world.cpp)

add_executable(helloWorld ${helloFile})
target_link_libraries(helloWorld libworld)

set(stateFile "scripts/testState.cpp")
add_executable(testState ${stateFile} ${subdir_srcs})

