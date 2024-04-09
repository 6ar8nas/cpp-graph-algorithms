#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

/**
 * @brief Finds the index of the maximum element in a container.
 * @tparam Container The type of container (e.g., vector, list).
 * @tparam T The type of elements stored in the container.
 * @tparam Args Additional template arguments for the container (if any).
 * @param container The container to search for the maximum element.
 * @return The index of the maximum element, or -1 if the container is empty.
 */
template <template <typename, typename...> class Container, typename T, typename... Args>
int findIndexOfMax(const Container<T, Args...> &container)
{
    if (container.empty())
        return -1;

    auto maxIterator = std::max_element(container.begin(), container.end());
    return std::distance(container.begin(), maxIterator);
}

#endif