# Digital Art Software
Digital Art Software is a Qt-based graphical application designed for creating and editing images through various drawing tools and shape selection options. It allows users to draw freehand lines, choose pen colors and widths, fill the screen with colors, and create predefined shapes such as rectangles, triangles, stars, and more. Users can also open and save images in multiple formats.

## Classes and Files Overview

1. **draw.h** and **draw.cpp**:
   - **draw** class inherits from `QWidget` and serves as the main widget for drawing on the application.
   - Features include handling mouse events (`mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`), painting shapes (`drawShape`), managing pen properties (`setPenColor`, `setPenWidth`), and image manipulation (`open_image`, `save_image`, `clearImage`, `resizeImage`).

2. **window.h** and **window.cpp**:
   - **window** class inherits from `QMainWindow` and acts as the main application window.
   - Manages menus (`file_menu`, `option_menu`), actions (`open_action`, `close_action`, etc.), and integrates the `draw` widget (`drawWindow`) as its central widget.
   - Includes functionality for opening (`open`), saving (`save`), selecting pen color (`penColor`), pen width (`penWidth`), and managing other options (`colorFill`, `addShape`, `clearScreen`).

## Key Functionality

- **Drawing:** Users can draw freehand lines by dragging the mouse, with options to set pen color and width.

  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/3a7bb5f5-2ee9-43c0-8bdd-7d926fb87e86)
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/95654160-1828-4f86-9a4b-87a34cd158ac)
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/aa0da279-a717-4a7d-bdb6-95be965a9b9b)

- **Shapes:** There's support for drawing predefined shapes (rectangle, square, diamond, etc.) at specified positions and dimensions.

  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/b09bbc60-5794-450a-b1a8-3955eecaa1ce)
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/6704dd91-6707-4486-8f71-b51ba8af3205)
  
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/9ef9f0ec-25cd-4893-bb95-a2805323c7a1)
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/09108ca6-79d9-41e2-bc07-bafc7b24f5d5)

- **File Operations:** Users can open existing images (`open`), save the current drawing (`save`), and export in various formats.

  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/514b56fc-bc01-4005-bb48-bff268b09291)
  
- **User Interface:** The application provides a menu-based interface (`file_menu`, `option_menu`) for intuitive interaction and configuration.
  
  ![image](https://github.com/dahze/Digital-Art-Software/assets/169538762/43a1be48-8697-496d-9cd0-420d770fa52c)

## Integration and Usage

- **Initialization:** Upon startup (`window` constructor), the main window is set up with menus and actions, and the drawing widget (`draw`) is instantiated and set as the central widget.
- **Event Handling:** Mouse events (`mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`) in `draw` handle drawing interactions.
- **Color Selection:** `QColorDialog` is used for selecting pen color (`penColor`) and fill color (`colorFill`).
- **Shape Drawing:** `QInputDialog` and predefined polygons (`drawShape`) facilitate drawing various shapes.
