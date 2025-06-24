# Interschem

## Overview

**Interschem** is an interactive application designed for creating, visualizing, and editing logical diagrams. It provides a graphical interface for users to design flowcharts and generate corresponding C++ code based on the logical structure of the diagrams.

## Features

- **Graphical Interface**: Allows users to create and manipulate logical blocks such as `Start`, `Stop`, `Read`, `Write`, `Declare`, `Assign`, and `Condition`.
- **Code Generation**: Automatically generates C++ code based on the logical structure of the diagram.
- **Interactive Editing**: Supports adding, deleting, and modifying blocks and connections.
- **Error Handling**: Detects logical errors in the diagram and provides feedback.
- **Visualization**: Displays the logical diagram in real-time with customizable colors and styles.

## Project Structure

Interschem/ ├── InterSchem.cbp # Code::Blocks project file ├── InterSchem.depend # Dependency file ├── InterSchem.layout # Layout configuration file ├── main.cpp # Main source code ├── bin/ │ └── Debug/ │ └── InterSchem.exe # Compiled executable ├── obj/ │ └── Debug/ │ └── main.o # Object file

## Key Components

### `main.cpp`

The core logic of the application resides in `main.cpp`. It includes:

- **Block Initialization**: Functions like `initNod` and `initbloc` to define block properties and positions.
- **Drawing Functions**: Functions such as `deseneazaNod`, `deseneazabloc`, `drawLine`, and others for rendering blocks and connections.
- **Code Generation**: The `GenerareCod` function generates C++ code based on the logical diagram.
- **Event Handling**: Handles user interactions like mouse clicks and keyboard inputs.
- **Error Detection**: Validates the logical structure of the diagram and highlights errors.

### Logical Blocks

The application supports the following block types:

- **Start**: Entry point of the diagram.
- **Stop**: Exit point of the diagram.
- **Read**: Reads input values.
- **Write**: Outputs values.
- **Declare**: Declares variables.
- **Assign**: Assigns values to variables.
- **Condition**: Represents conditional logic.

### Code Generation

The `GenerareCod` function translates the logical diagram into C++ code. It supports:

- Variable declarations.
- Input/output operations.
- Conditional statements.
- Error handling for invalid diagrams.

## How to Run

1. Open the project in Code::Blocks using `InterSchem.cbp`.
2. Build the project to generate the executable.
3. Run the application from the `bin/Debug/InterSchem.exe` file.

## Dependencies

- **Graphics Library**: The application uses a graphics library for rendering the interface. Ensure the required library is installed and linked during compilation.

## Future Improvements

- Add support for more complex logical operations.
- Enhance the graphical interface with drag-and-drop functionality.
- Improve error detection and debugging features.
- Provide export options for diagrams in various formats.