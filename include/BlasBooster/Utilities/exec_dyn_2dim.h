#pragma once

namespace BlasBooster {

template <class FunctionType, template <class ...> class Executor, class ExecutorExtraTypes, class T1, class TypeList>
struct DynFuncGenerator1;

template <class FunctionType, template <class ...> class Executor, class ...ExecutorExtraArgs, class T1, class ...Args>
struct DynFuncGenerator1<FunctionType, Executor, TypeList<ExecutorExtraArgs...>, T1, TypeList<Args...>>
{
	static std::array<FunctionType, sizeof...(Args)> dynFunc;
};

template <class FunctionType, template <class ...> class Executor, class ...ExecutorExtraArgs, class T1, class ...Args>
std::array<FunctionType, sizeof...(Args)>
    DynFuncGenerator1<FunctionType, Executor, TypeList<ExecutorExtraArgs...>, T1, TypeList<Args...>>::dynFunc =
        { Executor<ExecutorExtraArgs..., T1, Args>()... };

template <class FunctionType, template <class ...> class Executor, class ExecutorExtraTypes, class TypeList1, class TypeList2>
struct DynFuncGenerator2;

template <class FunctionType, template <class ...> class Executor, class ExecutorExtraTypes, class TypeList1, class... Args>
struct DynFuncGenerator2<FunctionType, Executor, ExecutorExtraTypes, TypeList1, TypeList<Args...>>
{
    static std::array<std::array<FunctionType, sizeof...(Args)>, sizeof...(Args)> dynFunc;
};

template <class FunctionType, template <class ...> class Executor, class ExecutorExtraTypes, class TypeList1, class ...Args>
std::array<std::array<FunctionType, sizeof...(Args)>, sizeof...(Args)>
    DynFuncGenerator2<FunctionType, Executor, ExecutorExtraTypes, TypeList1, TypeList<Args...>>::dynFunc =
        { DynFuncGenerator1<FunctionType, Executor, ExecutorExtraTypes, Args, TypeList1>::dynFunc... };

template <class TypeList, template <class ...> class Executor, class ExecutorExtraTypes, class FunctionType>
inline typename FunctionType::result_type exec_dyn_2dim(DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
    return DynFuncGenerator2<FunctionType, Executor, ExecutorExtraTypes, TypeList, TypeList>::dynFunc[ptrA->getTypeIndex()][ptrB->getTypeIndex()](ptrA, ptrB);
}

} // namespace BlasBooster
