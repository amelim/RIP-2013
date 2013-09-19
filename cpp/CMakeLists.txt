file(GLOB subdir_srcs "*.cpp")
file(GLOB subdir_headers "*.h")

file(GLOB script_srcs "scripts/*.cpp")
foreach(script ${script_srcs})
  add_executable(${script} ${script} ${subdir_srcs})
endforeach(script)
