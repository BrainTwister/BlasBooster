#pragma once

#include <type_traits>

namespace BlasBooster {

/// The primary variadic template for all type lists
template <class... T>
struct TypeList;

/// Return the position of the first match of type T in TypeList L
template <class T, class L>
struct GetIndex;

template <class T, class... Ts>
struct GetIndex<T, TypeList<T, Ts...>>
 : std::integral_constant<std::size_t, 0>
{};

template <class T, class Tail, class... Ts>
struct GetIndex<T, TypeList<Tail, Ts...>>
 : std::integral_constant<std::size_t, GetIndex<T, TypeList<Ts...>>::value + 1>
{};

template <class T>
struct GetIndex<T, TypeList<>>
 : std::integral_constant<std::size_t, 0>
{};

/// Returns the type T at position I in TypeList L
template <std::size_t I, class L>
struct GetType;

template <class Tail, class... Ts>
struct GetType<0, TypeList<Tail, Ts...>>
{
    using type = Tail;
};

template <std::size_t I, class Tail, class... Ts>
struct GetType<I, TypeList<Tail, Ts...>>
 : GetType<I - 1, TypeList<Ts...>>
{};

/// Return the size of TypeList L
template <class L>
struct GetSize;

template <class Tail, class... Ts>
struct GetSize<TypeList<Tail, Ts...>>
 : std::integral_constant<std::size_t, GetSize<TypeList<Ts...>>::value + 1>
{};

template <>
struct GetSize<TypeList<>>
 : std::integral_constant<std::size_t, 0>
{};

} // namespace BlasBooster
