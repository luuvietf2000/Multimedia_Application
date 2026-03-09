# Multimedia Application (Qt Framework)

## Overview
- This project is a multifunction desktop application developed using the Qt framework. 
- The graphical user interface is built with QML, while the core logic and data processing are implemented in C++.
- The application integrates several practical features, including online music streaming, map-based location search and routing, real-time data visualization via UART communication, and an interactive Gomoku (Caro) game with both multiplayer and AI modes.
- The goal of this project is to demonstrate the integration of modern UI design with system-level programming and external service APIs in a single Qt-based application.

## Features

- **Online music streaming and downloading** via the Zing MP3 API.
- **Location search and route navigation** using OpenStreetMap and OSRM.
- **Real-time display of speed and energy metrics** through UART communication.
- **Gomoku (Caro) game** supporting:
  - PvP (Player vs Player)
  - PvE (Player vs AI) with an algorithm that selects optimal moves.
  
## Technologies
- **Qt Framework** – Cross-platform framework used for application development.
- **QML** – Declarative language used to design the graphical user interface.
- **C++** – Used for backend logic, data processing, and system interaction.
- **Zing MP3 API** – Provides online music streaming and downloading functionality.
- **OpenStreetMap** – Open-source map data used for location search and display.
- **OSRM (Open Source Routing Machine)** – Used for route calculation and navigation.
- **UART Communication** – Used to receive real-time speed and energy data from external hardware.

## Demo
https://github.com/user-attachments/assets/0a96b0e0-a1db-4752-8126-f69af882c15a

## Implementation
### Music Streaming Module
- User interactions are captured in the QML interface and forwarded to the C++ backend through signals and slots. 
- The backend performs asynchronous API requests to prevent blocking the UI thread. 
- After receiving the response, the data is processed in C++ and propagated back to the QML layer via signals, allowing the UI to update dynamically. 
- This event-driven architecture improves responsiveness and ensures a smooth user experience.

### Map and Navigation Module
- The application uses the Qt6 QML framework to implement the user interface and handle rendering. 
- Operations such as searching and API-based computations are processed in the C++ backend.
- After the processing is completed, the results are emitted through signals from C++ to the QML layer, 
- where the interface updates dynamically to display the returned data.

### UART Data Monitoring
- Speed and energy data are visualized in the QML interface, while a C++ ViewModel manages the underlying data.
- UART communication is handled in a separate thread to ensure non-blocking operation. 
- When new data is received via UART, the thread processes the incoming message and forwards it to the ViewModel.
- The ViewModel updates its properties in C++, and the QML interface automatically reflects these changes through Qt's property binding mechanism.

### Gomoku Game
- This module follows the same architecture as other parts of the application. 
- User interactions on the game board are handled by QML, while the game logic and data processing are implemented in C++.
- The win condition is determined by checking the two endpoints of a continuous line of pieces. This approach simplifies the calculation and improves performance.
- In PvE mode, the computer selects its moves based on a scoring evaluation strategy:
	+ Each possible position is evaluated based on both offensive and defensive scores, considering potential winning opportunities and blocking the opponent.
	+ A Breadth-First Search (BFS) algorithm is used to traverse neighboring positions around existing pieces to evaluate candidate moves.
	+ The AI then selects the position with the highest score as the optimal move.

## Limitations
- Although the core features of the application have been implemented, there are still several limitations.
- The user interface works correctly, but the internal data processing logic has not been sufficiently simplified. This makes it difficult to extend the system and add new features in the future.
- For the map module, OpenStreetMap is used because it is free and open-source. However, the accuracy and completeness of the data are sometimes limited, which makes it difficult to fully rely on for real-world applications.
- In the music module, the MP3 API used in the project is not officially public. Therefore, its long-term availability and stability cannot be guaranteed.
- For the Gomoku game, the AI decision-making process is purely deterministic. Since it always evaluates the board using the same scoring algorithm, repeating the same moves will lead to the same results, which can make the gameplay predictable and less engaging.

## Future Improvements
- Based on the current limitations of the project, several improvements can be considered in the future.
- First, the internal data processing architecture should be simplified and better structured. Applying a clearer design pattern (such as MVVM) would make the codebase easier to maintain and extend with new features.
- Second, the map module could be improved by integrating other map services or combining multiple data sources to increase accuracy and reliability for real-world usage.
- For the music module, a more stable and officially supported music API should be considered to ensure long-term usability and avoid potential service disruptions.- 
- Finally, the Gomoku AI can be enhanced by introducing randomness or more advanced algorithms such as Minimax with Alpha-Beta pruning. This would make the gameplay less predictable and more engaging for players.