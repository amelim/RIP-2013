file(GLOB subdir_srcs "*.cpp")
file(GLOB subdir_headers "*.h")

set(helloFile "scripts/helloWorld.cpp")
# Does not compile due to subdir_srcs not being implemented
#add_executable(helloWorld ${helloFile} ${subdir_srcs})
add_executable(helloWorld ${helloFile})
