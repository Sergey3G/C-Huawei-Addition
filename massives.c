#include <stdio.h>

void input_array(int array[][5], int size_y, int size_x);
void print_array(const int array[][5], int size_y, int size_x);

int main()
{
    int array[5][5] = {{0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
		       {0, 0, 0, 0, 0},
		       {0, 0, 0, 0, 0}};
    int rows = 0, columns = 0;

    printf("Please enter quantities of rows and columns: ");
    scanf("%d %d", &rows, &columns);

    if (rows > 5 || columns > 5 || columns < 1 || rows < 1)
    {
        printf("Invalid sizes!");
        return 1;
    }

    input_array(array, rows, columns);
    print_array(array, rows, columns);

    return 0;
}


void input_array(int array[][5], int size_y, int size_x)
{
    printf("Please enter your massive: \n");
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            scanf("%d", &array[y][x]);
        }
    }
}

void print_array(const int array[][5], int size_y, int size_x)
{
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            printf("[%d][%d] = %d ", y, x, array[y][x]);
        }
        printf("\n");
    }
}




