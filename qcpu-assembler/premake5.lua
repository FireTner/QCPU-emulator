project "qcpu-assembler"
kind "ConsoleApp"
language "C"

objdir("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")
targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")

defines
{
    
}

includedirs
{
    "%{includePath.qcpuEmu}"
}

files
{
    "src/**.c"
}

links
{
}