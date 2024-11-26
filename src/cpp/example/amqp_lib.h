#include <amqpcpp.h>
#include <amqpcpp/libev.h>
#include <ev.h>
#include <iostream>
#include <list>

#define AMQP_PREFIX "amqp://"
enum consumedMsgAction {
  ACK,
  REJECT,
};

typedef void (*consumer_callback_function)(const AMQP::Message &message,
                                           uint64_t deliveryTag,
                                           bool redelivered);

typedef struct amqpInstance {
  AMQP::TcpConnection *connection;
  AMQP::TcpChannel *channel;
  AMQP::LibEvHandler *handler;
} amqp_instance;
class AmqpWrapper {
private:
  AMQP::TcpConnection *connection;
  AMQP::TcpChannel *channel;
  AMQP::LibEvHandler *handler;
  std::string queue_name;
  AMQP::TcpConnection *get_connection_instance(AMQP::LibEvHandler *handler);
  AMQP::TcpChannel *get_channel_instance(AMQP::LibEvHandler *handler);

public:
  AmqpWrapper() {}
  AmqpWrapper(AMQP::LibEvHandler *handler, std::string url) : handler(handler) {
    std::string full_url = AMQP_PREFIX + url;
    connection =
        new AMQP::TcpConnection(handler, AMQP::Address(AMQP_PREFIX + url));
    channel = new AMQP::TcpChannel(connection);
  }
  AmqpWrapper(AMQP::LibEvHandler *handler, std::string url, uint64_t instances)
      : handler(handler) {
    std::string full_url = AMQP_PREFIX + url;
    connection =
        new AMQP::TcpConnection(handler, AMQP::Address(AMQP_PREFIX + url));
    channel = new AMQP::TcpChannel(connection);
  }

  void create_queue(std::string queue);

  void send_message(std::string msg);

  void consume_message();
  void consume_message(consumer_callback_function cf);
  void consume_message(enum consumedMsgAction);

  static AmqpWrapper *instance;

  static void queueCreationSuccessCallback();
  static void queueCreationFailCallback(const char *message);
  static void DumpMessage(const AMQP::Message &message, uint64_t deliveryTag,
                          bool redelivered);
};