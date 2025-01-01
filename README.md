# Qt Task List Application

A simple and intuitive task list application built with Qt. This application allows users to manage and organize their tasks, save them to files, and load them back when needed. It features task addition, task status toggling (strike-through), and file management.

## Features

- Add tasks to a list.
- Mark tasks as completed (strike-through).
- Save tasks to a `.tasks` file.
- Load tasks from a `.tasks` file.
- Simple user interface for easy task management.

## Requirements

- Qt 5.15 or later
- C++17 or later
- CMake 3.10 or later

## Clone the repository

```bash
git clone https://github.com/<your-username>/qt-todolist.git
cd qt-todolist
```

## Build the project

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Add Tasks
Use the input field and press the **"Add Task"** button to add a new task to the list.

### Mark Tasks as Completed
Click on a task to toggle its status. When marked as completed, the task will appear with a strike-through font style.

### Save Tasks
Provide a filename in the save input field and press the **"Save List"** button to save the list of tasks to a `.tasks` file.

### Load Tasks
Select a previously saved task list from the drop-down menu and press the **"Open"** button to load the tasks from the selected file.

## License

This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.

## Acknowledgments

- **Qt Framework** - For providing the powerful tools to create cross-platform applications.
- **CMake** - For simplifying the build process.

