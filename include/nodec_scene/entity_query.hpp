#ifndef NODEC_SCENE__ENTITY_QUERY_HPP_
#define NODEC_SCENE__ENTITY_QUERY_HPP_

#include "components/hierarchy.hpp"
#include "components/name.hpp"
#include "scene_entity.hpp"
#include "scene_registry.hpp"

#include <string_view>

namespace nodec_scene {

inline nodec_scene::SceneEntity find_entity_by_name_path(
    nodec_scene::SceneRegistry &registry,
    nodec_scene::SceneEntity entity,
    const std::string_view &name_path) {
    using namespace nodec_scene::components;

    if (!registry.is_valid(entity)) return nodec::entities::null_entity;

    auto hierarchy = registry.try_get_component<const Hierarchy>(entity);
    if (!hierarchy) return nodec::entities::null_entity;

    const auto name_path_first_pos = name_path.find('/');
    const auto name_path_fist = name_path.substr(0, name_path_first_pos);

    auto child = hierarchy->first;

    while (child != nodec::entities::null_entity) {
        auto child_name = registry.try_get_component<const Name>(child);
        if (child_name && child_name->value == name_path_fist) {
            if (name_path_first_pos == std::string_view::npos) {
                return child;
            }
            return find_entity_by_name_path(registry, child, name_path.substr(name_path_first_pos + 1));
        }
        child = registry.try_get_component<const Hierarchy>(child)->next;
    }
    return nodec::entities::null_entity;
}

} // namespace nodec_scene

#endif