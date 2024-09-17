#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArray[n1], rightArray[n2];

    // Copiando os dados para os arrays temporários leftArray[] e rightArray[]
    for (i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = arr[mid + 1 + j];

    i = 0; // Índice inicial do primeiro subarray
    j = 0; // Índice inicial do segundo subarray
    k = left; // Índice inicial do subarray mesclado

    // Mescla os arrays temporários de volta para arr[left..right]
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de leftArray[], se houver algum
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de rightArray[], se houver algum
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mescla as metades ordenadas
        merge(arr, left, mid, right);
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: \n");
    printArray(arr, arrSize);

    mergeSort(arr, 0, arrSize - 1);

    printf("Array ordenado: \n");
    printArray(arr, arrSize);
    return 0;
}
