#pragma once

#include <tuple>
#include <vector>
#include <functional>

namespace engine
{
  template <typename... Components>
  class Entity
  {
  public:
    using ComponentTuple = std::tuple<Components *...>;

    template <typename Component>
    constexpr Component *GetComponent() const noexcept
    {
      return IGetComponent<Component>();
    }

    template <typename Component>
    constexpr Component &GetComponentRef() const noexcept
    {
      return *IGetComponent<Component>();
    }

    template <typename Component>
    constexpr void AddComponent(Component *ptr_component) noexcept
    {
      IGetComponent<Component>() = ptr_component;
    }

    template <typename Component>
    constexpr bool HasComponent() const noexcept
    {
      return IGetComponent<Component>() != nullptr;
    }

  private:
    template <typename Component>
    constexpr Component *&IGetComponent()
    {
      return std::get<Component *>(m_ComponenTuple);
    }

    template <typename Component>
    constexpr Component *const &IGetComponent() const
    {
      return std::get<Component *>(m_ComponenTuple);
    }

    ComponentTuple m_ComponenTuple;
  };

  template <typename... UsrComponents>
  class EntityManager
  {
  public:
    using ComponentStorage = std::tuple<std::vector<UsrComponents>...>;
    using Entity_t = Entity<UsrComponents...>;
    using EntityStorage = std::vector<Entity_t>;

    constexpr explicit EntityManager() = default;

    constexpr Entity_t &MakeEntity()
    {
      return m_EntityStorage.emplace_back();
    }

    template <typename Component, typename... Args>
    constexpr void AddComponent(Entity_t &_entity, Args &&..._args)
    {
      if (_entity.template HasComponent<Component>())
        return;
      auto &component = GetContainer<Component>().emplace_back(_args...);
      _entity.template AddComponent<Component>(&component);
    }

    template <typename Component>
    constexpr std::vector<Component> &GetContainer()
    {
      return std::get<std::vector<Component>>(m_ComponentStorage);
    }

    template <typename Component>
    constexpr void ReserveComponent(size_t n)
    {
      GetContainer<Component>().reserve(n);
    }

    constexpr void ReserveEntities(size_t n)
    {
      m_EntityStorage.reserve(n);
    }

    template <typename... CompsRequired>
    constexpr void ForEach(auto &&lambda)
    {
      for (auto &Entity : m_EntityStorage)
      {
        if ((true && ... && Entity.template HasComponent<CompsRequired>()))
        {
          lambda(Entity);
        }
      }
    }

    template <typename ...Components>
    std::vector<Entity_t *> &FilterAndSort(auto&& sortMethod)
    {
      static std::vector<Entity_t *> s_SortedEntities;

      size_t difSize = m_EntityStorage.size() - s_SortedEntities.size();

      if (difSize > 0)
      {
        s_SortedEntities.reserve(difSize);
        s_SortedEntities.clear();
        for (auto& entity : m_EntityStorage)
        {
          if ((true && ... && entity.template HasComponent<Components>()))
          {
            s_SortedEntities.push_back(&entity);
          }
        }
      }

      std::sort(s_SortedEntities.begin(), s_SortedEntities.end(), sortMethod);

      return s_SortedEntities;
    }

  private:
    ComponentStorage m_ComponentStorage;
    EntityStorage m_EntityStorage;
  };
} // namespace engine
