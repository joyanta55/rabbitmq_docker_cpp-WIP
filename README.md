# rabbitmq_docker_cpp
A Bazel template to create Docker images for C++ applications using AMQP-CPP (https://github.com/CopernicaMarketingSoftware/AMQP-CPP). The `src/cpp/example` directory includes a sample file, `app.cpp`, which is built and packaged into a Docker container for the local Docker registry. This setup is dependency-free — all required headers and AMQP-CPP implementations can be handled directly in the `app.cpp` file.

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
