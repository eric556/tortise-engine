function includeSFML()
    includedirs "Libraries/SFML/include"
end

function includeIMGUI()
    includedirs "Libraries/IMGUI/imgui"
    includedirs "Libraries/IMGUI/imgui-sfml"
end

function includeSOL2()
    includedirs "Libraries/sol2"
end

function includeLua()
    includedirs "Libraries/lua/include"
end

function useECS()
    includedirs "Projects/ECS"
    -- links "ECS" -- no need to link a header only lib
end

function linkSFML()
    libdirs "Libraries/SFML/lib"
    defines {"SFML_STATIC"}

    configuration "Debug"
        links {
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "sfml-network-s-d",
            "sfml-graphics-s-d",
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "openal32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",
            "ws2_32"
        }

    configuration "Release"
        links {
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
            "sfml-network-s",
            "sfml-graphics-s",
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "openal32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",
            "ws2_32"
        }
    
    filter{}
end

function linkIMGUI()
    files "Libraries/IMGUI/imgui/imgui.cpp"
    files "Libraries/IMGUI/imgui/imgui_draw.cpp"
    files "Libraries/IMGUI/imgui/imgui_widgets.cpp"
    files "Libraries/IMGUI/imgui-sfml/imgui-SFML.cpp"
    files "Libraries/IMGUI/imgui/imgui_demo.cpp"
end

function linkLua()
    libdirs "Libraries/lua"
    links {
        "lua53"
    }
end

workspace "TortiseEngine"
    location "Projects"
    language "C++"
    architecture "x86_64"

    configurations {"Debug", "Release"}

    filter{"configurations:Debug"}
        symbols "On"

    filter{"configurations:Release"}
        optimize "On"

    filter{}

    targetdir("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir("Build/Obj/%{prj.name}/%{cfg.longname}")

project "ECS"
    location "Projects/ECS"
    kind "StaticLib"

    files "Projects/ECS/**.cpp"
    files "Projects/ECS/**.hpp"
    files "Projects/ECS/**.h"

    includeLua()
    linkLua()

    includeSOL2()

project "DinoRun"
    location "Projects/DinoRun"
    kind "ConsoleApp"
    cppdialect "C++17"

    files "Projects/DinoRun/src/**.cpp"
    files "Projects/DinoRun/src/**.h"
    files "Projects/DinoRun/src/**.hpp"

    includeSFML()
    linkSFML()

    includeIMGUI()
    linkIMGUI()
    
    useECS()