# AVP_RohanChoudhary: Advanced Architectural Visualization Prototype

This repository contains the source code, assets, and project configurations for the **Unreal Engine 5.7 Architectural Visualization Prototype**. 

This project was built as part of the **Fujita Company Pre-Joining Training Program**. Although the allocated timeframe for completing the comprehensive training curriculum was **1 month (30 days)**, the entire implementation, including code development, UI configuration, performance profiling, and documentation, was successfully completed in **under 10 days**.

---

## 🚀 Program Acceleration Summary
- **Target Deadline**: 30 Days (1 Month)
- **Actual Completion**: **Under 10 Days**
- **Core Engine Version**: Unreal Engine 5.7 (C++ & UMG Blueprints)
- **Delivered Deliverables**: 20 distinct exercises implemented, verified, profiled, and consolidated into a final training report.

---

## 🛠️ Project Architecture & Core Modules

The project is structured into modular layers combining robust **Unreal C++** for core performance and data handling, with **UMG Blueprint subclasses** for visual layout and timeline adjustments.

### 1. Selection & Metadata Component Architecture
- **`UArchObjectInfoComponent` (C++)**: An actor component that encapsulates essential metadata (display names, descriptions, categories, rooms, floor area, material groups) for selectable actors.
- **CSV Data-Driven System**: Object properties are driven externally via [ArchObjectData.csv](file:///D:/Game%20Development/Projects/Unreal%20Projects/AVP_RohanChoudhary/Content/Data/ArchObjectData.csv). At runtime, object data is loaded dynamically into an Unreal Data Table. Missing or mismatched object IDs prompt clear UI warnings.
- **Review Notes Exporter (`ReviewNotes.csv`)**: Allows reviewers to click on objects, type feedback comments directly into a UMG panel in-game, and append them instantly to an RFC 4180-compliant CSV spreadsheet.

### 2. Interaction & Navigation System
- **Enhanced Input Context (IMC_Default)**: Utilizes Unreal Engine's Enhanced Input system to group 10 discrete actions (Look, Move, Sprint, Trace Select, Next/Previous Material, Play Presentation, Toggle UI, Toggle Furniture Data Layer, Slide Door).
- **Trace-Based Target Acquisition**: The viewer traverses the showroom floor in walking mode. Interaction is centered on a camera-based line trace: looking at an object highlights it, and pressing the interaction key selects it, dynamically releasing the mouse cursor for UI engagement.
- **Controls Hint Overlay (`WBP_ControlsOverlay`)**: On-screen overlay guides players with current inputs and feedback.

### 3. Material customization & Design Switcher
- **Dynamic Material board**: Wall, floor, and glass assets are driven by custom Master Materials and material instances, showcased in an in-level Sample Board.
- **Interactive UI Switcher (`WBP_DesignOptionSwitcher`)**: Pressing the `M` key opens a clean, centered selection grid enabling users to instantly swap furniture options, update the active selection outlines, and cycle materials.

### 4. Animation & Sequencer Presentations
- **Sliding Showroom Doors (`AArchAnimatedDoor`)**: Uses a C++ Timeline component connected to editable Blueprint curves to smoothly slide open door panels when hovered and activated with the `P` key.
- **Cinematic Showroom Flythrough (`S_Showroom_Presentation`)**: Automatically sweeps a Cine Camera through the showroom at level load to highlight architectural design points, seamlessly returning player control on completion.

---

## 📚 Exercise Breakdown (1.1 - 4.6)

The training reports consolidated in the final deliverable map to the following functional implementations:

### Milestone 1: Base Configurations & Project Setup
- **Ex 1.1**: Unreal Engine 5.7 prototype project creation.
- **Ex 1.2 & 1.3**: Clean folder hierarchy and rigid folder structure alignment.
- **Ex 1.4 & 1.5**: Struct declarations and basic 3D in-world tags.
- **Ex 1.7**: Reusable Blueprint Utility Library (`BPL_ArchVizUtilities`) written in C++.

### Milestone 2: Data Handling, Components & UI Panels
- **Ex 2.1**: Encapsulated actor component mapping (`UArchObjectInfoComponent`).
- **Ex 2.2**: C++ Type Practices (`TArray`, `TMap`, `FText`) for debugging.
- **Ex 2.3**: CSV Import validation and dynamic Data Table lookups.
- **Ex 2.4**: C++ CSV File Exporter for client review logs.
- **Ex 2.5**: Master Materials and in-level material variation board.
- **Ex 2.6**: Metadata-bound UMG Info Panel (`WBP_ObjectInfoPanel`).

### Milestone 3: Navigation, Enhanced Input & Layers
- **Ex 3.2**: Unified Keyboard/Mouse and Gamepad Enhanced Input mapping configurations.
- **Ex 3.3**: Walking character controller boundaries and sprint settings.
- **Ex 3.4**: Immersion-focused camera line-trace selection system.
- **Ex 3.6**: Data Layers integration for dynamic runtime variation loading (toggled via `L`).

### Milestone 4: Architecture Animations, Switching & Profiling
- **Ex 4.1**: C++ timeline-driven animated sliding showroom door.
- **Ex 4.2**: Selective animation triggers targeting hovered/nearest door (toggled via `P`).
- **Ex 4.3**: Cinematic level flythrough using Level Sequence bindings.
- **Ex 4.4**: Centered multi-option design switcher UI (toggled via `M`).
- **Ex 4.5**: Post-processing lighting pass, contrast control, and mirror reflections.
- **Ex 4.6**: Performance evaluation using stat counters and Unreal Insights (stable 60 FPS).

---

## 🎮 How to Interact with the Prototype

Launch the project map in the Unreal Editor and play to interact using the following binds:

| Action / Control | Input (Keyboard/Mouse) | Description |
| :--- | :--- | :--- |
| **Movement** | `W` `A` `S` `D` | Traverse the showroom floor |
| **Sprint** | `Shift` (Hold) | Toggle run speed |
| **Camera View** | Move Mouse | Look around (first-person walking mode) |
| **Select / Interact** | `Left Click` or `E` | Select the highlighted object under the crosshair |
| **Slide Door** | `P` | Open/Close nearest or selected sliding door |
| **Design switcher** | `M` | Open/Close the centered furniture layout switcher UI |
| **Toggle Data Layer** | `L` | Load/unload layout variants dynamically |
| **Toggle UI Mode** | `Tab` | Release mouse cursor for manual menu clicking |

---

## 📝 Training Documentation
The unified report compiling detailed summaries, implementation walkthroughs, C++ code listings, database schemas, and performance graphs for all exercises is available at:
👉 **[Final_Training_Report.docx](file:///D:/Game%20Development/Projects/Unreal%20Projects/AVP_RohanChoudhary/Final_Training_Report.docx)** (24.5 MB)
