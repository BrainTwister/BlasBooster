// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_UTILITIES_EXEC_IF_2DIM_H_
#define BLASBOOSTER_UTILITIES_EXEC_IF_2DIM_H_

#include "BlasBooster/Core/CoreException.h"

namespace BlasBooster {

template <class L>
struct exec_if_1dim_impl;

template <class T>
struct exec_if_1dim_impl<TypeList<T>>
{
    template <class T1, class P, class E>
    static typename E::result_type execute(T1*, P const& p, E const& e)
    {
        if (p(static_cast<T*>(0))) return e(static_cast<T1*>(0), static_cast<T*>(0));
        BLASBOOSTER_CORE_FAILURE("type not found");
    }
};

template <class Tail, class... Ts>
struct exec_if_1dim_impl<TypeList<Tail, Ts...>>
{
    template <class T1, class P, class E>
    static typename E::result_type execute(T1*, P const& p, E const& e)
    {
        if (p(static_cast<Tail*>(0))) return e(static_cast<T1*>(0), static_cast<Tail*>(0));
        return exec_if_1dim_impl<TypeList<Ts...>>::execute(static_cast<T1*>(0), p, e);
    }
};

template <class L>
struct exec_if_2dim_impl;

template <class T>
struct exec_if_2dim_impl<TypeList<T>>
{
    template <class L, class P1, class P2, class E>
    static typename E::result_type execute(P1 const& p1, P2 const& p2, E const& e, L* = nullptr)
    {
        if (p1(static_cast<T*>(0))) return exec_if_1dim_impl<L>::execute(static_cast<T*>(0), p2, e);
        BLASBOOSTER_CORE_FAILURE("type not found");
    }
};

template <class Tail, class... Ts>
struct exec_if_2dim_impl<TypeList<Tail, Ts...>>
{
    template <class L, class P1, class P2, class E>
    static typename E::result_type execute(P1 const& p1, P2 const& p2, E const& e, L* pl = nullptr)
    {
        if (p1(static_cast<Tail*>(0))) return exec_if_1dim_impl<L>::execute(static_cast<Tail*>(0), p2, e);
        return exec_if_2dim_impl<TypeList<Ts...>>::execute(p1, p2, e, pl);
    }
};

template <class L, class P1, class P2, class E>
inline typename E::result_type exec_if_2dim(P1 const& p1, P2 const& p2, E const& e, L* pl = nullptr)
{
    return exec_if_2dim_impl<L>::execute(p1, p2, e, pl);
}

} // namespace BlasBooster

#endif // BLASBOOSTER_UTILITIES_EXEC_IF_2DIM_H_
