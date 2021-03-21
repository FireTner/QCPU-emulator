workspace "QCPU-Emulator"
    configurations
    {
        "Debug",
        "Release",
        "Fast",
        "MinRelSize"
    }

    __OS = ""
    if os.host() == "windows" then
        if not os.is64bit() then
            __OS = "win32"
        else
            __OS = "win64"
        end
    elseif os.host() == "linux" then
        __OS = "linux-amd64"
    end

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        buildoptions "-O3"

    filter "configurations:Fast"
        runtime "Release"
        buildoptions "-Ofast"

    filter "configurations:MinRelSize"
        runtime "Release"
        buildoptions "-Os"

    outputDir = __OS .. "/%{cfg.buildcfg}"

includePath = {}
includePath["qcpuEmu"] = "%{wks.location}/qcpu"

include "qcpu"
include "qcpu-assembler"
include "qcpu-programs/qcpu-fib"
include "qcpu-programs/qcpu-multiply"