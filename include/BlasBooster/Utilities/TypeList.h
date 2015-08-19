#ifndef BLASBOOSTER_UTILITIES_TYPELIST_H_
#define BLASBOOSTER_UTILITIES_TYPELIST_H_

#include <type_traits>

namespace BlasBooster {

/// The primary variadic template for all type lists
template <class... T>
struct TypeList;

/// Providing the index of type T listed in TypeList L
template <class T, class L>
struct GetIndex;

template <class T, class... Ts>
struct GetIndex<T, TypeList<T, Ts...>>
 : std::integral_constant<std::size_t, 0>
{};

template <class T, class Tail, class... Ts>
struct GetIndex<T, TypeList<Tail, Ts...>>
 : std::integral_constant<std::size_t, 1 + GetIndex<T, TypeList<Ts...>>::value>
{};

} // namespace BlasBooster

#endif /* BLASBOOSTER_UTILITIES_TYPELIST_H_ */
