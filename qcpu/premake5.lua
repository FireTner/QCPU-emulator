project "QCPUemu"
kind "SharedLib"
language "C"

objdir("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")
targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")

defines
{
    
}

includedirs
{
}

files
{
    "**.c"
}

links
{

}

project "QCPUemuS"
kind "StaticLib"
language "C"

objdir("%{wks.location}/bin-int/" .. outputDir .. "/%{prj.name}")
targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")

defines
{
    
}

includedirs
{
}

files
{
    "**.c"
}

links
{

}