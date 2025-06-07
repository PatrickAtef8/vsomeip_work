# SOME/IP and vSOMEIP Example Project

## Introduction to SOME/IP and vSOMEIP

**SOME/IP (Scalable service-Oriented MiddlewarE over IP)** is a communication protocol used primarily in automotive systems for service-oriented communication between Electronic Control Units (ECUs). It is designed to support the requirements of automotive applications, such as low-latency, reliable, and scalable communication over Ethernet. SOME/IP enables client-server interactions, event notifications, and remote procedure calls (RPCs) in a flexible and efficient manner, making it suitable for use cases like infotainment, Advanced Driver Assistance Systems (ADAS), and other in-vehicle networking needs.

**vSOMEIP** is an open-source implementation of the SOME/IP protocol, developed to provide a lightweight and efficient middleware for automotive and embedded systems. It is written in C++ and provides APIs for creating applications that communicate using SOME/IP. vSOMEIP supports features like service discovery, request-response communication, and event-based communication, making it a robust choice for implementing SOME/IP-based systems.

This project demonstrates a basic client-server communication using vSOMEIP, where a client sends a request to a server, and the server responds with a return code. The project includes configuration files, source code for both client and server, and a CMake build script to compile and link the applications.

## Project Structure

The project consists of the following files:

- `client.cpp`: Implements the client application that requests a service from the server.
- `client.hpp`: Header file for the client class.
- `server.cpp`: Implements the server application that offers a service and responds to client requests.
- `server.hpp`: Header file for the server class.
- `CMakeLists.txt`: CMake script to build the client and server applications.
- `server.json`: Configuration file for vSOMEIP, defining network and service parameters.

## Detailed Explanation of Code Components

### Client Implementation (`client.hpp` and `client.cpp`)

#### `client` Class

The `client` class encapsulates the vSOMEIP application logic for the client side.

- **Member Variables**:

  - `std::shared_ptr<vsomeip::application> app`: A smart pointer to the vSOMEIP application instance, representing the client application named "client".

- **Methods**:

  - **init()**:
    - Creates a vSOMEIP application instance with the name "client".
    - Registers an availability handler (`on_service_availability`) to detect when the server (service ID `0x4666`, instance ID `0x3000`) becomes available.
    - Registers a message handler (`on_message_handler`) to process responses from the server for the specified method ID (`0x6000`).
    - Initializes the vSOMEIP application.
    - Requests the service from the server using `request_service`.
    - Returns `true` to indicate successful initialization.
  - **start()**:
    - Starts the vSOMEIP application, enabling it to process messages and events.
  - **stop()**:
    - Unregisters the availability and message handlers.
    - Stops the vSOMEIP application, shutting down communication.

#### `on_service_availability` Function

- **Purpose**: Called when the availability of the server (service ID `0x4666`, instance ID `0x3000`) changes.
- **Parameters**:
  - `_service_id`: The ID of the service being monitored.
  - `_instance_id`: The instance ID of the service.
  - `_isAvailable`: A boolean indicating whether the service is available.
- **Behavior**:
  - Checks if the service and instance IDs match the expected values and if the service is available.
  - If available, it retrieves the client application instance, creates a request message with the specified service, instance, and method IDs (`0x6000`), and sends it to the server.
  - Prints a confirmation message to the console.

#### `on_message_handler` Function

- **Purpose**: Handles responses received from the server.
- **Parameters**:
  - `_response`: A shared pointer to the vSOMEIP message containing the server's response.
- **Behavior**:
  - Extracts the return code from the response using `get_return_code`.
  - Prints the return code to the console, indicating the server's response status.

#### `main` Function

- Creates an instance of the `client` class.
- Calls `init()` to initialize the client.
- Calls `start()` to begin communication.

### Server Implementation (`server.hpp` and `server.cpp`)

#### `server` Class

The `server` class encapsulates the vSOMEIP application logic for the server side.

- **Member Variables**:

  - `std::shared_ptr<vsomeip::application> app`: A smart pointer to the vSOMEIP application instance, representing the server application named "server".

- **Methods**:

  - **init()**:
    - Creates a vSOMEIP application instance with the name "server".
    - Registers an availability handler (`on_service_availability`) to monitor the server's own service availability (service ID `0x4111`, instance ID `0x3111`).
    - Registers a message handler (`on_message_handler`) to process incoming client requests for the specified method ID (`0x6000`).
    - Initializes the vSOMEIP application.
    - Offers the service using `offer_service`, making it available to clients.
    - Returns `true` to indicate successful initialization.
  - **start()**:
    - Starts the vSOMEIP application, enabling it to accept and process client requests.
  - **stop()**:
    - Unregisters the availability and message handlers.
    - Stops the vSOMEIP application, shutting down communication.

