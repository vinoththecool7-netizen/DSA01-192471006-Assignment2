# Assignment report and analysis

S Vinoth Kumar — 192471006  
Assistant-prepared study material and execution evidence. Predictions are assistant predictions, not a claim about the student's own pre-run work. The student must independently perform and document required work.

## Q1 — Value, reference, pointer

For 45000 and 10%, the copy prints 40500 inside the function, but the stored fee stays 45000; reference and pointer each update their separate caller value to 40500. A value parameter is a separate object, a reference aliases the caller object, and a pointer is a copied address whose dereference modifies the caller. Passing a large read-only object by `const Student&` avoids a copy and prevents modification through that reference; it must remain alive during the call. A returned fee (`fee = returned(fee, percent)`) makes a sequence of concessions explicit and permits keeping the original. Sequential reductions compound; e.g. 10% then 15% gives 34425 from 45000, not a combined 25%. All take O(1) time and O(1) auxiliary space for a long long. By value copies sizeof(long long), while reference and const reference avoid copying the referred object (implementation may pass an address). A Student with n bytes of owned data can require O(n) copying and additional storage, while reference binding is O(1); actual copy behavior depends on its members.

The predicted output is in PREDICTIONS.md; the run matched. In `change`, only b and c in main change: a is local, b aliases, c points to the caller. `bigger(a,c)` aliases c (13), so assignment changes c to 100. `show(1)` uses y=5 and z=10; `show(1,2)` uses z=10; `show(1,2,3)` uses no defaults. Integer arithmetic truncates and multiplication can overflow for very large fees; production code should validate bounds and percentages.

## Q2 — Return references

`highest` scans n marks in O(n) and returns the winning element by reference, allowing `+=2` and assignment. A const reference prevents modification through that reference; a copy is independent. The array must be nonempty and outlive the returned reference. `dangling.cpp` intentionally returns a reference to a local; its compiler warning is recorded. The local dies on return, so reading or writing through the reference is undefined behavior; the example does not dereference it.

Equivalent alternatives: find the winning index and use `marks[index] += 2`, or return `&marks[index]` and use `*p += 2`. All scans are O(n) time and O(1) extra space. Pointer may be null to represent absence, but must be checked. A vector reallocation invalidates references and pointers to its elements; a saved index still identifies the same position after append/reallocation, but insertions, erasures, sorting, or shrinking can alter its meaning or invalidate it. Reacquire a reference using a validated index after growth.

## Q3 — Overloading and defaults

