#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    printf("Данная программа реализует нахождение неполного частного\n"
           "чисел a и b, не используя оператор деления\n");
    printf("Введите числа а и b через пробел: ");
    scanf("%d %d", &a, &b);
    
    //неполное частное можно найти, подсчитав сколько раз число b
    //"помещается" в число a
    int result = 0;
    while (a > b)
    {
        a -= b;
        result++;
    }
    
    //вывод результата
    printf("a / b = %d\n", result);
    
    return 0;
}