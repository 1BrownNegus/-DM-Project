#include <iostream>
#include <cstdlib>
#include <chrono>
#include <limits> // For numeric_limits
#include <fstream>
using namespace std;
using namespace std::chrono;

const int MAX_SIZE = 1000;

/* ---------- Utility Functions ---------- */
void showData(int data[], int n)
{
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;
}

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* ---------- File Handling ---------- */
bool readFromFile(const string& filename, int arr[], int& n)
{
    ifstream fin(filename);
    if (!fin)
    {
        cout << "Error opening input file.\n";
        return false;
    }

    fin >> n;
    if (n < 1 || n > MAX_SIZE)
    {
        cout << "Invalid size in file.\n";
        return false;
    }

    for (int i = 0; i < n; i++)
        fin >> arr[i];

    fin.close();
    return true;
}

void writeDatasetToFile(const string& filename, int arr[], int n)
{
    ofstream fout(filename, ios::app);
    fout << "Dataset: ";
    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";
    fout << "\n";
    fout.close();
}

void writeToFile(const string& filename, const string& name, int arr[], int n, long long duration_ms, long long duration_ns)
{
    ofstream fout(filename, ios::app);
    fout << name << ": ";
    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";
    fout << " - Time: " << duration_ms << " ms (" << duration_ns << " ns)\n";
    fout.close();
}


/* ---------- Data Generation ---------- */
void createDataset(int data[], int n) { for (int i = 0; i < n; i++) data[i] = rand() % 100; }
void createBestCase(int data[], int n) { for (int i = 0; i < n; i++) data[i] = i + 1; }
void createWorstCase(int data[], int n) { for (int i = 0; i < n; i++) data[i] = n - i; }

/* ---------- Sorting Algorithms with step display ---------- */
void runBubble(int data[], int n)
{
    cout << "\nBubble Sort Steps:\n";
    int pass = 0;
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < n - pass - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                swapped = true;
                showData(data, n);
            }
        }
        pass++;
    } while (swapped && pass < n - 1);
}

void runBubbleSilent(int data[], int n)
{
    int pass = 0;
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < n - pass - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                swapped = true;
            }
        }
        pass++;
    } while (swapped && pass < n - 1);
}

void runSelection(int data[], int n)
{
    cout << "\nSelection Sort Steps:\n";
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (data[j] < data[minIndex])
                minIndex = j;
        swap(data[i], data[minIndex]);
        showData(data, n);
    }
}

void runSelectionSilent(int data[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (data[j] < data[minIndex])
                minIndex = j;
        swap(data[i], data[minIndex]);
    }
}

void runInsertion(int data[], int n)
{
    cout << "\nInsertion Sort Steps:\n";
    for (int i = 1; i < n; i++)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
        showData(data, n);
    }
}

void runInsertionSilent(int data[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

/* ---------- Quick Sort ---------- */
int partition(int arr[], int low, int high)
{
    // Median of three pivot selection
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    // Now arr[low] <= arr[mid] <= arr[high], pivot is arr[mid]
    swap(arr[mid], arr[high]);
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void runQuick(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        showData(arr, high + 1);
        runQuick(arr, low, pi - 1);
        runQuick(arr, pi + 1, high);
    }
}

void runQuickSilent(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        runQuickSilent(arr, low, pi - 1);
        runQuickSilent(arr, pi + 1, high);
    }
}

/* ---------- Merge Sort ---------- */
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    showData(arr + l, r - l + 1);

    delete[] L;
    delete[] R;
}

