// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_UTILITIES_EXEC_DYN_2DIM_H_
#define BLASBOOSTER_UTILITIES_EXEC_DYN_2DIM_H_

namespace BlasBooster {

template <class FunctionType, template <class, class> class Executor, class T1, class TypeList>
struct DynFuncGenerator1;

template <class FunctionType, template <class, class> class Executor, class T1, class ...Args>
struct DynFuncGenerator1<FunctionType, Executor, T1, TypeList<Args...>>
{
	static std::array<FunctionType, sizeof...(Args)> dynFunc;
};

template <class FunctionType, template <class, class> class Executor, class T1, class ...Args>
std::array<FunctionType, sizeof...(Args)>
    DynFuncGenerator1<FunctionType, Executor, T1, TypeList<Args...>>::dynFunc = { Executor<T1, Args>()... };

template <class FunctionType, template <class, class> class Executor, class TypeList1, class TypeList2>
struct DynFuncGenerator2;

template <class FunctionType, template <class, class> class Executor, class TypeList1, class... Args>
struct DynFuncGenerator2<FunctionType, Executor, TypeList1, TypeList<Args...>>
{
    static std::array<std::array<FunctionType, sizeof...(Args)>, sizeof...(Args)> dynFunc;
};

template <class FunctionType, template <class, class> class Executor, class TypeList1, class ...Args>
std::array<std::array<FunctionType, sizeof...(Args)>, sizeof...(Args)>
    DynFuncGenerator2<FunctionType, Executor, TypeList1, TypeList<Args...>>::dynFunc = { DynFuncGenerator1<FunctionType, Executor, Args, TypeList1>::dynFunc... };

template <class TypeList, template <class, class> class Executor, class ResultType, class FunctionType>
inline ResultType exec_dyn_2dim(DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
    return DynFuncGenerator2<FunctionType, Executor, TypeList, TypeList>::dynFunc[ptrA->getTypeIndex()][ptrB->getTypeIndex()](ptrA, ptrB);
}

} // namespace BlasBooster

#endif // BLASBOOSTER_UTILITIES_EXEC_DYN_2DIM_H_
