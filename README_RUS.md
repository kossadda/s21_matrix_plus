# s21_matrix+

Реализация библиотеки s21_matrix_oop.h.

Английскую версию README можно найти в репозитории.

## Содержание
1. [Описание проекта](#описание-проекта)
2. [Сборка проекта](#сборка-проекта)
3. [Обратная связь](#обратная-связь)

<br>

## [Описание проекта](#s21_matrix)

Цель данного проекта состоит в реализации на языке программирования С++ класса, имитирующего полноценную работу с матрицами.
Ниже представлено краткое описание операций над матрицами, которые были реализованы в разрабатыванной библиотеке.

| Операция                                 | Описание                                                                     | Исключительные ситуации                                            |
| ---------------------------------------- | ---------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| `bool EqMatrix(const S21Matrix& other)`  | Проверяет матрицы на равенство между собой.                                  |                                                                    |
| `void SumMatrix(const S21Matrix& other)` | Прибавляет вторую матрицы к текущей                                          | Различная размерность матриц.                                      |
| `void SubMatrix(const S21Matrix& other)` | Вычитает из текущей матрицы другую                                           | Различная размерность матриц.                                      |
| `void MulNumber(const double num)`       | Умножает текущую матрицу на число.                                           |                                                                    |
| `void MulMatrix(const S21Matrix& other)` | Умножает текущую матрицу на вторую.                                          | Число столбцов первой матрицы не равно числу строк второй матрицы. |
| `S21Matrix Transpose()`                  | Создает новую транспонированную матрицу из текущей и возвращает ее.          |                                                                    |
| `S21Matrix CalcComplements()`            | Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее. | Матрица не является квадратной.                                    |
| `double Determinant()`                   | Вычисляет и возвращает определитель текущей матрицы.                         | Матрица не является квадратной.                                    |
| `S21Matrix InverseMatrix()`              | Вычисляет и возвращает обратную матрицу.                                     | Определитель матрицы равен 0.                                      |

Помимо реализации данных операций, реализованы конструкторы и деструкторы:

| Метод                               | Описание                                                                               |
| ----------------------------------- | -------------------------------------------------------------------------------------- |
| `S21Matrix()`                       | Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью. |  
| `S21Matrix(int rows, int cols)`     | Параметризированный конструктор с количеством строк и столбцов.                        | 
| `S21Matrix(const S21Matrix& other)` | Конструктор копирования.                                                               |
| `S21Matrix(S21Matrix&& other)`      | Конструктор переноса.                                                                  |
| `~S21Matrix()`                      | Деструктор.                                                                            |

А также перегружены следующие операторы, частично соответствующие операциям выше:

| Оператор          | Описание                                           | Исключительные ситуации                                            |
| ----------------- | -------------------------------------------------- | ------------------------------------------------------------------ |
| `+`               | Сложение двух матриц.                              | Различная размерность матриц.                                      |
| `-`               | Вычитание одной матрицы из другой.                 | Различная размерность матриц.                                      |
| `*`               | Умножение матриц и умножение матрицы на число.     | Число столбцов первой матрицы не равно числу строк второй матрицы. |
| `==`              | Проверка на равенство матриц (`EqMatrix`).         |                                                                    |
| `=`               | Присвоение матрице значений другой матрицы.        |                                                                    |
| `+=`              | Присвоение сложения (`SumMatrix`).                 | Различная размерность матриц.                                      |
| `-=`              | Присвоение разности (`SubMatrix`).                 | Различная размерность матриц.                                      |
| `*=`              | Присвоение умножения (`MulMatrix`/`MulNumber`).    | Число столбцов первой матрицы не равно числу строк второй матрицы. |
| `(int i, int j)`  | Индексация по элементам матрицы (строка, колонка). | Индекс за пределами матрицы.                                       |

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора gcc;
- Код программы находится в папке src;
- Форматирование кода произведено в соответствии с Google Style;
- Матрица реализована в виде класса `S21Matrix`;
- Хранятся только приватные поля `matrix_`, `rows_` и `cols_`;
- Доступ к приватным полям `rows_` и `cols_` реализован через accessor и mutator. При увеличении размера матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается;
- Решение оформлено как статическая библиотеку (с заголовочным файлом s21_matrix_oop.h);
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки GTest;
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix_oop.a).

## [Сборка проекта](#s21_matrix)

В Makefile добавлены следующие основные цели для работы с проектом:

| #  | Цель               | Описание цели                                                                         |
|----| ------------------ | ------------------------------------------------------------------------------------- |
| 1  | `all`              | Производит сборку проекта и формирует документацию к проекту.                         |
| 2  | `s21_matrix_oop`   | Осуществляет сборку модулей в статическую библиотеку.                                 |
| 3  | `test`             | Производит тестирование модулей.                                                      |
| 4  | `gcov_report`      | Производит тестирование модулей и формирует отчет о покрытии в `html` формате.        |
| 5  | `dvi`              | Формирует документацию в формате `html` и `manual` к функционалу.                     |
| 6  | `clean`            | Производит очистку репозитория от сгенерированных файлов.                             |
| 7  | `rebuild`          | Осуществляет пересборку проекта.                                                      |
| 8  | `clang_check`      | Тестирование модулей на соответствие `Google style`.                                  |
| 9  | `valgrind`         | Тестирование модулей на работу с памятью через `Valgrind`.                            |
| 10 | `dependencies`     | Производит установку необходимых зависимостей для cборки и тестирования проекта.      |

<br>

## [Обратная связь](#s21_matrix)

Если имеются вопросы касаемо особенностей или других интересующих вас моментов, то обращайтесь на <br>

|          |                       |
| ---------| --------------------- |
| почту    | gabilov1997@gmail.com |
| telegram | @kossadda             |
| vk       | vk.com/kossadda       |

Спасибо за внимание. Надеюсь, что данный проект вам понравится и будет полезен.

<br>

[К оглавлению](#s21_matrix)