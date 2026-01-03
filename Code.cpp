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
    for (int i = 0; i < n; i++)
        data[i] = rand() % 100;
}

/* Bubble Sort */
void runBubble(int data[], int n)
{
    for (int pass = 0; pass < n - 1; pass++)
    {
        for (int i = 0; i < n - pass - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
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
        {
            if (data[j] < data[minIndex])
                minIndex = j;
        }

        int temp = data[i];
        data[i] = data[minIndex];
        data[minIndex] = temp;

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

/* Time measurement wrapper */
void evaluateSort(void (*algo)(int[], int), int original[], int n, string name)
{
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++)
        temp[i] = original[i];

    clock_t start = clock();
    algo(temp, n);
    clock_t end = clock();

    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "\n" << name << " completed in " << timeTaken << " ms\n";
}

int main()
{
    srand(time(0));

    int size;
    int data[MAX_SIZE];
    int choice;
    char regenerate;

    cout << "=== Sorting Algorithm Demonstrator ===\n";
    cout << "Enter number of elements (1 - 1000): ";
    cin >> size;

    if (size < 1 || size > MAX_SIZE)
    {
        cout << "Invalid size. Exiting program.\n";
        return 0;
    }

    createDataset(data, size);

    do
    {
        cout << "\nCurrent Dataset:\n";
        showData(data, size);

        cout << "\nMenu:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                evaluateSort(runBubble, data, size, "Bubble Sort");
                break;

            case 2:
                evaluateSort(runSelection, data, size, "Selection Sort");
                break;

            case 3:
                evaluateSort(runInsertion, data, size, "Insertion Sort");
                break;

            case 0:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

        if (choice != 0)
        {
            cout << "\nGenerate new data? (y/n): ";
            cin >> regenerate;
            if (regenerate == 'y' || regenerate == 'Y')
                createDataset(data, size);
        }

    } while (choice != 0);

    return 0;
}
