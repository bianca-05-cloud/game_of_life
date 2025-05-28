# 🧬 Conway’s Game of Life

An implementation of John Conway’s Game of Life in **C**, showcasing how simple rules applied to data structures can generate complex behavior.

---

## 🚀 Features

- Implementation of the Game of Life using various data structures:
  - **Arrays**
  - **Linked Lists**
  - **Stacks**
  - **Queues**
  - **Trees**
  - **Graphs**
- Real-time observation of structural changes as the game evolves
- Modular and extensible C codebase

---

## 🧠 About the Project

This project is both an exploration of **data structures** and an implementation of a classic algorithm. It demonstrates how:
- Abstract data types behave under iterative logic
- Memory is managed and traversed in a low-level language like C
- Modular design can be applied in algorithmic simulations

---

## ⚙️ How It Works

**Conway’s Game of Life** is not a traditional game, but a **cellular automaton** — a mathematical model where cells evolve over discrete time steps according to a set of rules. It illustrates how complexity can emerge from simplicity.

### 🌱 The Grid

- The game is played on a 2D grid of **square cells**
- Each cell has **two states**: `alive` or `dead`
- Cells interact with their **eight neighbors** (horizontal, vertical, and diagonal)

### 📏 Game Rules

At each time step (called a **generation**), the state of each cell is updated according to the following rules:

1. 🏜️ **Underpopulation**: Any living cell with **fewer than two** living neighbors dies.
2. 🌿 **Survival**: Any living cell with **two or three** living neighbors stays alive.
3. 🔥 **Overpopulation**: Any living cell with **more than three** living neighbors dies.
4. 🌱 **Reproduction**: Any dead cell with **exactly three** living neighbors becomes a living cell.

> 📖 For additional details and project requirements, visit the official project page:  
> [https://site-pa.netlify.app/proiecte/game_of_life/](https://site-pa.netlify.app/proiecte/game_of_life/)

---

## 💻 Installation Instructions

### 🧰 System Requirements

To run the **checker tool**, you must have a Linux-based environment. If you're using **Windows** or **macOS**, you have two main options:

- **Windows**: Install the **Windows Subsystem for Linux (WSL)**, preferably with an Ubuntu distribution.
- **macOS**: Use a **Linux virtual machine** (e.g., via VirtualBox, UTM, or Parallels) or run Linux tools via Docker or a dual boot setup.

> ⚠️ Without a Linux environment, the checker may not function correctly, as it relies on Linux-specific tools and scripting behavior.

### 🧪 What Is the Checker?

The **checker** is an automated testing tool that compares the output of your implementation against the expected (reference) output. It validates correctness based on specific input and expected result files.

### 📦 How to Install the Checker

To install and use the checker, follow the instructions on its Git repository and downloud one of the following extensions, the one which matches you operation system:
- https://gitlab.cs.pub.ro/paaa/checker/-/jobs/artifacts/t1v1.1/raw/checker-linux-arm64?job=build:linux:arm64
- https://gitlab.cs.pub.ro/paaa/checker/-/jobs/artifacts/t1v1.1/raw/checker-linux-amd64?job=build:linux:amd64

## Dependencies

* `valgrind`
* `cppcheck`
* `git`

### Quick install

```bash
# Update the package repositories
sudo apt update

# Install valgrind
sudo apt install valgrind

# Install cppcheck
sudo apt install cppcheck

# Install git (if not already installed)
sudo apt install git
```

## Features

- [x] Parallel test running

- [x] Configuration
  - [x] Configurable tests
  - [x] Configurable modules
  - [x] User configuration
  - [x] Macros

- [x] Modules
  - [x] Module dependency checks
  - [x] Diff module
  - [x] Memory module _(valgrind backend)_
  - [x] Style module _(cppcheck backend)_
  - [x] Commit module _(git backend)_

- [x] Interface
  - [x] Basic - full module dump
  - [x] Interactive
    - [x] Live reload
    - [x] Module output visualization
      - [x] Side-by-side diff visualization
      - [x] Memory leak information

  
- [x] OS Compatibility
  - [x] `Linux / WSL` - full support
  - [ ] `OSX` - partial support _(no backend for the memory module)_
  - [ ] `Windows` - partial support _(no backend for the memory module)_

## Overview

### Running the checker

#### Basic
```bash
./checker
```

#### Interactive
```bash
./checker -i
```

### Navigating the interactive interface

* Use the `arrow keys` to navigate around
* Press `TAB` to switch between navigation and current section
* Press `ESC` to exit a fullscreen page
* Press `ESC` or `Ctrl+C` while on the main page to exit the program
* Press `~` to trigger a test run _(or modify the executable)_
* `Mouse` should be fully supported

### Configuration

Inside `config.json` or the `Options` tab you can modify the following:

* `Executable Path` - the executable that will be used to run the tests
* `Source Path` - the project root directory
* `Input Path` - the directory containing the input files
* `Output Path` - the directory where the test output will be stored
* `Ref Path` - the directory containing the reference files
* `Forward Path` - the directory where the `stdout` & `stderr` of each test will be stored
* `Valgrind` - whether to run the tests using valgrind or not _(disable for faster iteration)_
* `Tutorial` - display the tutorial again _(disabled afterward)_


🔗 [https://gitlab.cs.pub.ro/paaa/checker](https://gitlab.cs.pub.ro/paaa/checker)

This page provides detailed setup steps, usage guidelines, and troubleshooting tips.

---

## 📂 File structure and organization

- main.c: THE main part of the program, divided in four tasks using an if function, where variable T represent the number of task; here we applied the functions and we build the actuall program
- functions.c: all the functions utilised in the program;
- header.h: declariation of all data structure utillized and functions;
- 

## 📄 License

This project is open-source and available under the (LICENSE).



