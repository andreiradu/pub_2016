project "Engine"
    kind "SharedLib"
    language "C++"
    location(baseDir .. ".prj")
    targetdir(baseDir .. ".bin/" .. _ACTION)
    objdir(baseDir .. ".obj/" .. _ACTION)
    
     files { 
         "public/**.h", 
         "private/**.h",
         "private/**.cpp" 
         }
    flags { "Symbols" }
       
    filter "configurations:Debug"
      defines { "DEBUG" }
 
    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
    dependsOn["engine"] = function ()
            
    end