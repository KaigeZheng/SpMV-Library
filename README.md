# SpMV-Library
A C/C++ library for SpMV(sparse matrix-vector multiplication) supporting multiple storage formats.

```text
├── LibFormTrans
│   ├── 2COO.c
│   ├── 2COO.cpp
│   ├── 2CSR.c
│   ├── 2CSR.cpp
│   └── 2DIA.cpp
├── LibSpMV
│   ├── SpMV_2D.c
│   ├── SpMV_2D.cpp
│   ├── SpMV_C.h
│   ├── SpMV_COO.cpp
│   ├── SpMV_CSR.c
│   ├── SpMV_CSR.cpp
│   └── SpMV_CXX.h
└── test_demo.cpp
```

Currently, the supported matrix storage format conversions are limited (the 2DIA format has issues in the current version), and there is no optimization for matrix-vector multiplication for sparse matrices.

In the future, more matrix storage format conversions will be added, along with specific optimization for SpMV.
