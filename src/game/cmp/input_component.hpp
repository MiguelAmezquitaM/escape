#pragma once

#include <unordered_map>
#include <functional>

namespace esc
{

  struct InputComponent
  {
    std::unordered_map<int, std::function<void()>> actions;
  };

} // namespace esc
