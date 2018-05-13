#pragma once

namespace BlasBooster {

template <class FunctionType, template <class ...> class Executor, class ExecutorExtraTypes, class TypeList>
struct DynFuncGenerator;

template <class FunctionType, template <class ...> class Executor, class ...ExecutorExtraArgs, class ...Args>
struct DynFuncGenerator<FunctionType, Executor, TypeList<ExecutorExtraArgs...>, TypeList<Args...>>
{
	static std::array<FunctionType, sizeof...(Args)> dynFunc;
};

template <class FunctionType, template <class ...> class Executor, class ...ExecutorExtraArgs, class ...Args>
std::array<FunctionType, sizeof...(Args)>
    DynFuncGenerator<FunctionType, Executor, TypeList<ExecutorExtraArgs...>, TypeList<Args...>>::dynFunc = { Executor<ExecutorExtraArgs..., Args>()... };

template <class TypeList, template <class ...> class Executor, class ExecutorExtraTypes, class FunctionType>
inline typename FunctionType::result_type exec_dyn(DynamicMatrix const& ptrA)
{
    return DynFuncGenerator<FunctionType, Executor, ExecutorExtraTypes, TypeList>::dynFunc[ptrA->getTypeIndex()](ptrA);
}

} // namespace BlasBooster
