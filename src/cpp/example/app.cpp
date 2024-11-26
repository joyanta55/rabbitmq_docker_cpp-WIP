#include "amqp_lib.h"

void messageCallback(const AMQP::Message &message, uint64_t deliveryTag,
                     bool redelivered) {
  std::string msg(message.body(), message.bodySize());
  
  std::cout << "Received message: " << msg << "Delivery tag "<<deliveryTag<<std::endl;
  std::cout<<"Exchange "<<message.exchange()<<std::endl;
  std::cout<<"Routing "<<message.routingkey()<<std::endl;
}


int main() {
  // access to the event loop
  auto *loop = EV_DEFAULT;


  // handler for libev (so we don't have to implement AMQP::TcpHandler!)
  AMQP::LibEvHandler handler(loop);

  AmqpWrapper amqpwrapper(&handler, "test:test@172.17.0.1");

  amqpwrapper.create_queue("test_queue1");

  amqpwrapper.send_message("Hello World, this is Joyanta!! Test 2");

  //amqpwrapper.consume_message(messageCallback); //messageCallback is the callback implemented above).
  //amqpwrapper.consume_message(); // consume the message.
  //amqpwrapper.consume_message(ACK); //consume and ack the message. (i.e. channel->ack). 
  amqpwrapper.consume_message(REJECT); //consume and reject the message. (i.e. channel->reject).
  ev_run(loop, 0);

  // done
  return 0;
}