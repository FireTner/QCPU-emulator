project "qcpu-multiply"
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
    "QCPUEmu"
}

if __OS == "win32" then
    postbuildcommands
    {
        "if [ ! -f %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/QCPUEmu.dll ]; then ln -srv %{wks.location}/bin/" .. outputDir .. "/QCPUEmu/QCPUEmu.dll %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/QCPUEmu.dll; fi"
    }
elseif __OS == "win64" then
    postbuildcommands
    {
        "if [ ! -f %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/QCPUEmu.dll ]; then ln -srv %{wks.location}/bin/" .. outputDir .. "/QCPUEmu/QCPUEmu.dll %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/QCPUEmu.dll; fi"
    }
else
    postbuildcommands
    {
        "if [ ! -f %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/libQCPUEmu.so ]; then ln -srv %{wks.location}/bin/" .. outputDir .. "/QCPUEmu/libQCPUEmu.so %{wks.location}/bin/" .. outputDir .. "/%{prj.name}/libQCPUEmu.so; fi"
    }
end