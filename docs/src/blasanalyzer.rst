.. Copyright (c) 2018 Bernd Doser

   Distributed under the terms of the GPL-3.0 License.

   The full license is in the file LICENSE, distributed with this software.

BlasAnalyzer
============

Standard BLAS support
---------------------

BlasBooster supports an interface to the <a href="http://www.netlib.org/blas" target="_blank">
BLAS de-facto standard</a>. Therefore, it is possible to use BlasBooster without any changes within your application.
However, it should be mentioned that the usage of the BlasBooster C++ interface has significant performance advantages, so that its usage is highly recommended.

Analyze BLAS usage
------------------

It is also possible to use the BlasBooster interface to analyze the usage of BLAS within your application with respect to

- the
