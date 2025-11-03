# CSV-Crunch

A tiny, fast C++23 command‑line tool for streaming CSV inspection. Start simple (row counting and header handling), then grow into filtering, statistics, histograms, and group‑by—step by step.

> This repository is intentionally incremental. Each mission adds a focused capability with clean commits and docs so you can follow the learning path.

---

## Features (current)

* ⚙️ **Streaming I/O**: reads CSV line‑by‑line (no full‑file loads).
* 🧭 **Header detection**: first line is treated as a header.
* 🪟 **CRLF tolerance**: trims trailing `\r` for Windows CSV files.
* 📤 **Clear diagnostics & exit codes**.

Planned next features (see Roadmap):

* CSV parsing (no quotes → full RFC4180-ish quotes/escapes)
* Online statistics (Welford mean/variance, online median)
* ASCII histograms
* Row filtering with a tiny expression language
* Group‑by aggregations

---

## Quickstart

### Build with CMake (recommended)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/csvsum data/sample.csv fare
```

> **Requires**: a C++23 compiler (GCC ≥ 13, Clang ≥ 16, or MSVC 19.36+), CMake ≥ 3.20.

### CLion

1. Put your CSVs in `data/` (or anywhere you like).
2. **Run → Edit Configurations…**

   * **Program arguments:** `data/sample.csv fare`
   * **Working directory:** `$ProjectFileDir$`
3. Run the target `csvsum`.

### Windows notes

* **MSVC (Visual Studio 2022 Build Tools):**

  * Use *Developer PowerShell* / *x64 Native Tools Prompt*.
  * Build: `cl /std:c++23 /O2 /W4 /EHsc main.cpp /Fe:csvsum.exe`
* **MSYS2 (g++):**

  * Install UCRT64 toolchain: `pacman -S --needed mingw-w64-ucrt-x86_64-toolchain`
  * Build: `g++ -std=c++23 -O2 -Wall -Wextra -pedantic main.cpp -o csvsum.exe`
* **WSL (Ubuntu):**

  * `sudo apt install g++` then `g++ -std=c++23 -O2 -Wall -Wextra -pedantic main.cpp -o csvsum`

---

## Usage

```
csvsum <file.csv> <column-name>
```

### Examples

```bash
# Count data rows (ignores empty lines)
./csvsum data/sample.csv fare
rows: 3
```

> The `column-name` is accepted early for future features (summary, hist, filter) and validates CLI shape. In current stage it is not used beyond the interface.

---

## Exit codes

* `0` — success
* `1` — usage error (not enough arguments)
* `2` — cannot open input file
* `3` — empty file (no header line)

Clear, script‑friendly semantics make it easy to integrate in pipelines.

---

## Development

### Code style

* C++23, warnings cranked up (`-Wall -Wextra -pedantic`).
* Trim Windows `\r` on input lines to avoid invisible tail characters.
* Prefer streaming and single‑pass algorithms for large files.

### Recommended directory layout (as the project grows)

```
.
├── app/              # CLI entrypoints (later)
├── include/          # public headers
├── src/              # implementations
├── tests/            # unit tests
├── data/             # sample CSVs
├── CMakeLists.txt
└── README.md
```

---

## Roadmap (incremental missions)

1. **Parser (no quotes)** — split on commas, preserve empty fields. — ✅
2. Quoted fields (embedded commas) — ✅
3. **Header lookup** — resolve column index by name.
4. **Online stats** — Welford mean/variance; online median (two heaps).
5. **ASCII histograms** — `hist <file> --col X --bins N`.
6. **Quoted CSV** — RFC4180-ish quotes and `""` escapes.
7. **Row filtering** — tiny expression language: `fare>50 && name=='Alice'`.
8. **Group‑by** — `--by <column>` with online aggregations per group.
9. **Parallel pipeline** — chunked reading + worker threads.

Each step will come with tests, docs, and a focused commit.

---

## Contributing

* Keep PRs small and focused.
* Add tests for every new feature or bugfix.
* Use conventional commit messages, e.g.:

  * `feat(parser): split by comma without quotes`
  * `fix(cli): print usage to stderr`
  * `test(stats): add welford edge cases`

---

## License

MIT © 2025
