baseDir = path.getabsolute("..").."/"

workspace "Game"
    configurations {"Debug", "Release"}
     location(baseDir .. ".prj")
    flags
    {
        "FatalCompileWarnings",
        "MultiProcessorCompile",
        
    }
dependsOn = {}

dofile(baseDir.."engine/engine.lua")
dofile(baseDir.."dependencies/SDL2-2.0.4/sdl.lua")

project "Game"
    kind "ConsoleApp"
    language "C++"
    
    targetdir(baseDir .. ".bin/" .. _ACTION)
    objdir(baseDir .. ".obj/" .. _ACTION)
    location(baseDir .. ".prj")
    
     files { 
         "src/**.h", 
         "src/**.cpp" 
         }
    flags { "Symbols" }
       
    filter "configurations:Debug"
      defines { "DEBUG" }
 
    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
    dependsOn["engine"]()
    dependsOn["sdl"]()
    
    