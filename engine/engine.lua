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
    includedirs({"./public", "./private"})
    defines({"ENGINE_DLL", "ENGINE_EXPORT"})  
    filter "configurations:Debug"
      defines { "DEBUG" }
 
    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
    filter "*"
    local inclPath = path.getabsolute("./public")
    
    dependsOn["engine"] = function (state)
            table.insert(state.includes, path.getrelative(path.getabsolute("."), inclPath))
            table.insert(state.defines, "ENGINE_DLL")
            table.insert(state.links, "Engine")
    end
    
   local state = {includes={}, links={}, defines={}}
    dependsOn["sdl"](state)
    defines(state.defines)
    includedirs(state.includes)
    links(state.links)