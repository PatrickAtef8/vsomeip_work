# vSOME/IP Example Project

This project demonstrates a simple client-server communication using the **vSOME/IP** (Scalable service-Oriented MiddlewarE over IP) library, commonly used in automotive and IoT applications for service-oriented communication. The project consists of two executables: a **server** that offers a service and a **client** that requests the service. The communication is configured using a JSON configuration file (`vsomeip-local.json`).

## Project Structure

The project includes the following files:

- **client.cpp**: Implements the client application that discovers and communicates with the server.
- **client.hpp**: Header file for the client class, defining its interface.
- **server.cpp**: Implements the server application that provides a service and responds to client requests.
- **server.hpp**: Header file for the server class, defining its interface.
- **CMakeLists.txt**: CMake configuration file to build the project.
- **vsomeip-local.json**: Configuration file for vSOME/IP, specifying network and service discovery settings.

Below is a detailed explanation of each file and its role in the project.

---

## Code Files Explanation

### 1. `client.cpp` and `client.hpp`

#### Overview
The `client.cpp` file implements a vSOME/IP client that discovers a service offered by the server and sends a request to it. The `client.hpp` file defines the `client` class, which encapsulates the vSOME/IP application logic.

#### Key Components
- **Constants**:
  - `service_id` (`0x4111`): Identifies the service the client is looking for (matches the server’s service ID).
  - `instance_id` (`0x3111`): Identifies the specific instance of the service (matches the server’s instance ID).
  - `method_id` (`0x6000`): Identifies the method to call on the server.
- **Handlers**:
  - `on_service_availability`: Logs service availability and, when the service (`0x4111`, `0x3111`) becomes available, creates and sends a request to the server.
  - `on_message_handler`: Processes the server’s response, printing the return code and its enum name (e.g., `E_OK` for `0`).
- **Client Class Methods**:
  - `init()`: Initializes the vSOME/IP application, registers handlers, and requests the service.
  - `start()`: Starts the vSOME/IP application, enabling communication.
  - `stop()`: Unregisters handlers and stops the application.
- **Main Function** (in `client.cpp`):
  - Creates a `client` object, initializes it, and starts it if initialization succeeds.

#### Functionality
The client:
1. Initializes a vSOME/IP application named "client".
2. Registers handlers to monitor service availability and process responses.
3. Requests the service identified by `service_id` (`0x4111`) and `instance_id` (`0x3111`).
4. Upon service availability, sends a request to the server’s method (`method_id`).
5. Prints the return code from the server’s response with its enum name.

---

### 2. `server.cpp` and `server.hpp`

#### Overview
The `server.cpp` file implements a vSOME/IP server that offers a service and responds to client requests. The `server.hpp` file defines the `server` class, which encapsulates the server logic.

#### Key Components
- **Constants**:
  - `service_id` (`0x4111`): Identifies the service offered by the server.
  - `instance_id` (`0x3111`): Identifies the specific instance of the service.
  - `method_id` (`0x6000`): Identifies the method clients can call.
- **Handlers**:
  - `on_service_availability`: Logs service availability changes for debugging (e.g., the server’s own service).
  - `on_message_handler`: Processes client requests, creates a response with a success return code (`E_OK`), and sends it back.
- **Server Class Methods**:
  - `init()`: Initializes the vSOME/IP application, registers handlers, and offers the service.
  - `start()`: Starts the vSOME/IP application.
  - `stop()`: Unregisters handlers and stops the application.
- **Main Function** (in `server.cpp`):
  - Creates a `server` object, initializes it, and starts it if initialization succeeds.

#### Functionality
The server:
1. Initializes a vSOME/IP application named "server".
2. Registers handlers to monitor availability (optional) and process client requests.
3. Offers a service identified by `service_id` (`0x4111`) and `instance_id` (`0x3111`).
4. Upon receiving a client request, sends a response with a success code.

---

### 3. `CMakeLists.txt`

#### Overview
The `CMakeLists.txt` file configures the build process for the project using CMake.

#### Key Components
- **Minimum CMake Version**: Requires CMake 3.5 or higher.
- **Project Name**: Defines the project as `vsomeip_example`.
- **Dependencies**:
  - Finds the `vsomeip3` library (required for vSOME/IP functionality).
  - Finds the `Boost` library (required for vSOME/IP dependencies).
- **Include Directories**: Adds include paths for Boost and vSOME/IP headers.
- **Configuration File Copy**: Copies `vsomeip-local.json` to the build directory for runtime use.
- **Executables**:
  - Creates `server` executable from `server.cpp`.
  - Creates `client` executable from `client.cpp`.
- **Linking**: Links both executables with `vsomeip3` and `Boost` libraries.

#### Functionality
This file ensures the project is built with the correct dependencies and configurations, producing `server` and `client` executables.

---

### 4. `vsomeip-local.json`

#### Overview
The `vsomeip-local.json` file configures the vSOME/IP runtime environment, specifying network settings and service discovery parameters.

