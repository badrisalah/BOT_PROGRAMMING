# 🌳 Codingame Gold League Bot

A C++ bot developed for a Codingame multiplayer challenge that reached **Gold League** using a lightweight heuristic strategy centered around efficient harvesting and early expansion.

---

## Overview

The bot follows a simple resource-management approach:

- Locate the player's shack.
- Plant trees around the shack during the opening.
- Harvest the nearest fruit-bearing trees.
- Return harvested fruit to the shack.
- Train new trolls whenever resources permit.

Despite relying on greedy decision making instead of advanced AI techniques, the bot achieved **Gold League**.

---

## Strategy

### Early Game

- Detect the shack location.
- Reserve the four adjacent tiles for planting.
- Assign the first troll as a dedicated planter.
- Harvest a fruit to obtain a tree type.
- Plant trees around the shack.

### Mid Game

Once all planting spots are filled:

- Every troll harvests the closest available tree.
- Trolls carrying fruit immediately return to the shack.
- Empty trolls continue harvesting.

### Expansion

The bot trains additional trolls whenever enough resources are available, up to **three workers**.

---

## Troll Roles

### First Troll

- Plants trees around the shack.
- Switches to harvesting after all planting spots are occupied.

### Remaining Trolls

- Harvest the nearest fruit-bearing tree.
- Deliver harvested fruit to the shack.
- Repeat.

---

## Decision Making

Each game turn the bot:

1. Reads the current game state.
2. Collects all trees containing fruit.
3. Calculates the nearest target for each troll.
4. Generates one of the following commands:

- `MOVE`
- `HARVEST`
- `PLANT`
- `DROP`
- `TRAIN`
- `WAIT`

Tree selection is performed by sorting trees according to their squared Euclidean distance from each troll.

---

## Features

- ✅ Automatic shack detection
- ✅ Dedicated early-game planter
- ✅ Automatic harvesting
- ✅ Automatic resource delivery
- ✅ Automatic troll training
- ✅ Greedy nearest-tree targeting
- ✅ Lightweight implementation
- ✅ Gold League capable

---

## Technologies

- C++17
- Standard Template Library (STL)

Libraries used:

- `vector`
- `map`
- `algorithm`
- `string`

---

## Performance

**Highest League Achieved**

🥇 **Gold League**

The implementation intentionally favors simplicity, resulting in fast execution while remaining competitive.

---

## Future Improvements

- Smarter target assignment to avoid multiple trolls choosing the same tree.
- Better pathfinding.
- Opponent-aware strategies.
- Improved planting decisions.
- Dynamic worker management.
- Resource prioritization.

---

## Project Structure

```text
.
├── main.cpp
└── README.md
```

---

## Author

Developed as a Codingame AI bot focused on demonstrating how effective simple heuristic algorithms can be in competitive programming.