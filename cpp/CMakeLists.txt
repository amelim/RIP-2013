file(GLOB subdir_srcs "*.cpp")
file(GLOB subdir_headers "*.h")

set(planneroutput "scripts/planner.cpp")
set(helloFile "scripts/helloWorld.cpp")
set(world "world.cpp")
set(state "state.cpp")
set(astar "a_star.cpp")

# Does not compile due to subdir_srcs not being implemented
#add_executable(helloWorld ${helloFile} ${subdir_srcs})

# compile libraries
add_library(libworld world.cpp)
add_library(libstate state.cpp)
add_library(libastar a_star.cpp)

add_executable(helloWorld ${helloFile})
target_link_libraries(helloWorld libworld libstate libastar)

add_executable(planner ${planneroutput})
target_link_libraries(planner libworld libstate libastar)

set(stateFile "scripts/testState.cpp")
add_executable(testState ${stateFile} ${subdir_srcs})
target_link_libraries(testState libworld)

