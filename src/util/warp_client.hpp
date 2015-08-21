#pragma once

#include "zmq_util.hpp"
#include "warp_server.hpp"
#include "util/proto/warp_msg.pb.h"
#include <zmq.hpp>
#include <utility>
#include <memory>
#include <string>
#include <unordered_map>

namespace mldb {

struct WarpClientConfig {
  // E.g. "50.1.1.2".
  std::string server_ip;
};

class WarpClient {
public:
  // Server binds to a socket, while clients connect to it. The order of bind
  // and connect doesn't matter (but for inproc, which we don't use, order
  // matters).
  //
  // Client router socket's identity is set internally by zmq.
  explicit WarpClient(const WarpClientConfig& config);

  // Return success or not. Always async.
  bool Send(const std::string& data);

  // Receive from server (blocking).
  zmq::message_t Recv();

private:
  // Handshake with the server and get the client's client id. The first
  // connect and receive.
  void HandshakeWithServer();

private:
  std::unique_ptr<zmq::context_t> zmq_ctx_;
  std::unique_ptr<zmq::socket_t> sock_;
  std::string server_id_;

  // client id is rank among all clients. It only increase monotonically, so
  // missing rank means dead client.
  int client_id_{-1};
};

}  // namespace mldb