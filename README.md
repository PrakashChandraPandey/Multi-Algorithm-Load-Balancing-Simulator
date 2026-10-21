Multi Algorithm Load Balancing Simulator

Project Overview
It is currently a terminal-based C++ project that demonstrates how incoming requests can be distributed among multiple servers using different load-balancing algorithms. It also simulates request processing, server failure and recovery, and adding servers during a simulation.


This phase focuses on the backend and terminal-based interaction. A graphical interface can be considered as a future enhancement.
Features
- Distributes requests using selectable load-balancing algorithms.
- Generates requests with processing times.
- Tracks active requests and waiting requests.
- Manages server capacity, weight, current load, and availability.
- Simulates server failure and recovery.
- Returns interrupted requests to the waiting queue when possible.
- Supports adding servers during the simulation.
- Displays server information and request queues in the terminal.
Load-Balancing Algorithms
- Round Robin: Selects eligible servers in cyclic order.
- Weighted Round Robin: Selects eligible servers according to their configured weights.
- Least Connections: Selects an eligible server with the lowest number of active requests/connections as counted by the implementation.



## Project Modules

The following list matches the source files in this repository.

| File | Responsibility |
|---|---|
| `ProjectHeaders.h` | Declares the ServerBase, Server, Request, CircularQueue, and LoadBalancer classes and their functions. |
| `data_structures.h` | Defines the C-compatible request data structure and fixed-size circular queue operations. |
| `Server_Module.cpp` | Implements the ServerBase constructor, derived Server constructor, and server display. |
| `Request_Module.cpp` | Implements request initialization, processing-time assignment, and conversion between C++ requests and the C request structure. |
| `Circular_Queue_Module.cpp` | Implements the C++ CircularQueue wrapper using functions from data_structures.h. |
| `Load_Balancer_Core_and_Algorithms.cpp` | Implements core load-balancer operations, algorithm selection, waiting-request assignment, and request processing. |
| `Round_Robin_Algorithm.cpp` | Implements Round Robin server selection. |
| `Weighted_Round_Robin_Algorithm.cpp` | Implements Weighted Round Robin server selection. |
| `Least_Connections_Algorithm.cpp` | Implements Least Connections server selection. |
| `Request_Generation_Module.cpp` | Generates requests, validates the selected algorithm, and assigns requests. |
| `Server_Display_Module.cpp` | Displays server details and status. |
| `Server_Failure_Module.cpp` | Handles server failure and returns interrupted requests to the waiting queue when possible. |
| `Server_Recovery_Module.cpp` | Reactivates failed servers and assigns waiting requests. |
| `Add_Server_Module.cpp` | Adds new servers with an ID, capacity, and weight. |
| `Queue_Display_Module.cpp` | Displays active and waiting requests. |

## Technologies and Concepts

- **Language:** C++
- **Programming Concepts:** Classes, Objects, Inheritance, and Modular Programming
- **Data Structures:** Vector and Circular Queue



Technologies and Conceptsader/source files, request processing, and server failure handling
Requirements
- GCC/MinGW C++ compiler with C++17 support
- Terminal or command prompt


Current Phase
The current version provides terminal-based interaction for testing the backend modules. A Qt-based graphical interface and visual representation of request distribution may be added in a later phase if required.
Future Enhancements
- Build a graphical interface using Qt.
- Visualize request distribution and server workloads.
Project Information
- Project type: Academic project
- Domain: Load balancing and systems programming
- Language: C/C++
