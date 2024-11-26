#include "amqp_lib.h"

class MyHandler : public AMQP::LibEvHandler {
public:
  MyHandler(struct ev_loop *loop) : AMQP::LibEvHandler(loop) {}

  // Override the onError method to handle connection errors
  virtual void onError(AMQP::TcpConnection *connection,
                       const char *message) override {
    std::cerr << "Connection error: " << message << std::endl;
  }
};

AMQP::TcpConnection *
AmqpWrapper::get_connection_instance(AMQP::LibEvHandler *handler) {
  AMQP::TcpConnection *connection = new AMQP::TcpConnection(
      handler, AMQP::Address("amqp://guest:guest@localhost/"));

  return connection;
}

AMQP::TcpChannel *
AmqpWrapper::get_channel_instance(AMQP::LibEvHandler *handler) {
  AMQP::TcpConnection *conn = get_connection_instance(handler);
  AMQP::TcpChannel *channel = new AMQP::TcpChannel(conn);
  return channel;
}

void AmqpWrapper::queueCreationSuccessCallback() {
  std::cout << "Queue created successfully! " << std::endl;
}
void AmqpWrapper::queueCreationFailCallback(const char *message) {
  std::cout << "Queue creation failed, reason: " << message << std::endl;
}
void AmqpWrapper::create_queue(std::string queue) {

  queue_name = queue;
  // channel->declareExchange("exchange_key", AMQP::direct);
  channel->declareQueue(queue_name, AMQP::durable)
      .onSuccess(queueCreationSuccessCallback)
      .onError(queueCreationFailCallback);
}
void AmqpWrapper::DumpMessage(const AMQP::Message &message,
                              uint64_t deliveryTag, bool redelivered) {
  std::string body(message.body(), message.bodySize());
  std::cout << "Received message: " << body << std::endl;
  std::cout << "Delivery Tag: " << deliveryTag << std::endl;
  std::cout << "Redelivered: " << redelivered << std::endl;
  std::cout << "Routing Key: " << message.routingkey() << std::endl;
  std::cout << "Exchange: "
            << (message.exchange().empty() ? "Default Exchange"
                                           : message.exchange())
            << std::endl;
}

void AmqpWrapper::send_message(std::string msg) {

  channel->publish("", queue_name, msg);
}

void AmqpWrapper::consume_message(consumer_callback_function cf) {

  channel->consume(queue_name).onReceived(cf);
}

void AmqpWrapper::consume_message() {
  AMQP::TcpChannel *channel_temp;
  channel_temp = channel;
  channel->consume(queue_name)
      .onReceived([channel_temp](const AMQP::Message &message,
                                 uint64_t deliveryTag, bool redelivered) {
        // Process the message
        DumpMessage(message, deliveryTag, redelivered);
        channel_temp->ack(deliveryTag);
      });
}

void AmqpWrapper::consume_message(enum consumedMsgAction flag) {
  AMQP::TcpChannel *channel_temp;
  channel_temp = channel;

  switch (flag) {
  case ACK:
    channel->consume(queue_name)
        .onReceived([channel_temp](const AMQP::Message &message,
                                   uint64_t deliveryTag, bool redelivered) {
          // Process the message
          DumpMessage(message, deliveryTag, redelivered);
          channel_temp->ack(deliveryTag);
        });
  case REJECT:
    channel->consume(queue_name)
        .onReceived([channel_temp](const AMQP::Message &message,
                                   uint64_t deliveryTag, bool redelivered) {
          // Process the message
          DumpMessage(message, deliveryTag, redelivered);
          channel_temp->reject(deliveryTag);
        });
    break;

  default:
    break;
  }
}