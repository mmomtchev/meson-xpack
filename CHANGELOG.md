# 1.5.2-4 2024-10-20
  * Fix [`hadron#55`](https://github.com/mmomtchev/hadron/issues/55), always resolve `emnapi` paths to allow building Node-API WASM modules with `emnapi` installed in `../emnapi` relative to the project root

# 1.5.2-3 2024-10-08
  * Fix [`hadron#51`](https://github.com/mmomtchev/hadron/issues/51), do not pass paths with `\`to CMake on Windows
  * Fix [`hadron#53`](https://github.com/mmomtchev/hadron/issues/53), accept library names specified with `.lib` extension in CMake on Windows

# 1.5.2-2 2024-10-01
  * Fix [`hadron#46`](https://github.com/mmomtchev/hadron/issues/46), in the `cmake` module, installing multiple files from a variable in `INSTALL(FILES...)` does not work
  * Fix [`hadron#48`](https://github.com/mmomtchev/hadron/issues/48), in the `cmake` module, generated files in `INSTALL(FILES...)` should be ignored with a warning

# 1.5.2-1 2024-10-01
  * Update `meson` to 1.5.2
  * Fix [`hadron#37`](https://github.com/mmomtchev/hadron/issues/37), do not eliminate `/usr/local/include` when used in `-isystem` with `-isysroot`

# 1.5.1-2 2024-07-29
  * Fix uninstallable package

# 1.5.1-1 2024-07-29
  * Update `meson` to 1.5.1

# 1.5.0-1 2024-07-15
  * hadron 1.5.0, first official release

# 1.5.0rc2-2 2024-07-04
  * Fix [#1](https://github.com/mmomtchev/meson-xpack/issues/1), pass `--internal` to `meson` on Windows

# 1.5.0rc2-1 2024-07-03
  * First tagged release, aligned with `meson` 1.5.0rc2
  * Support setting the `rpath` in the `cmake` module
  * Display a proper error message if the `node-api` download fails

# 1.4.99-9 2024-06-26
  * Use `npm_package_json` as a starting point instead of `npm_local_prefix` when searching for the Python DLL on Windows

# 1.4.99-8 2024-06-09
  * Fix building with static compiler runtime (`/MT`) on Windows

# 1.4.99-7 2024-06-07
  * Ignore `npm_config_prefix`

# 1.4.99-6 2024-06-06
  * Automatically parse the `npm_config_` `npm` install options

# 1.4.99-5 2024-06-05
  * Pass the auto-detected `ninja` to `CMake` allowing for transparent compatibility with the `ninja` xPack which uses `ninja.cmd`

# 1.4.99-4 2024-06-03
  * Downgrade Python to 3.10 for various reasons (`distutils` being the most important)
  * Implement the `PyInstaller` protocol, `meson` uses it
  * Ensure precedence over a pip-installed `meson`

# 1.4.99-3 2024-05-31
  * Include an `.exe` wrapper on Windows

# 1.4.99-2 2024-05-30
  * Fix the binary path

# 1.4.99-1 2024-05-29
  * First release with the git HEAD
