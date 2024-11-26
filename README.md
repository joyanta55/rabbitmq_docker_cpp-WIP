# rabbitmq_docker_cpp
A Bazel template to create Docker images for C++ applications using AMQP-CPP (https://github.com/CopernicaMarketingSoftware/AMQP-CPP). The `src/cpp/example` directory includes a sample file, `app.cpp`, which is built and packaged into a Docker container for the local Docker registry. This setup is dependency-free — all required headers and AMQP-CPP implementations can be handled directly in the `app.cpp` file.

# Usage Scenarios and Practical Applications

This repository provides a foundation for building and deploying C++ applications using the AMQP-CPP library. Below are some practical scenarios where this repository can be applied:

## 1. Message Publishing Service
- **Scenario**: A microservice that sends notifications, logs, or events to a message broker (RabbitMQ) for other systems to consume.
- **Example Use Case**:
  - A logging service that aggregates application logs and publishes them to RabbitMQ.
  - Notifications for user actions, such as order confirmations or alerts, are sent to a queue for email or SMS processing.

## 2. Message Consumer Service
- **Scenario**: A microservice that listens to a RabbitMQ queue and processes incoming messages.
- **Example Use Case**:
  - A worker service that consumes messages from a task queue and executes background tasks (e.g., image processing, data analysis).
  - A real-time chat application backend that consumes messages from a queue and relays them to connected clients.

## 3. Prototyping and Testing RabbitMQ Workflows
- **Scenario**: Developers who want to quickly prototype and test RabbitMQ message workflows in a containerized environment.
- **Example Use Case**:
  - Prototyping a queue-based workflow for data ingestion and validation.
  - Testing RabbitMQ configurations and connection handling using the example application.

## 4. Containerized C++ Microservices
- **Scenario**: Deployment of microservices written in C++ with RabbitMQ integration in Dockerized environments.
- **Example Use Case**:
  - A lightweight, scalable Docker container that publishes and consumes messages in distributed applications.
  - Integration of RabbitMQ into a Kubernetes cluster for highly available message brokering.

## 5. Performance Benchmarking
- **Scenario**: Testing the performance of RabbitMQ-based messaging workflows in C++.
- **Example Use Case**:
  - Benchmarking message throughput between producers and consumers.
  - Analyzing the latency of RabbitMQ interactions under high traffic.

By leveraging this repository, developers can implement and deploy these scenarios with minimal setup. The example `app.cpp` provides a starting point for extending functionality to suit specific needs.




## Build instruction

All it needs to run is to run the following command
```
bazel run //src/cpp:amqp_image_ubuntu_cpp
```

This would create a docker image, so you can see that by the `docker images` command. For the base docker image, I choose ubuntu 20.04. This can be modified at the `WORKSPACE` file. To create centos based amqp docker image  
```
bazel run //src/cpp:amqp_image_centos_cpp
```
The centos version used is 6.6. Again this can be changed at `WORKSPACE` file.

To see the created images
```
docker images
```

## Example

In my case I see the follwing docker image, when I type `docker images` in my machine.
```
bazel/src/cpp   amqp_image_ubuntu_cpp   f5562587940b
```

To run the docker image, 
```
docker run -it f5562587940b
```

And the output is shown as:
```
Queue created successfully! 
Received message: Hello World, this is Joyanta!! Test 2
Delivery Tag: 1
Redelivered: 0
Routing Key: test_queue1
Exchange: Default Exchange
```
**src/cpp/example/app.cpp** serves as a placeholder with minimal implementation. The IP and user in this example correspond to my RabbitMQ server configuration. To set up a RabbitMQ server on Debian, refer to the official installation guide. For more advanced usage, visit the AMQP-CPP documentation (https://github.com/CopernicaMarketingSoftware/AMQP-CPP).

The necessary Bazel rules are already configured to handle all header and library dependencies. Simply update **app.cpp** with your custom logic and run `bazel run` to build and load the Docker image.
