workspace("KNR")

configurations({
	"debug",
	"release",
})

location("build")

function build_project(source_dir, source_file)
	project(source_file)
	kind("ConsoleApp")
	language("C")

	targetdir("build/%{cfg.buildcfg}")

	files({
		source_dir .. "/" .. source_file .. ".c",
	})

	links({
		"m",
	})

	includedirs({
		source_dir,
	})

	-- minimum: GCC 15
	filter({ "system:linux", "action:gmake" })
	buildoptions({
		"-std=c23",
		"-g",
		"-Og",
		"-save-temps",
		"-march=native",
		"-Wall",
		"-Wextra",
		"-Whardened",
		"-Werror",
		"-Wformat",
		"-Wformat=2",
		"-Wformat-security",
		"-Wconversion",
		"-Wsign-conversion",
		"-Wimplicit-fallthrough",
		"-Wfloat-equal",
		"-Wtrampolines -fzero-init-padding-bits=all",
		"-Wbidi-chars=any",
		"-Wundef",
		"-Wunused-variable",
		"-Wshadow",
		"-Wpointer-arith",
		"-Wcast-align",
		"-Wstrict-prototypes",
		"-Wmissing-prototypes",
		"-Wmissing-declarations",
		"-Wmisleading-indentation",
		"-Wparentheses",
		"-Wlogical-op",
		"-Wuseless-cast",
		"-Wmissing-include-dirs",
		"-Wredundant-decls",
		"-Wold-style-definition",
		"-Wwrite-strings",
		"-Wcast-qual",
		"-Wswitch-default",
		"-Wunreachable-code",
		"-Winit-self",
		"-Wimplicit-function-declaration",
		"-Wdeprecated",
		"-U_FORTIFY_SOURCE",
		"-D_FORTIFY_SOURCE=3",
		"-fstrict-flex-arrays=3",
		"-fstack-clash-protection",
		"-fstack-protector-strong",
		"-Wl,-z,nodlopen",
		"-Wl,-z,noexecstack",
		"-Wl,-z,relro",
		"-Wl,-z,now",
		"-Wl,--as-needed",
		"-Wl,--no-copy-dt-needed-entries",
		"-fPIE -pie",
		"-fcf-protection=full",
		"-fno-delete-null-pointer-checks",
		"-fno-strict-overflow",
		"-fno-strict-aliasing",
		"-ftrivial-auto-var-init=zero",
	})

	linkoptions({
		"-Wl,-z,nodlopen",
		"-Wl,-z,noexecstack",
		"-Wl,-z,relro",
		"-Wl,-z,now",
		"-Wl,--as-needed",
		"-Wl,--no-copy-dt-needed-entries",
		"-fPIE -pie",
	})

	filter({ "system:linux", "action:gmake", "configurations:debug" })
	symbols("On")

	defines({
		"_DEBUG",
	})

	buildoptions({
		"-fno-omit-frame-pointer",
		"-fno-optimize-sibling-calls",
		"-fno-common",
		"-fsanitize=address,undefined",
	})

	linkoptions({
		"-fsanitize=address,undefined",
	})

	filter("configurations:release")
	symbols("On")

	defines({
		"NDEBUG",
	})

	buildoptions({
		"-O2",
	})

	linkoptions({
		"-flto",
	})
end

-------------- CHAPTER 1 --------------
build_project("arrays_and_strings", "ex1_1")
build_project("arrays_and_strings", "ex1_2")
build_project("arrays_and_strings", "ex1_3")
build_project("arrays_and_strings", "ex1_4")
build_project("arrays_and_strings", "ex1_5")
build_project("arrays_and_strings", "ex1_6")
build_project("arrays_and_strings", "ex1_7")
build_project("arrays_and_strings", "ex1_8")
build_project("arrays_and_strings", "ex1_9")
