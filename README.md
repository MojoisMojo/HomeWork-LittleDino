# HomeWork-LittleDino

---

A dino-Game imitating the classic game, dino in Chrome. The picture of the dinosaur is got from Chrome, Delete if infringing

## Build with MSYS2 MINGW64

Use the SDL2 packages and compiler from the same MSYS2 MINGW64 environment.

Use a separate build directory for each configuration. Debug builds keep a
console for `printf` diagnostics; Release builds show only the game window.
The commands below create a Debug build. For a no-console Release build,
replace `build-debug` with `build-release` and `Debug` with `Release`.

In an MSYS2 MINGW64 terminal:

```sh
cmake -S . -B build-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/mingw64
cmake --build build-debug
```

In PowerShell, after adding the MSYS2 MINGW64 `bin` directory to `PATH`:

```powershell
$Msys2Mingw = Split-Path (Split-Path (Get-Command gcc).Source)
cmake -S . -B build-debug -G Ninja `
  '-DCMAKE_BUILD_TYPE=Debug' `
  "-DCMAKE_C_COMPILER=$Msys2Mingw/bin/gcc.exe" `
  "-DCMAKE_MAKE_PROGRAM=$Msys2Mingw/bin/ninja.exe" `
  "-DCMAKE_PREFIX_PATH=$Msys2Mingw"
cmake --build build-debug
```

The build output contains `DinoGame.exe` and copies the `image`, `font`, and
`data` resource directories beside it. The executable is not started by the
build.
