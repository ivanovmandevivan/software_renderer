
solution "software_renderer"
  
configurations {
  "Release",
  "Debug"
}

platforms {
  "x64",
  "x32",
  "Native",
}


PROJ_DIR = path.getabsolute("..")
BIN_FOLDER = PROJ_DIR .. "/bin";

-- Create table for include and source dirs:

IncludeDir = {};
IncludeDir["SDL2"] = (PROJ_DIR .. "/deps/SDL2/include");
IncludeDir["SFW_RENDERER"] = (PROJ_DIR .. "/include");

SourceDir = {};
SourceDir["SFW_RENDERER"] = (PROJ_DIR .. "/src");

project "software_renderer"
kind "ConsoleApp"
location (PROJ_DIR .. "/build")
language "C++"
flags({
  "Cpp11",
  "Cpp14"
});  


targetdir (PROJ_DIR .. "/bin/" )--.. project().name)
debugdir (PROJ_DIR .. "/bin/" )--.. project().name)
objdir (PROJ_DIR .. "/bin/" )--.. project().name)

defines {
  "_CRT_SECURE_NO_WARNINGS",
}

files {
  
  -- Main SRC
  SourceDir["SFW_RENDERER"] .. "/**.c",
  SourceDir["SFW_RENDERER"] .. "/**.cc",
  SourceDir["SFW_RENDERER"] .. "/**.cpp",

  -- Main INCLUDE
  IncludeDir["SFW_RENDERER"] .. "/**.h",

  -- Deps:
  IncludeDir["SDL2"] .. "/*.h",
}

includedirs{
  IncludeDir["SDL2"]
}

libdirs {
  PROJ_DIR .. "/bin",
}

links {
  "user32", 
  "gdi32" ,
  "shell32",
  "SDL2"
}

flags{"Symbols" }

configuration "Debug"
  defines {
    "DEBUG"
  }

configuration "windows"
  
  defines {}

configuration "linux"
  defines {
    "CPUR_LINUX_PLATFORM"
  }
