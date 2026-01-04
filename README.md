# Sorting Algorithm Demonstrator

This C++ program demonstrates various sorting algorithms with step-by-step visualization, performance timing, and best/worst-case scenario testing. It is designed for educational purposes to understand sorting algorithm behaviors.

## Features
- Interactive demonstration of sorting algorithms with visual step-by-step output.
- Support for multiple dataset types: Random, Best Case (already sorted), and Worst Case (reverse sorted).
- Performance measurement in milliseconds and nanoseconds.
- Automated testing for best and worst-case scenarios across different array sizes.
- Data input from file or manual generation.
- Output logging to file for analysis.

## Files
- `Code.cpp`: The main C++ source code containing all sorting implementations and the interactive menu.
- `data.txt`: Optional input file for datasets (first line: number of elements, subsequent lines: space-separated integers).
- `testcases.txt`: Output log file where datasets, sorted results, and timings are appended.
- `README.md`: This documentation file.

## Prerequisites
- C++ compiler (e.g., g++ on Windows/Linux/Mac).
- Standard C++ libraries (included with most compilers).

## Compilation
Compile the program using g++:
```
g++ Code.cpp -o SortingDemo.exe
```

## Usage
Run the compiled executable:
```
./SortingDemo.exe
```

### Program Flow
The program runs in an interactive loop, allowing you to work with multiple datasets.

1. **Data Source Selection**:
   - Choose 'y' to read data from `data.txt`.
   - Choose 'n' to generate data manually.

2. **Dataset Generation** (if generating manually):
   - Enter the number of elements (1-1000).
   - Select dataset type:
     - 1: Random (unsorted array).
     - 2: Best Case (already sorted ascending).
     - 3: Worst Case (sorted descending).

3. **Display Dataset**:
   - The current dataset is displayed on the console.

4. **Sorting Options**:
   - Choose from:
     - 1: Bubble Sort
     - 2: Selection Sort
     - 3: Insertion Sort
     - 4: Merge Sort
     - 5: Quick Sort
     - 6: Test Best/Worst Cases (automated performance testing)
     - 0: Exit
   - For individual sorts (1-5): Displays step-by-step array changes and final timing.
   - For option 6: Runs silent performance tests on best/worst cases for sizes 10, 100, 500, 1000.

5. **Repeat Options**:
   - Option to sort the same dataset again with a different algorithm.
   - Option to generate a new dataset (returns to step 1).

## Supported Algorithms
- **Bubble Sort**: O(n²) worst/average, O(n) best case (with early termination).
- **Selection Sort**: O(n²) in all cases.
- **Insertion Sort**: O(n²) worst/average, O(n) best case.
- **Merge Sort**: O(n log n) in all cases, stable sort.
- **Quick Sort**: O(n log n) average, O(n²) worst case (mitigated with median-of-three pivot).

## Output
- **Console**: Step-by-step array changes during sorting and final execution times.
- **`testcases.txt`**: Logs datasets, sorted arrays, and timings for analysis.

## Example Usage
```
=== Sorting Algorithm Demonstrator ===
Read data from file? (y/n): n
Enter number of elements (1 - 1000): 10
Select dataset type:
1. Random
2. Best case
3. Worst case
Enter choice: 2

Current Dataset:
1 2 3 4 5 6 7 8 9 10

Sorting Menu:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort
6. Test Best/Worst Cases
0. Exit
Enter choice: 6

=== Testing with n = 10 ===

Best Case (Already Sorted):
Bubble Sort completed in 0 ms (0 ns) - Sorted
...
```

## Project Status
This is a completed educational project for Discrete Mathematics (CSC102F25R169). All algorithms are implemented and tested for correctness on best and worst-case scenarios.

## License
This project is for educational purposes. Feel free to use and modify as needed.
