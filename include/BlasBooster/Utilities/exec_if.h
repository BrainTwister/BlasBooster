// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_UTILITIES_EXEC_IF_H_
#define BLASBOOSTER_UTILITIES_EXEC_IF_H_

#include "BlasBooster/Core/CoreException.h"

namespace BlasBooster {

template <class L>
struct exec_if_impl;

template <class T>
struct exec_if_impl<TypeList<T>>
{
    template <class P, class E>
    static typename E::result_type execute(P const& p, E const& e)
    {
        if (!p(static_cast<T*>(0))) BLASBOOSTER_CORE_FAILURE("type not found");
        return e(static_cast<T*>(0));
    }
};

template <class Tail, class... Ts>
struct exec_if_impl<TypeList<Tail, Ts...>>
{
    template <class P, class E>
    static typename E::result_type execute(P const& p, E const& e)
    {
        if (p(static_cast<Tail*>(0))) return e(static_cast<Tail*>(0));
        return exec_if_impl<TypeList<Ts...>>::execute(p, e);
    }
};

template <class L, class P, class E>
inline typename E::result_type exec_if(P const& p, E const& e, L* = nullptr)
{
    return exec_if_impl<L>::execute(p, e);
}

} // namespace BlasBooster

#endif // BLASBOOSTER_UTILITIES_EXEC_IF_H_
