#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

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
    srand(time(0));
    for (int i = 0; i < n; i++)
        data[i] = rand() % 100;
}

/* Bubble Sort Implementation */
void runBubble(int data[], int n)
{
    for (int pass = 0; pass < n - 1; pass++)
    {
        for (int i = 0; i < n - pass - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                int swapTemp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = swapTemp;
            }
            showData(data, n);
        }
    }
}

/* Selection Sort Implementation */
void runSelection(int data[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int smallest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (data[j] < data[smallest])
                smallest = j;
        }

        int temp = data[i];
        data[i] = data[smallest];
        data[smallest] = temp;

        showData(data, n);
    }
}

/* Insertion Sort Implementation */
void runInsertion(int data[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int current = data[i];
        int pos = i - 1;

        while (pos >= 0 && data[pos] > current)
        {
            data[pos + 1] = data[pos];
            pos--;
        }

        data[pos + 1] = current;
        showData(data, n);
    }
}

/* Measures execution time */
void evaluateSort(void (*sortAlgo)(int[], int), int original[], int n, string name)
{
    int copy[MAX_SIZE];
    for (int i = 0; i < n; i++)
        copy[i] = original[i];

    clock_t start = clock();
    sortAlgo(copy, n);
    clock_t finish = clock();

    double duration = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    cout << "\n" << name << " completed in " << duration << " ms\n";
}

int main()
{
    int size;
    int numbers[MAX_SIZE];

    cout << "=== Sorting Algorithm Demonstrator ===\n";
    cout << "Enter number of elements (1 - 1000): ";
    cin >> size;

    if (size < 1 || size > MAX_SIZE)
    {
        cout << "Invalid size entered.\n";
        return 0;
    }

    createDataset(numbers, size);

    cout << "\nInitial Data:\n";
    showData(numbers, size);

    cout << "\nChoose Sorting Method:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "Enter choice: ";

    int option;
    cin >> option;

    switch (option)
    {
        case 1:
            evaluateSort(runBubble, numbers, size, "Bubble Sort");
            break;

        case 2:
            evaluateSort(runSelection, numbers, size, "Selection Sort");
            break;

        case 3:
            evaluateSort(runInsertion, numbers, size, "Insertion Sort");
            break;

        default:
            cout << "Invalid option selected.\n";
    }

    cout << "\nProgram Finished Successfully.\n";
    return 0;
}
