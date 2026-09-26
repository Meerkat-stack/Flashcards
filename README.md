# Flashcards CLI (C)

A lightweight, feature-rich command-line flashcard application written in C for effective vocabulary learning and practice.

## Key Features

- **Multiple File Formats:** Supports custom CSV files (with status tracking) and TXT files (simple `key=value` format).
- **Practice Modes:**
  - Learn all flashcards.
  - Practice only unlearned/new cards.
  - Practice known/learned cards.
- **Customization Options:**
  - Card shuffling and reverse mode (e.g., PL -> ENG / ENG -> PL).
  - Terminal ANSI color customization (toggleable).
  - Live session timer and session summary.
- **Progress Tracking:** Shows real-time progress, accuracy percentage, and elapsed session time.
- **Flexible Argument Parsing:** Robust CLI flag handling using pointers.

## Build & Installation

Ensure you have `gcc` (or another C compiler) and `make` installed.

### Quick One-Liner Setup
You can clone, prepare directories, and build the project with a single command:

```bash
git clone https://github.com/Meerkat-stack/Flashcards-CLI.git && cd Flashcards-CLI && mkdir -p bin && cd src && make
```

### Manual Build Instructions
1. Clone the repository and navigate into the project root:
   ```bash
   git clone https://github.com/Meerkat-stack/Flashcards-CLI.git
   cd Flashcards-CLI
   ```
2. Create the output directory for binaries (if not handled automatically by Makefile):
   ```bash
   mkdir -p bin
   ```
3. Navigate to the `src` directory and run `make`:
   ```bash
   cd src
   make
   ```

The compiled binary will be placed inside the `bin/` directory.


## Usage

```bash
./flashcards <source_file> [OPTIONS]
```

### Options:
| Flag | Description |
| :--- | :--- |
| `-a` | Practice all flashcards |
| `-i` | Practice only unlearned/new flashcards (default) |
| `-k` | Practice only known/learned flashcards |
| `-o <file>` | Save updated progress to a specific output file |
| `-s` | Sequential mode (disable card shuffling) |
| `-r` | Reverse flashcards direction |
| `-n` | Hide live timer (show total time spent in summary only) |
| `-c` | Colorless mode (disable ANSI colored output) |
| `-h, --help` | Display help message and exit |

### Quick Example:
```bash
# Practice unlearned cards in reverse mode from vocabulary.csv
./flashcards vocabulary.csv -r -i
```

## Practice Interface Example
During practice, the app provides real-time stats:
```text
[3/60] (50%) | T 00:02 | meerkat : 
```
- `[3/60]`: Current progress (Card / Total).
- `(50%)`: Live accuracy score.
- `T 00:02`: Elapsed session time.
- Type `/quit` at any prompt to exit and save progress.
