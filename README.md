Multi Algorithm Load Balancing Simulator

Project Overview
Load Balancer Visualizer is a terminal-based C++ project that demonstrates how incoming requests can be distributed among multiple servers using different load-balancing algorithms. It also simulates request processing, server failure and recovery, and adding servers during a simulation.


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


Project Modules
The following list matches the source files in this repository.
File	Responsibility
ProjectHeaders.h	Declares the ServerBase, Server, Request, CircularQueue, and LoadBalancer classes and their functions.
data_structures.h	Defines the C-compatible request data structure and fixed-size circular queue operations.
Server_Module.cpp	Implements the ServerBase constructor, the derived Server constructor, and server display. ServerBase is implemented here; there is no separate server-base source file.
Request_Module.cpp	Implements request initialization, processing-time assignment, and conversion between C++ requests and the C request structure.
Circular_Queue_Module.cpp	Implements the C++ CircularQueue wrapper using the queue functions in data_structures.h.
Load_Balancer_Core_and_Algorithms.cpp	Implements core load-balancer operations, server lookup and eligibility checks, algorithm selection, waiting-request assignment, initialization, request processing, and pending-request checks.
Round_Robin_Algorithm.cpp	Implements Round Robin server selection.
Weighted_Round_Robin_Algorithm.cpp	Implements Weighted Round Robin server selection.
Least_Connections_Algorithm.cpp	Implements Least Connections server selection.
Request_Generation_Module.cpp	Generates requests, validates the selected algorithm, places requests in the waiting queue, and starts assignment.
Server_Display_Module.cpp	Displays the server list and their status.
Server_Failure_Module.cpp	Marks a server as failed and returns its active requests to the waiting queue when possible.
Server_Recovery_Module.cpp	Reactivates a failed server and attempts to assign waiting requests.
Add_Server_Module.cpp	Validates and adds a new server with an ID, capacity, and weight.
Queue_Display_Module.cpp	Displays active and waiting requests.


Technologies and Concepts
- Language: C++
- Programming concepts: Classes, objects, inheritance, and modular programming
- Data structures: vector and circular queue
- Other concepts: File separation through header/source files, request processing, and server failure handling
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
