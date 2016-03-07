newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

solution "tmp_octavebands"
configurations {
	"Debug",
	"Release",
}

platforms {
    "ARM"
	"x32",
	"x64",
	"Native", -- for targets where bitness is not specified
}

language "C++"

PROJ_DIR = path.getabsolute("..")
local PROJ_BUILD_DIR = path.join(PROJ_DIR, ".build")

dofile "toolchain.lua"
toolchain(BX_BUILD_DIR)

function copyLib()
end

project ("tmp_octavebands" .. _name)
    uuid (os.uuid("tmp_octavebands" .. _name))
    kind(_kind)

    if _kind == "SharedLib" then
		defines {
			"SHARED_LIB_BUILD=1",
		}

		configuration { "vs20* or mingw*" }
			links {
				"gdi32",
				"psapi",
			}

		configuration { "mingw*" }
			linkoptions {
				"-shared",
			}

		configuration { "linux-*" }
			buildoptions {
				"-fPIC",
			}

		configuration {}
	end

    if _kind == "SharedProj" then
		defines {
			"SHARED_PROJ_BUILD=1",
		}

		configuration { "vs2015 or mingw*" }
			links {
				"gdi32",
				"psapi",
			}

		configuration { "mingw*" }
			linkoptions {
				"-shared",
			}

		configuration { "linux-*" }
			buildoptions {
				"-fPIC",
			}

		configuration {}
	end

	includedirs {
		path.join(BX_DIR, "include"),
	}

	defines {
		_defines,
	}

	configuration { "Debug" }
		defines {
			"BUILD_CONFIG_DEBUG=1",
		}

	configuration { "android*" }
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "winphone8* or winstore8*" }
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	configuration { "*clang*" }
		buildoptions {
			"-Wno-microsoft-enum-value", -- enumerator value is not representable in the underlying type 'int'
			"-Wno-microsoft-const-init", -- default initialization of an object of const type '' without a user-provided default constructor is a Microsoft extension
		}

	configuration { "osx" }
		linkoptions {
			"-framework Cocoa",
			"-framework QuartzCore",
			"-framework OpenGL",
			"-weak_framework Metal",
		}

	configuration { "ios* or tvos*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
			"-weak_framework Metal",
		}

	configuration { "xcode4", "ios" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/iOS-Info.plist"),
		}

	configuration { "xcode4", "tvos" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/tvOS-Info.plist"),
		}

	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()

	configuration {}

		includedirs {
			path.join(BGFX_DIR, "include"),
		}

		files {
			path.join(BGFX_DIR, "include/**.h"),
			path.join(BGFX_DIR, "src/**.cpp"),
			path.join(BGFX_DIR, "src/**.h"),
		}

		removefiles {
			path.join(BGFX_DIR, "src/**.bin.h"),
		}

	copyLib()
end