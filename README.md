# 🎮 so_long

> A 2D top-down graphical game developed in C using the MiniLibX engine, featuring event-driven input handling, tile-based map parsing, and recursive path validation algorithms.

## 📖 Overview

`so_long` is a low-level graphics and game engineering project designed to introduce event-driven programming, window management, and sprite rendering. The player navigates a character through a 2D grid map to collect all items before escaping through the exit, balancing game state logic with real-time user input and dynamic memory cleanup.

## ⚙️ Technical Constraints & Architecture

- **Language:** C (compiled with `gcc -Wall -Wextra -Werror`).
- **Graphics Library:** MiniLibX (X11/Cocoa API wrapper for window initialization, image buffer creation, dynamic texture rendering, and event hook registration).
- **Algorithmic Path Validation:** Recursive **Flood Fill** algorithm (Depth-First Search) to verify map solvability prior to window instantiation.
- **Memory & Resource Safety:** 100% leak-free execution. All image buffers, textures, window handles, display contexts, and dynamically allocated grid arrays are cleanly deallocated upon exit (audited via Valgrind).
- **Standards:** 100% compliant with 42's **Norminette** coding standard.

---

## ✨ Key Features & Gameplay Mechanics

- **Tile-Based World Rendering:** Converts 2D text maps into a grid of graphical sprites (player, walls, collectibles, floor tiles, and exit portal).
- **Event-Driven Input Engine:** Captures keyboard events (`W`, `A`, `S`, `D` / Arrow keys) and window destroy hooks (`ESC` key, window close button `X`) using MiniLibX event hooks (`mlx_hook`, `mlx_key_hook`).
- **Real-Time Step Counter:** Tracks and outputs total player movement counts to the terminal stream or screen overlay on every successful position update.
- **Strict Win/Loss State Logic:** Exit portal remains locked or inactive until all collectible elements (`C`) are retrieved from the grid.

---

## 🗺️ Map Format & Validation Rules

Maps are passed via `.ber` files containing a rectangular 2D grid. Before loading graphics, the engine executes strict syntactic and structural validation checks:

| Map Character | Description | Validation Rule |
| :---: | :--- | :--- |
| `1` | Wall | Map perimeter must be completely enclosed by walls. |
| `0` | Floor | Empty passable tile space. |
| `P` | Player Start | Must contain **exactly one** starting position. |
| `E` | Map Exit | Must contain **exactly one** exit portal. |
| `C` | Collectible | Must contain **at least one** collectible item. |

### Validation Pipeline

1. **Shape Integrity:** Verifies the map is rectangular and uniform in width.
2. **Perimeter Check:** Ensures top, bottom, left, and right borders are entirely composed of wall tiles (`1`).
3. **Element Count:** Enforces valid counts for `P` (1), `E` (1), and `C` ($\ge 1$).
4. **Flood Fill Solvability:** Runs a Depth-First Search algorithm on a duplicate grid to guarantee a valid path exists from `P` to all collectibles `C` and the exit `E`.

---

## 🛠️ Quickstart & Execution

### Prerequisites

MiniLibX requires system graphics and X11 development headers installed:

```bash
# Ubuntu / Debian
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev zlib1g-dev

# macOS (XQuartz / Native Cocoa frameworks)
