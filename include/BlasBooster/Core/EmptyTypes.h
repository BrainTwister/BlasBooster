#pragma once

namespace BlasBooster {

struct Dense {};      ///< Type for dense matrix
struct Sparse {};     ///< Type for sparse matrix
struct Zero {};       ///< Type for zero matrix
struct Plus {};       ///< Type for addition in BinaryOperation
struct Minus {};      ///< Type for subtraction in BinaryOperation
struct NullType{};    ///< Type for empty class

}
