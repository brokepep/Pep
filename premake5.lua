workspace "Pep"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Pep/vendor/GLFW/include"
IncludeDir["Glad"] = "Pep/vendor/Glad/include"
IncludeDir["ImGui"] = "Pep/vendor/imgui"
IncludeDir["glm"] = "Pep/vendor/glm"

include "Pep/vendor/GLFW"
include "Pep/vendor/Glad"
include "Pep/vendor/imgui"

project "Pep"
	location "Pep"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	buildoptions "/utf-8"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "peppch.h"
	pchsource "Pep/src/peppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PEP_PLATFORM_WINDOWS",
			"PEP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PEP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PEP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PEP_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	buildoptions "/utf-8"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Pep/vendor/spdlog/include",
		"Pep/src",
		"Pep/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Pep"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PEP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PEP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PEP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PEP_DIST"
		runtime "Release"
		optimize "on"