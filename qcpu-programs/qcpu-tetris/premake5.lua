project "qcpu-tetris"
kind "ConsoleApp"
language "C"

objdir("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")
targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")

defines
{
    
}

includedirs
{
    "%{includePath.qcpu-emu}"
}

files
{
    "src/**.c"
}

links
{
    "QCPUEmu"
}