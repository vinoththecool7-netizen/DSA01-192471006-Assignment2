# DSA Assignment 2

Student: S Vinoth Kumar  
Register number: 192471006  
Repository: https://github.com/vinoththecool7-netizen/DSA01-192471006-Assignment2


Compiler used here: Apple clang version 21.0.0 (clang-2100.3.34.2), invoked as `g++`. No interactive inputs are required; examples have fixed test values. Output text files record the assistant's runs.

From the repository root, compile and run each executable source (substitute the file path):

```sh
g++ -std=c++17 -Wall -Wextra Task01/main.cpp -o /tmp/task
/tmp/task
```

Run all `main.cpp`, `complete.cpp`, `predict.cpp`, `function.cpp`, and `tests.cpp` files in the task folders in the same way. `Task02/dangling.cpp` is compiled only to observe the warning, and `Task03/ambiguous.cpp` is intentionally uncompilable to demonstrate the error. For timings:

```sh
g++ -std=c++17 -Wall -Wextra -O0 Task06/benchmark.cpp -o /tmp/bench && /tmp/bench
g++ -std=c++17 -Wall -Wextra -O2 Task06/benchmark.cpp -o /tmp/bench && /tmp/bench
g++ -std=c++17 -Wall -Wextra -O2 Task07/main.cpp -o /tmp/redesign && /tmp/redesign
```

Results: Q1 distinguishes copy and alias; Q2 moderates the actual array element and diagnoses a dangling reference; Q3 resolves six overload calls; Q4 retains ten transactions; Q5 issues three seats and puts later tickets on the waiting list; Q6 checks times and measures calls; Q7 compares shifting and circular buffers. See `REPORT.md` and each output file for details. Timings vary with machine and load.