#### `on_service_availability` Function

- **Purpose**: Called when the server's service availability changes.
- **Parameters**:
  - `_service_id`: The ID of the service being monitored.
  - `_instance_id`: The instance ID of the service.
  - `_isAvailable`: A boolean indicating whether the service is available.
- **Behavior**:
  - Checks if the service and instance IDs match the server's IDs (`0x4111`, `0x3111`).
  - Prints a message indicating whether the server is available or not.

#### `on_message_handler` Function

- **Purpose**: Handles incoming requests from clients.
- **Parameters**:
  - `_request`: A shared pointer to the vSOMEIP message containing the client's request.
- **Behavior**:
  - Prints a message to confirm receipt of the client's request.
  - Retrieves the server application instance.
  - Creates a response message based on the client's request.
  - Sets the return code to `E_OK` (indicating success).
  - Sends the response back to the client.

#### `main` Function

- Creates an instance of the `server` class.
- Calls `init()` to initialize the server.
- Calls `start()` to begin offering the service.

### `server.json` Configuration File

The `server.json` file configures the vSOMEIP middleware for the server application. It defines:

- **unicast**: Specifies the IP address (`10.145.25.146`) used for unicast communication.
- **application**: Defines the server application with:
  - `name`: "server" (matches the application name in `server.cpp`).
  - `id`: `0x344` (unique application ID).
- **services**: Specifies the service offered by the server:
  - `service`: `0x4111` (service ID).
  - `instance`: `0x3111` (instance ID).
  - `unreliable`: `30452` (port for unreliable communication, typically UDP).
- **routing**: Specifies the routing application as "server".
- **service-discovery**: Configures service discovery:
  - `enable`: `true` (enables service discovery).
  - `multicast`: `224.224.224.111` (multicast address for service discovery).
  - `protocol`: `udp` (protocol used for service discovery).
  - `port`: `30509` (port for service discovery).

This configuration ensures that the server can advertise its service and communicate with clients over the specified network settings.

### `CMakeLists.txt`

The CMake script configures the build process for both client and server applications:

- Specifies configuration files (`vsomeip.json` and `vsomeip-local.json`) for vSOMEIP.
- Finds and links the required `vsomeip3` (version 3.5.5) and Boost libraries.
- Includes necessary directories for Boost and vSOMEIP.
- Creates two executables: `server` (from `server.cpp`) and `client` (from `client.cpp`).
- Links both executables with `vsomeip3` and Boost libraries.

## Project Workflow

1. **Server Startup**:

   - The server initializes and offers a service with ID `0x4111` and instance ID `0x3111`.
   - It registers handlers to monitor its availability and process incoming client requests.
   - The server starts and waits for client requests.

2. **Client Startup**:

   - The client initializes and requests a service with ID `0x4666` and instance ID `0x3000`.
   - It registers handlers to detect service availability and process server responses.
   - Upon detecting the server's availability, the client sends a request to the server's method ID `0x6000`.

3. **Communication**:

   - The server receives the client's request, processes it in `on_message_handler`, and sends a response with a return code (`E_OK`).
   - The client receives the response in `on_message_handler` and prints the return code.

4. **Service Discovery**:

   - The `server.json` configuration enables service discovery, allowing the client to find the server using multicast UDP on the specified address and port.

## How to Build and Run

1. **Prerequisites**:

   - Install `vsomeip3` (version 3.5.5 or higher).
   - Install Boost libraries.
   - Install CMake.
   - Ensure the vSOMEIP configuration files (`vsomeip.json`, `vsomeip-local.json`) are available in the specified path (`../../config/`).

2. **Build**:

   ```bash
    cmake -S . -B buildsomeip
    cmake --build buildsomeip
   ```

3. **Run the Server**:

   ```bash
   ./server
   ```

4. **Run the Client** (in a separate terminal):

   ```bash
   ./client
   ```

5. **Expected Output**:

   - Server: Prints "Server available" when it starts, and "Server request from client" when it receives a request.
   - Client: Prints "The Client service is available request method" when the server is detected, and "The Client Return code is: 0" when it receives the server's response.

## Notes

- The service and instance IDs in the client (`0x4666`, `0x3000`) and server (`0x4111`, `0x3111`) are different in the provided code, which may prevent communication unless corrected. Ensure that the client's requested service ID and instance ID match the server's offered service ID and instance ID.
- The `server.json` file should be adjusted to match the client's service and instance IDs if necessary.
- The project assumes a network configuration compatible with the specified IP address and ports.

1. This project serves as a minimal example of vSOMEIP-based communication, demonstrating the core concepts of SOME/IP, including service offering, requesting, and request-response handling.