The original one- and two-argument calls are ambiguous because the longer overload is also viable via defaults, with identical conversion ranks; see compiler-error.txt. The redesign has one overload per input type, each with trailing optional flags. The predictions matched: `2` chooses int, `2.0` double, `2.0f` double via floating promotion, `Parcel` its object overload, and the last two use int and double respectively. Exact matches rank above promotions, which rank above standard conversions; if the best viable candidates tie, the call is ambiguous. Defaults fill omitted trailing arguments; after a default is declared, parameters to its right must also have defaults (subject to the language's declaration rules).

A single `charge(const Parcel&)` with fields for kg and optional flags unifies the interface; callers construct a Parcel. A template could normalize types, but needs constraints to reject inappropriate types. Overload resolution is compile-time, with no runtime dispatch cost. All calculations are O(1), primitive arguments copy constant space, and `const Parcel&` avoids a Parcel copy; a Parcel value copies its fields. Adding an option requires extending the common implementation and overload signatures, whereas adding a defaulted Parcel field can avoid many signature changes, though callers may still need updates.

## Q4 — Mini-statement

The private array protects ordering, count and balance invariants; deposit and withdrawal reject nonpositive amounts and withdrawal checks funds. When full, the 11th record shifts the remaining nine entries left and appends the new entry. For capacity k this costs O(k), storage O(k); a circular buffer overwrites `a[start]` and advances `start=(start+1)%k`, O(1) per insertion and O(k) storage, with O(k) display. A deque can `push_back` and `pop_front` in amortized/constant endpoint operations with O(k) elements and implementation overhead. For 50 transactions choose the circular design: changing the capacity preserves the O(1) insertion and bounded storage, at the cost of more indexing logic. Test output after 11 deposits and a withdrawal retains the final ten records.

## Q5 — Static members and tickets

`issued` and `CAPACITY` belong to the class; `seat` and `name` belong to each ticket. The static data member is defined once outside the class. Static functions have no implicit object, so have no `this` and cannot directly access non-static members. The array initializes four objects, three assigned seats and one waiting. `function.cpp` calls a function twice: the count persists after local ticket destruction, so the second call issues seat 3 then waiting; issued remains 3. This design counts seats ever issued, not live objects, and does not support cancellation or multiple buses independently.

Token prediction matched: 101 103 104 4. `next` is initialized once to 100 by its out-of-class definition, and four constructor calls increment it. A global counter also takes O(1) time and one counter but exposes shared mutable state. A `TicketOffice` object with capacity and count passed to each ticket encapsulates allocation and allows separate buses, with one O(1) counter per office and O(1) allocation. Its lifetime must cover use by tickets if they retain a reference.

## Q6 — Friends and inline

A friend is a non-member invoked `minutesBetween(a,b)` and granted private access. It is useful for symmetric operations but is not strictly necessary: a member or getters also work. Making data public would let callers violate representation invariants. `inline` permits multiple identical definitions across translation units and suggests substitution; the compiler decides whether to inline. Both comparisons are O(1). 09:45 to 13:10 is 205 minutes; 11:55 to 12:05 is 10; identical times give 0 and are not earlier. The absolute difference is within one day, not an overnight journey duration.

The benchmark uses 10,000,000 calls at each optimization setting and a volatile checksum; the non-inline variant uses a compiler-specific noinline attribute. See Task06 outputs for measured values. The measurements include loop, lambda and volatile overhead; the variants and optimizer may generate different code, so they are illustrative, not a controlled universal comparison. In this run -O2 timings were about 17.08 ms inline, 14.88 ms noinline, 6.44 ms member, and 6.45 ms getters. At -O0 they were 46.50, 44.16, 45.10, and 80.02 ms respectively. Optimization and measurement noise can outweigh the inline keyword. Choose friends for compact symmetric operations if private representation access is desirable; getters reduce privileged coupling, while members are convenient but asymmetric. A production Time class should validate hours and minutes.

## Q7 — Diagnose and redesign

**A. Diagnosis:** Q4's full array shifts k-1 old elements on every insertion. The 11th entry drops the oldest, demonstrating the repeated shift; the benchmark reproduces this algorithm at capacities 10, 50, and 1000.

**B. Objective:** retain precisely the last k entries in chronological order with O(1) full-buffer insertion and O(k) storage, and compare 200,000 identical inserts.

**C. Design:** a ring stores `start` and `count` alongside the array. If not full, place x at `(start+count)%k` and increment count. If full, replace `array[start]` and advance start modulo k. Read entry i at `(start+i)%k`. This uses two indices of O(1) extra space, with more complex indexing. Capacity must be positive. The benchmark uses vectors for dynamic capacity, but implements the ring algorithm itself.

**D. Prediction before implementation:** see PREDICTIONS.md: output equality and one replacement instead of k writes, with growing advantage at larger k. Timing for small k may be dominated by overhead.

**E. Validation:** the program asserts identical ordered results and endpoint values. On this machine at -O2, shift/ring times in ms were 1.08/1.13 (k=10), 2.04/1.09 (50), and 13.45/1.08 (1000), respectively. These are single runs, not statistically robust; see raw output and repeat on the target machine.

**F. Decision:** the operation-count objective was met, with a measured advantage for 50 and 1000 in this run; at 10 the ring was slightly slower. The array shift remains simpler and can be preferable for small, infrequent updates. Both occupy O(k), and reading the statement costs O(k). Measurements are not a guarantee on other compilers or workloads.
