./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../include/BlasBooster/BlasInterface/Blas.h.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../include/BlasBooster/BlasInterface/BlasInterface_IntelMKL.h.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../include/BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../include/BlasBooster/BlasInterface/FunctionTypes.h.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../include/BlasBooster/BlasInterface/IntelMKL_SpBlas.h.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../src/Interfaces/IntelMKL/BlasInterface_IntelMKL.cpp.pre
./jinja_code_generator.py -d ../include/BlasBooster/BlasInterface/FunctionList.yml -t ../src/Interfaces/OpenBLAS/BlasInterface_OpenBLAS.cpp.pre

echo "All done."
