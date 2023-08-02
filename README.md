[![Clang](https://github.com/dragon-archer/da/actions/workflows/clang.yml/badge.svg)](https://github.com/dragon-archer/da/actions/workflows/clang.yml)
[![GCC](https://github.com/dragon-archer/da/actions/workflows/gcc.yml/badge.svg)](https://github.com/dragon-archer/da/actions/workflows/gcc.yml)
[![MSVC](https://github.com/dragon-archer/da/actions/workflows/msvc.yml/badge.svg)](https://github.com/dragon-archer/da/actions/workflows/msvc.yml)

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/9c00226519bb405a85d070fd40124e6b)](https://app.codacy.com/gh/dragon-archer/da/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Codacy Badge](https://app.codacy.com/project/badge/Coverage/9c00226519bb405a85d070fd40124e6b)](https://app.codacy.com/gh/dragon-archer/da/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_coverage)
# DA

A C++ utility library majored in preprocessor macros and template classes (STL-compatible)

## Install
Copy the include [folder](https://github.com/dragon-archer/da/tree/master/include/da) to your build tree and use a C++20 compiler.

## Avaialbility

<table>
	<tr>
		<td>Level</td>
		<td>Module</td>
		<td>Notes</td>
	</tr>
	<tr>
		<td bgcolor=darkorange>B</td>
		<td>cmdline_parser</td>
		<td>Partly tested</td>
	</tr>
	<tr>
		<td bgcolor=red>C</td>
		<td>string</td>
		<td>Oldest, not tested, might not work</td>
	</tr>
	<tr>
		<td bgcolor=green>A</td>
		<td>preprocessor</td>
		<td>Old but fully tested</td>
	</tr>
	<tr>
		<td bgcolor=green>A</td>
		<td>type_traits</td>
		<td>New, partly tested</td>
	</tr>
	<tr>
		<td bgcolor=green>A</td>
		<td>utility</td>
		<td>Newest, fully tested</td>
	</tr>
</table>

## Dependency
This project depends on [spdlog](https://github.com/gabime/spdlog) for logging.

If CMake option `DA_UseStdFormat` is not enabled(default), this project will depend on [fmt](https://github.com/fmtlib/fmt) for formatting

## License

This project is published under MIT License

Copyright(C) 2022-2023 dragon-archer
