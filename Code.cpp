#include <iostream>
#include <cstdlib>
#include <chrono> // For precise timing

using namespace std;
using namespace std::chrono;

const int MAX_SIZE = 1000;

/* Displays the contents of an array */
void showData(int data[], int n)
{
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;
}

/* Generates random integers */
void createDataset(int data[], int n)
{
    for (int i = 0; i < n; i++)
        data[i] = rand() % 100;
}

/* Generates ascending sorted dataset */
void createBestCase(int data[], int n)
{
    for (int i = 0; i < n; i++)
        data[i] = i + 1;
}

/* Generates descending sorted dataset */
void createWorstCase(int data[], int n)
{
    for (int i = 0; i < n; i++)
        data[i] = n - i;
}

/* Bubble Sort */
void runBubble(int data[], int n)
{
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

/* Selection Sort */
void runSelection(int data[], int n)
{
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

/* Insertion Sort */
void runInsertion(int data[], int n)
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
        showData(data, n);
    }
}

/* Merge Sort */
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
        showData(arr, r + 1);
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

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

/* Quick Sort */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
        showData(arr, high + 1);
    }
    swap(arr[i + 1], arr[high]);
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

/* Time measurement using chrono - for sorts with int[], int */
void evaluateSort(void (*algo)(int[], int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++)
        temp[i] = original[i];

    auto start = high_resolution_clock::now();
    algo(temp, n);
    auto end = high_resolution_clock::now();

    auto duration_ns = duration_cast<nanoseconds>(end - start).count();
    auto duration_ms = duration_cast<milliseconds>(end - start).count();

    cout << "\n" << name << " completed in " << duration_ms << " ms (" 
         << duration_ns << " ns)\n";
}

/* Time measurement using chrono - for sorts with int[], int, int */
void evaluateSort(void (*algo)(int[], int, int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++)
        temp[i] = original[i];

    auto start = high_resolution_clock::now();
    algo(temp, 0, n - 1);
    auto end = high_resolution_clock::now();

    auto duration_ns = duration_cast<nanoseconds>(end - start).count();
    auto duration_ms = duration_cast<milliseconds>(end - start).count();

    cout << "\n" << name << " completed in " << duration_ms << " ms (" 
         << duration_ns << " ns)\n";
}

int main()
{
    srand(time(0));

    int size;
    int data[MAX_SIZE];
    int choice, shapeChoice;
    char regenerate;

    cout << "=== Sorting Algorithm Demonstrator ===\n";
    cout << "Enter number of elements (1 - 1000): ";
    cin >> size;

    if (size < 1 || size > MAX_SIZE)
    {
        cout << "Invalid size. Exiting program.\n";
        return 0;
    }

    do
    {
        cout << "\nSelect dataset type:\n";
        cout << "1. Random\n";
        cout << "2. Best case (ascending)\n";
        cout << "3. Worst case (descending)\n";
        cout << "Enter choice: ";
        cin >> shapeChoice;

        switch (shapeChoice)
        {
            case 1: createDataset(data, size); break;
            case 2: createBestCase(data, size); break;
            case 3: createWorstCase(data, size); break;
            default: createDataset(data, size); break;
        }

        cout << "\nCurrent Dataset:\n";
        showData(data, size);

        cout << "\nMenu:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Merge Sort\n";
        cout << "5. Quick Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: evaluateSort(runBubble, data, size, "Bubble Sort"); break;
            case 2: evaluateSort(runSelection, data, size, "Selection Sort"); break;
            case 3: evaluateSort(runInsertion, data, size, "Insertion Sort"); break;
            case 4: evaluateSort(runMerge, data, size, "Merge Sort"); break;
            case 5: evaluateSort(runQuick, data, size, "Quick Sort"); break;
            case 0: cout << "\nExiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

        if (choice != 0)
        {
            cout << "\nGenerate new data? (y/n): ";
            cin >> regenerate;
        }

    } while (choice != 0 && (regenerate == 'y' || regenerate == 'Y'));

    return 0;
}
