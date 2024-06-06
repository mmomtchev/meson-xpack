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
