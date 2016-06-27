baseDir = "../"

workspace "Game"
    configurations {"Degug", "Release"}
     location(baseDir .. ".prj")
    
dependsOn = {}

dofile(baseDir.."engine/engine.lua")

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
    
    