/******************************************************************************/
/**
 * @file    nyContainers.hpp
 * @author  Dalia Castellanos
 * @date    13/03/2026
 * @brief   Defines different aliases for common SLT types.
 *
 * Defines aliases for common STL types that could be overwritten by custom
 * classes with similar interfaces and uses. Also defines simple functions for
 * creating some of these objects, that can be overwritten too.
 *
 * @bug	    No known bugs.
 */
 /******************************************************************************/
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <fstream>

namespace nyEngineSDK
{
  using String = std::string;

  template <class T>
  using Vector = std::vector<T>;

  template <class T>
  using UPtr = std::unique_ptr<T>;

  template <class T, class... _Args>
  UPtr<T>
  makeUnique(_Args&& ...args) noexcept
  {
    return std::make_unique<T>(std::forward<_Args>(args));
  }

  template <class T>
  using SPtr = std::shared_ptr<T>;

  template <class T, class... _Args>
  SPtr<T>
  makeShared(_Args&& ...args) noexcept
  {
    return std::make_shared<T>(std::forward<_Args>(args));
  }

  template <class T>
  using WPtr = std::weak_ptr<T>;

  template <class K, class V>
  using HashMap = std::unordered_map<K, V>;

  template <class T>
  using HashSet = std::unordered_set<T>;
} // namespace nyEngineSDK