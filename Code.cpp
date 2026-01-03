#include <iostream>
#include <cstdlib>
#include <chrono>
#include <limits> // For numeric_limits
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

/* ---------- Data Generation ---------- */
void createDataset(int data[], int n) { for (int i = 0; i < n; i++) data[i] = rand() % 100; }
void createBestCase(int data[], int n) { for (int i = 0; i < n; i++) data[i] = i + 1; }
void createWorstCase(int data[], int n) { for (int i = 0; i < n; i++) data[i] = n - i; }

/* ---------- Sorting Algorithms with step display ---------- */
void runBubble(int data[], int n)
{
    cout << "\nBubble Sort Steps:\n";
    for (int pass = 0; pass < n - 1; pass++)
    {
        for (int i = 0; i < n - pass - 1; i++)
        {
            if (data[i] > data[i + 1])
                swap(data[i], data[i + 1]);
            showData(data, n);
        }
    }
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

/* ---------- Quick Sort ---------- */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    cout << "Partitioned with pivot " << pivot << ": ";
    showData(arr, high + 1);
    return i + 1;
}

void runQuick(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        runQuick(arr, low, pi - 1);
        runQuick(arr, pi + 1, high);
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

    cout << "Merged [" << l << " - " << r << "]: ";
    for (int x = l; x <= r; x++) cout << arr[x] << " ";
    cout << endl;

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

/* ---------- Evaluation ---------- */
void evaluateSort(void (*algo)(int[], int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    cout << "\n=== " << name << " ===\n";
    auto start = high_resolution_clock::now();
    algo(temp, n);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns)\n";
}

void evaluateSort(void (*algo)(int[], int, int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = original[i];

    cout << "\n=== " << name << " ===\n";
    auto start = high_resolution_clock::now();
    algo(temp, 0, n - 1);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start).count();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    cout << name << " completed in " << duration_ms << " ms (" << duration_ns << " ns)\n";
}

/* ---------- Main Program ---------- */
int main()
{
    srand(time(0));
    int size, choice, shapeChoice;
    char regenerate;
    int data[MAX_SIZE];

    cout << "=== Sorting Algorithm Demonstrator ===\n";

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

    do
    {
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

        cout << "\nCurrent Dataset:\n";
        showData(data, size);

        // Sorting menu
        do
        {
            while (true)
            {
                cout << "\nSorting Menu:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n0. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;
                if (cin.fail() || choice < 0 || choice > 5)
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
