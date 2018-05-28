.. Copyright (c) 2018 Bernd Doser

   Distributed under the terms of the GPL-3.0 License.

   The full license is in the file LICENSE, distributed with this software.

Matrix types
============

Static matrix types
-------------------

If the matrix type is known at compile time you can use static matrix types. 
All static matrix types are specialized from a single template class:

``Matrix<MatrixType, ElementType, MatrixParameter>``

- ``MatrixType`` specifies the type of the matrix, e.g. dense or sparse.
- <code>ElementType</code> specifies the type of the matrix elements, e.g. float or double.
- <code>MatrixParameter</code> combine remaining matrix parameters, e.g.:
    + <code>IndexType</code> specifies the type of the index parameter.
    + <code>SizeType</code> specifies variable or fixed dimension of the matrix.
    + <code>OrientationType</code> specifies if the matrix is stored row or column oriented.
    + <code>StorageType</code> specifies if the matrix is stored on heap or on stack.

Thus enables the instantiation of following examples:

<pre><code>// A dense matrix with single precision
Matrix<Dense, float>

// A sparse matrix with double precision
Matrix<Sparse, double>

// A dense matrix, row-wise storage with a fixed size of 3x2
Matrix<Dense, double, Parameter<int, RowMajor, FixedSize<3, 2>>>
</code></pre>


DynamicMatrix
-------------

The DynamicMatrix allows to determine the matrix type dynamically during runtime using inheritance.
To avoid a complex system of virtual functions a general approach was developed which allows to forward
dynamic to corresponding static functions.


MultipleMatrix
--------------

The MultipleMatrix splits a matrix <code>A</code> in a sum of matrices <code>A<sub>1</sub> + A<sub>2</sub></code>.
This is useful if a matrix have many small entries which can be stored with single precision and only some entries which
must be stored with double precision: 

<code>MultipleMatrix<Matrix<Dense, float>, Matrix<Sparse, double>></code>

The type is comparable to an expression template. If a MultipleMatrix <code>A</code> is multiplied
by a Matrix <code>B</code> it result in <code>A<sub>1</sub> * B + A<sub>2</sub> * B</code>.

Block matrix
------------

A block matrix $A$ consists of submatrices $A_{i,j}$:

$$
    A = \left[
        \begin{matrix}
             A_{1,1} \quad A_{1,2} \\
             A_{2,1} \quad A_{2,2}
        \end{matrix}
        \right]
$$

In BlasBooster this can simply be formulated by using a matrix type as <code>ElementType</code>.
For instance a dense block matrix with a dense submatrices can be defined as

<code>Matrix<Dense, Matrix<Dense, double>></code>


Dynamic block matrix
--------------------

The most powerful matrix type can be achieved by using the <code>DynamicMatrix</code> type as <code>ElementType</code>,
so that the submatrices can have different matrix types. Therefore, it allows to handle submatrices with a
sparse occupation as <code>Matrix<Sparse, double></code> and submatrices with a dense occupation as <code>Matrix<Sparse, double></code>.