void mergeSilent(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void runMerge(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        runMerge(arr, l, m);
        runMerge(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void runMergeSilent(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        runMergeSilent(arr, l, m);
        runMergeSilent(arr, m + 1, r);
        mergeSilent(arr, l, m, r);
    }
}

/* ---------- Evaluation ---------- */
void evaluateSort(void (*algo)(int[], int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    cout << "\n=== " << name << " ===\n";
    writeDatasetToFile("testcases.txt", original, n);
    auto start = high_resolution_clock::now();
    algo(temp, n);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns)\n";

    writeToFile("testcases.txt", name, temp, n, duration_ms, duration_ns);
}

void evaluateSort(void (*algo)(int[], int, int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    cout << "\n=== " << name << " ===\n";
    writeDatasetToFile("testcases.txt", original, n);
    auto start = high_resolution_clock::now();
    algo(temp, 0, n - 1);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns)\n";

    writeToFile("testcases.txt", name, temp, n, duration_ms, duration_ns);
}

void evaluateSortSilent(void (*algo)(int[], int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    auto start = high_resolution_clock::now();
    algo(temp, n);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    // Check if sorted
    bool sorted = true;
    for (int i = 1; i < n; i++)
        if (temp[i] < temp[i-1]) { sorted = false; break; }

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns) - " << (sorted ? "Sorted" : "Not Sorted") << "\n";
}

void evaluateSortSilent(void (*algo)(int[], int, int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    auto start = high_resolution_clock::now();
    algo(temp, 0, n - 1);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    // Check if sorted
    bool sorted = true;
    for (int i = 1; i < n; i++)
        if (temp[i] < temp[i-1]) { sorted = false; break; }

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns) - " << (sorted ? "Sorted" : "Not Sorted") << "\n";
}

/* ---------- Test Best and Worst Cases ---------- */
void testBestWorst()
{
    const int testSizes[] = {10, 100, 500, 1000};
    int numSizes = sizeof(testSizes) / sizeof(testSizes[0]);

    for (int s = 0; s < numSizes; s++)
    {
        int n = testSizes[s];
        int best[MAX_SIZE], worst[MAX_SIZE];

        createBestCase(best, n);
        createWorstCase(worst, n);

        cout << "\n=== Testing with n = " << n << " ===\n";

        cout << "\nBest Case (Already Sorted):\n";
        evaluateSortSilent(runBubbleSilent, best, n, "Bubble Sort");
        evaluateSortSilent(runSelectionSilent, best, n, "Selection Sort");
        evaluateSortSilent(runInsertionSilent, best, n, "Insertion Sort");
        evaluateSortSilent(runMergeSilent, best, n, "Merge Sort");
        evaluateSortSilent(runQuickSilent, best, n, "Quick Sort");

        cout << "\nWorst Case (Reverse Sorted):\n";
        evaluateSortSilent(runBubbleSilent, worst, n, "Bubble Sort");
        evaluateSortSilent(runSelectionSilent, worst, n, "Selection Sort");
        evaluateSortSilent(runInsertionSilent, worst, n, "Insertion Sort");
        evaluateSortSilent(runMergeSilent, worst, n, "Merge Sort");
        evaluateSortSilent(runQuickSilent, worst, n, "Quick Sort");
    }
}

/* ---------- Main Program ---------- */
int main()
{
    srand(time(0));
    int size, choice, shapeChoice;
    char regenerate, fileChoice;
    int data[MAX_SIZE];

    cout << "=== Sorting Algorithm Demonstrator ===\n";

    do
    {
        // Ask if user wants to read from file
        while (true)
        {
            cout << "Read data from file? (y/n): ";
            cin >> fileChoice;
            if (fileChoice == 'y' || fileChoice == 'Y' || fileChoice == 'n' || fileChoice == 'N')
                break;
            else
                cout << "Invalid input. Enter 'y' or 'n'.\n";
        }

        if (fileChoice == 'y' || fileChoice == 'Y')
        {
            if (!readFromFile("data.txt", data, size))
                return 0;
        }
        else
        {
            // Input size with validation
            while (true)
            {
                cout << "Enter number of elements (1 - 1000): ";
                cin >> size;
                if (cin.fail() || size < 1 || size > MAX_SIZE)
                {
                    cout << "Invalid input. Try again.\n";
                    clearInput();
                }
                else break;
            }

            // Dataset selection with validation
            while (true)
            {
                cout << "\nSelect dataset type:\n1. Random\n2. Best case\n3. Worst case\n";
                cout << "Enter choice: ";
                cin >> shapeChoice;
                if (cin.fail() || shapeChoice < 1 || shapeChoice > 3)
                {
                    cout << "Invalid choice. Try again.\n";
                    clearInput();
                }
                else break;
            }

            switch (shapeChoice)
            {
                case 1: createDataset(data, size); break;
                case 2: createBestCase(data, size); break;
                case 3: createWorstCase(data, size); break;
            }
        }

        cout << "\nCurrent Dataset:\n";
        showData(data, size);

        // Sorting menu
        do
        {
            while (true)
            {
                cout << "\nSorting Menu:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n6. Test Best/Worst Cases\n0. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;
                if (cin.fail() || choice < 0 || choice > 6)
                {
                    cout << "Invalid choice. Try again.\n";
                    clearInput();
                }
                else break;
            }

            if (choice == 0) break;

            switch (choice)
            {
                case 1: evaluateSort(runBubble, data, size, "Bubble Sort"); break;
                case 2: evaluateSort(runSelection, data, size, "Selection Sort"); break;
                case 3: evaluateSort(runInsertion, data, size, "Insertion Sort"); break;
                case 4: evaluateSort(runMerge, data, size, "Merge Sort"); break;
                case 5: evaluateSort(runQuick, data, size, "Quick Sort"); break;
                case 6: testBestWorst(); break;
            }

            // Ask if user wants to sort same dataset again
            while (true)
            {
                cout << "\nSort same dataset again? (y/n): ";
                cin >> regenerate;
                if (regenerate == 'y' || regenerate == 'Y' || regenerate == 'n' || regenerate == 'N')
                    break;
                else
                    cout << "Invalid input. Enter 'y' or 'n'.\n";
            }

        } while (regenerate == 'y' || regenerate == 'Y');

        // Ask if user wants a new dataset
        while (true)
        {
            cout << "\nGenerate NEW dataset? (y/n): ";
            cin >> regenerate;
            if (regenerate == 'y' || regenerate == 'Y' || regenerate == 'n' || regenerate == 'N')
                break;
            else
                cout << "Invalid input. Enter 'y' or 'n'.\n";
        }

    } while (regenerate == 'y' || regenerate == 'Y');

    cout << "\nExiting program. Goodbye!\n";
    return 0;
}
