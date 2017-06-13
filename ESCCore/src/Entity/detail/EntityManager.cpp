#include "EntityManager.h"
#include <boost/uuid/random_generator.hpp>
#include <queue>
#include <algorithm>

std::unordered_map<boost::uuids::uuid, gsl::detail::EntityDetail, gsl::Util::UuidHash> gsl::detail::EntityManager::detail_;
gsl::detail::EntityDetail gsl::detail::EntityManager::root_(L"root", boost::uuids::random_generator{}());

boost::uuids::uuid gsl::detail::EntityManager::CreateEntityDetail(const s3d::String & Name) {
  auto uuid = boost::uuids::random_generator{}();
  auto pair = detail_.emplace(uuid, EntityDetail{ Name,uuid });
  if (pair.second) {
    root_.trans_.AddChild(pair.first->first);
  }
  return pair.first->first;
}

gsl::detail::EntityDetail* gsl::detail::EntityManager::FindEntityDetail(const boost::uuids::uuid & Uuid) {
  if (detail_.empty())return nullptr;
  auto it = detail_.find(Uuid);
  if (it == detail_.end()) {
    return nullptr;
  }
  else {
    return &it->second;
  }
}

boost::uuids::uuid gsl::detail::EntityManager::FindEntityUUIDWithName(const s3d::String & Name) {
  std::queue<std::vector<Entity>> queue;
  queue.push(std::move(root_.trans_.GetChild()));
  while (!queue.empty()) {
    auto& target = queue.front();
    for (auto&& val : target) {
      if (val.IsValid()) {
        if (*val.GetName() == Name) {
          return *val.GetID();
        }
        queue.push(val.GetChild());
      }
    }
    queue.pop();
  }
  return {};
}
