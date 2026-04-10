# TicTacToeGame

## Building the Project

All build commands are run from the **project root** directory.
CMake separates *configuring* (reading `CMakeLists.txt` and generating Makefiles)
from *building* (actually compiling the code). You run configure once, then build as many times as needed.

### Debug build (default)

Use this during development. Compiles with `-g` (debug symbols), no optimization.
Breakpoints, step-through, and variable inspection all work correctly.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

After the first configure, you can rebuild with just:

```bash
cmake --build build
```

The binary is placed at `build/TicTacToeGame`.

### Release build

Use this for a final/production binary. Compiles with `-O3` and strips debug info.
Smaller and faster, but breakpoints will not work.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Building from VSCode

- **Ctrl+Shift+B** — runs the default CMake build task (defined in `.vscode/tasks.json`)
- **F5** — builds then launches the debugger (defined in `.vscode/launch.json`)

The CMake Tools extension must be installed (`ms-vscode.cmake-tools`) and a Kit selected
(Ctrl+Shift+P → `CMake: Select a Kit`).

---

### Deleting the cache and reconfiguring

The CMake cache (`build/CMakeCache.txt`) stores the values you passed at configure time
(build type, compiler path, flags, etc.). It is read on every build, not just the first one.

**When to delete the cache and reconfigure:**

| Situation | Why reconfigure is needed |
|---|---|
| Switching between Debug and Release | `CMAKE_BUILD_TYPE` is cached; the old value is reused unless you override it |
| Changing the compiler or toolchain | The old compiler path is stored in the cache |
| Adding a new dependency or CMake option | The cache won't pick up new `find_package` calls or option defaults |
| CMake errors that persist after fixing `CMakeLists.txt` | Stale cached values can hide the fix |
| Moving or renaming the project folder | Absolute paths stored in the cache become invalid |

**How to delete the cache:**

From the terminal:
```bash
# From the project root
rm -rf build/CMakeFiles build/CMakeCache.txt
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

From VSCode (CMake Tools extension):
```
Ctrl+Shift+P → CMake: Delete Cache and Reconfigure
```
This wipes `CMakeCache.txt` and `CMakeFiles/`, then immediately re-runs configure.

> You do **not** need to reconfigure just because you added or edited `.cpp` files —
> only changes to `CMakeLists.txt` or build settings require it.

---

## The `build/CMakeFiles/` Folder

`CMakeFiles/` is generated entirely by CMake during the configure step. You never edit
anything inside it. It is safe to delete the whole folder and regenerate it with `cmake -B build`.

### What it contains

```
build/CMakeFiles/
├── 4.3.1/                        # CMake version marker — identifies which CMake generated this cache
├── CMakeConfigureLog.yaml        # Full log of the configure run; useful for diagnosing configure errors
├── CMakeDirectoryInformation.cmake  # Internal: relative path info for this directory
├── Makefile.cmake                # Internal: rules for the top-level Makefile
├── Makefile2                     # Internal: secondary Makefile with per-target rules
├── TargetDirectories.txt         # List of all directories that contain a CMake target
├── cmake.check_cache             # Internal: used by CMake to detect when a reconfigure is needed
├── InstallScripts.json           # Install rules (empty here since we have no install() calls)
├── pkgRedirects/                 # Reserved for package manager integration
├── progress.marks                # Tracks build progress percentage
│
└── TicTacToeGame.dir/                  # Per-target folder for the "TicTacToeGame" executable
    ├── Program.cpp.o             # Compiled object file for Program.cpp
    ├── Program.cpp.o.d           # Dependency file: lists headers Program.cpp depends on
    │                             #   — used to trigger a rebuild when a header changes
    ├── CommandParser.cpp.o       # Object file for CommandParser.cpp
    ├── CommandParser.cpp.o.d     # Dependency file for CommandParser.cpp
    ├── ...                       # (one .o and .o.d per source file)
    ├── flags.make                # Compiler flags used for this target (CXXFLAGS, include paths)
    ├── link.txt                  # The exact linker command used to produce the final binary
    ├── build.make                # Make rules for building this target's object files
    ├── DependInfo.cmake          # Tracks which source files belong to this target
    ├── compiler_depend.make      # Auto-generated header dependency rules (from .o.d files)
    ├── compiler_depend.internal  # Internal state for incremental dependency tracking
    ├── compiler_depend.ts        # Timestamp used to detect when dependencies need refreshing
    ├── cmake_clean.cmake         # Script that lists files to remove on `cmake --build . --target clean`
    └── depend.make               # Legacy dependency tracking (superseded by compiler_depend)
```

### Why are object files (`.o`) stored here?

Each `.cpp` file is compiled into a separate `.o` (object file) first.
Only after all `.o` files are ready does the linker combine them into the final `TicTacToeGame` binary.
This enables **incremental builds**: if you change one `.cpp` file, only that file's `.o` is
recompiled, and then the linker re-links. The rest of the object files are reused as-is.

### Why are dependency files (`.o.d`) stored here?

When a `.cpp` file includes a header (`#include "Board.h"`), the compiler records that
dependency in a `.o.d` file. On the next build, Make reads these files and knows to recompile
`SomeFile.cpp` if `Board.h` changed — even though `SomeFile.cpp` itself was not modified.
Without these files, header changes would silently not take effect until a full rebuild.