#### Key Components
- **Unicast**: Sets the IP address to `127.0.0.1` (localhost).
- **Applications**: Defines the "server" application with ID `0x1111`.
- **Routing**: Specifies "server" as the routing manager.
- **Service Discovery**:
  - Enabled with `"enable": "true"`.
  - Uses multicast address `224.224.224.245` and port `30490` for service discovery.

#### Functionality
This configuration ensures that the server and client communicate over localhost, with the server acting as the routing manager and service discovery enabled via multicast.

---

## Prerequisites

To build and run this project, you need:

- **CMake**: Version 3.5 or higher.
- **vSOME/IP**: Version 3.x library installed (e.g., at `/home/patrick/Patrick_Storage/vsomeip/vsomeip-3.5.5/build`).
- **Boost**: Required by vSOME/IP.
- **C++ Compiler**: Supporting C++11 or higher (e.g., GCC).
- **Linux Environment**: The instructions are tailored for Ubuntu or similar.

---

## Build Instructions

Follow these steps to build the project:

1. **Create a build directory**:
   ```bash
   mkdir -p buildsomeip
   ```

2. **Configure the project with CMake**:
   ```bash
   cmake -S . -B buildsomeip
   ```
   This generates build files in the `buildsomeip` directory.

3. **Build the executables**:
   ```bash
   cmake --build buildsomeip
   ```
   This compiles `server` and `client` executables in `buildsomeip/`.

---

## Environment Setup

To ensure the vSOME/IP library is found at runtime, update the `LD_LIBRARY_PATH`:

1. **Add vSOME/IP library path to your shell**:
   ```bash
   echo 'export LD_LIBRARY_PATH=/home/patrick/Patrick_Storage/vsomeip/vsomeip-3.5.5/build:$LD_LIBRARY_PATH' >> ~/.bashrc
   ```

2. **Reload the shell environment**:
   ```bash
   source ~/.bashrc
   ```

**Note**: Replace `/home/patrick/Patrick_Storage/vsomeip/vsomeip-3.5.5/build` with the actual path to your vSOME/IP build directory.

---

## Run Instructions

1. **Navigate to the build directory**:
   ```bash
   cd buildsomeip
   ```

2. **Start the server**:
   ```bash
   VSOMEIP_CONFIGURATION=$(pwd)/vsomeip-local.json ./server
   ```
   - The `VSOMEIP_CONFIGURATION` environment variable specifies the configuration file.
   - The server will initialize, offer the service, and wait for client requests.

3. **Open another terminal and start the client**:
   ```bash
   cd buildsomeip
   VSOMEIP_CONFIGURATION=$(pwd)/vsomeip-local.json ./client
   ```
   - The client will discover the server, send a request, and print the response.

---

## Expected Behavior

1. The server starts and offers a service (ID `0x4111`, instance `0x3111`).
2. The client starts, detects the server’s service, and sends a request to method `0x6000`.
3. The server receives the request and responds with a success code (`E_OK`).
4. The client prints the return code from the server’s response.

Example console output:

**Server**:
```
2025-06-07 ... server [info] Using configuration file: ".../vsomeip-local.json".
2025-06-07 ... server [info] Application(server, 1111) is initialized (11, 100).
2025-06-07 ... server [info] OFFER(1111): [4111.3111:0.0] (true)
Service [4111.3111] is available.
2025-06-07 ... server [info] Application/Client 0101 is registering.
2025-06-07 ... server [info] REQUEST(0101): [4111.3111:255.4294967295]
Server received a request from client.
```

**Client**:
```
2025-06-07 ... [info] Application(client, ffff) is initialized (11, 100).
2025-06-07 ... [info] Application/Client 0101 (client) is registered.
Service [4111.3111] is available.
The Client service is available, sending request...
Client received response. Return code: 0 (E_OK)
```

---

## Notes

- **Service IDs**: The client and server both use `service_id` `0x4111` and `instance_id` `0x3111`, ensuring successful communication.
- **Server Availability Handler**: The server logs its own service availability for debugging. This can be removed if not needed by skipping the `register_availability_handler` call in `server.cpp`.
- **Return Code Logging**: The client’s `on_message_handler` includes the return code’s enum name (e.g., `E_OK`) for clarity.
- **Configuration File**: The `vsomeip-local.json` file is copied to the build directory during the build. Ensure it is correctly referenced in the `VSOMEIP_CONFIGURATION` variable.
- **Enhancements**: Consider adding payload processing or error handling for more complex scenarios.

---

## Troubleshooting

- **Library Not Found**: Ensure `LD_LIBRARY_PATH` includes the vSOME/IP build directory.
- **Service Not Discovered**: Verify that both client and server use the same `service_id` and `instance_id`, and that `vsomeip-local.json` is correctly configured.
- **CMake Errors**: Ensure `vSOME/IP` and `Boost` are installed and found by `CMake`.
- **Runtime Errors**: Check that the JSON configuration file is in the build directory and accessible.
- **Stray Processes**: If unexpected behavior occurs, check for running vSOME/IP processes and terminate them:
  ```bash
  ps aux | grep vsomeip
  killall server client
  ```

---

