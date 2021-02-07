mkdir analysis
copy ..\premake5.lua_GLFW gwcEngine\vendor\GLFW
rename gwcEngine\vendor\GLFW\premake5.lua_GLFW premake5.lua
CALL vendor\bin\premake\premake5.exe vs2019
PAUSE