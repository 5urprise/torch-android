SET(src DiskFile.c ApkFile.c File.c Generator.c MemoryFile.c PipeFile.c Storage.c Tensor.c Timer.c utils.c init.c TensorOperator.c TensorMath.c random.c )
SET(luasrc init.lua File.lua Tensor.lua CmdLine.lua Tester.lua test/test.lua)
  
# Necessayr do generate wrapper
ADD_TORCH_WRAP(tensormathwrap TensorMath.lua)
ADD_TORCH_WRAP(randomwrap random.lua)

ADD_TORCH_PACKAGE(torch "${src}" "${luasrc}")

TARGET_LINK_LIBRARIES(torch luaT TH)
