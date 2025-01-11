#pragma once
#include "classes/socket.h"
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <thread>

using MessageHandler = std::pair<std::thread, std::thread>;
using InputHandler = std::function<void(std::string)>;
using OutputGetter = std::function<std::string()>;
using LoopEnder = std::function<bool()>;

void tryNetworkingFunction(const std::function<void()>& function);
MessageHandler getMessageHandler(Socket& socket, const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition);