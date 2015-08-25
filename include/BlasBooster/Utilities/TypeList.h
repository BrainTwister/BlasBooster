#ifndef BLASBOOSTER_UTILITIES_TYPELIST_H_
#define BLASBOOSTER_UTILITIES_TYPELIST_H_

#include <type_traits>

namespace BlasBooster {

/// The primary variadic template for all type lists
template <class... T>
struct TypeList;

/// Return the position index of the first found type T listed in TypeList L
template <class T, class L>
struct GetIndex;

template <class T, class... Ts>
struct GetIndex<T, TypeList<T, Ts...>>
 : std::integral_constant<size_t, 0>
{};

template <class T, class Tail, class... Ts>
struct GetIndex<T, TypeList<Tail, Ts...>>
 : std::integral_constant<size_t, 1 + GetIndex<T, TypeList<Ts...>>::value>
{};

/// Returns the type T at position I in TypeList L
template <size_t I, class L>
struct GetType;

template <class Tail, class... Ts>
struct GetType<0, TypeList<Tail, Ts...>>
{
	using type = Tail;
};

template <size_t I, class Tail, class... Ts>
struct GetType<I, TypeList<Tail, Ts...>>
 : GetType<I - 1, TypeList<Ts...>>;
{};

} // namespace BlasBooster

#endif /* BLASBOOSTER_UTILITIES_TYPELIST_H_ */
