#include <stdafx.h>
#include <stdio.h>

int main() {
    
    short a = 10;      
    short b = 3;
    short d = 20;
    short e = 4;       
    short c_start = 0; // начальное значение c
    short h = 2;       // шаг изменения c
    short n = 5;       // количество точек

    // Массивы для вывода
    short result[5];   // значения y
    short number[5];   // номера точек
    short c_values[5]; // значения аргумента c

    int i;

    
    short c = c_start;
    for (i = 0; i < n; i++) {
        number[i] = i + 1;
        c_values[i] = c;
        c = c + h;
    }

    
    __asm {
        lea  edi, result     // адрес массива result
        mov  bx, c_start     // текущее значение c (начинаем с c_start)
        mov  cx, n           // счетчик точек

        L1 :
        // Вычисляем (d / e) – целочисленное деление
        mov  ax, d           
            cwd                  
            idiv e               
            mov  si, ax          

            // Вычисляем b * c
            mov  ax, b           
            imul bx             

            
            add  ax, a           // ax = b*c + a
            sub  ax, si          // ax = a + b*c - d/e

            // Сохраняем результат в массив
            mov[edi], ax
            add edi, 2           // переход к следующему элементу массива (short = 2 байта)

            // Переход к следующей точке
            add  bx, h           // c = c + h
            dec  cx
            jnz  L1
    }

    // Вывод таблицы
    printf("No   c   y\n");
    printf("------------\n");
    for (i = 0; i < n; i++) {
        printf("%2d   %2d   %d\n", number[i], c_values[i], result[i]);
    }

    getchar();
    return 0;
}
