# Testing std::atomic vs volatile performance

- Windows: Visual Studio 2022 for x64 Release target
```/std:c++20 /O2 /Oi /Ot```

- Linux: clang++ 18.1.3
```-std=c++20 -O3```

![Screenshot](https://github.com/CyberusConsulting/AtomicVolatileTest/raw/main/results.png)
![Screenshot](https://github.com/CyberusConsulting/AtomicVolatileTest/raw/main/results-2.png)
