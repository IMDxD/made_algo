# A. Кузнечик собирает монеты
Кузнечик прыгает по столбикам, расположенным на одной линии на равных расстояниях друг от друга. Столбики имеют порядковые номера от 1 до n. В начале Кузнечик сидит на столбике с номером 1 и хочет добраться до столбика с номером n. Он может прыгнуть вперед на расстояние от 1 до k столбиков, считая от текущего.

На каждом столбике Кузнечик может получить или потерять несколько золотых монет (для каждого столбика это число известно). Определите, как нужно прыгать Кузнечику, чтобы собрать наибольшее количество золотых монет. Учитывайте, что Кузнечик не может прыгать назад.

Входные данные
В первой строке вводятся два натуральных числа: n и k (3≤n≤10000, 1≤k≤10000), разделённые пробелом. Во второй строке записаны через пробел n−2 целых числа – количество монет, которое Кузнечик получает на каждом столбике, от 2-го до n−1-го. Если это число отрицательное, Кузнечик теряет монеты. Гарантируется, что все числа по модулю не превосходят 10000.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Кузнечик. Во второй строке выводится число прыжков Кузнечика, а в третьей строке – номера всех столбиков, которые посетил Кузнечик (через пробел в порядке возрастания).

Если правильных ответов несколько, выведите любой из них.


# B. Черепаха и монеты
Черепаха хочет переползти из левого верхнего угла поля размером n на m клеток (2≤n,m≤1000) в правый нижний. За один шаг она может переместиться на соседнюю клетку вправо или на соседнюю клетку вниз. Кроме того, проходя через каждую клетку, Черепаха получает (или теряет) несколько золотых монет (это число известно для каждой клетки).

Определите, какое максимальное количество монет может собрать Черепаха по пути и как ей нужно идти для этого.

Входные данные
В первой строке вводятся два натуральных числа: n и m (2≤n,m≤1000), разделённые пробелом. В каждой из следующих n строк записаны через пробел по m чисел aij(|aij|≤10), которые обозначают количество монет, получаемых Черепашкой при проходе через каждую клетку. Если это число отрицательное, Черепашка теряет монеты.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Черепаха. Во второй строке без пробелов выводятся команды, которые нужно выполнить Черепахе: буква 'R' (от слова right) обозначает шаг вправо, а буква 'D' (от слова down) — шаг вниз.


# C. Наибольшая возрастающая подпоследовательность
Пусть a1, a2, ..., an — числовая последовательность. Длина последовательности — это количество элементов этой последовательности. Последовательность ai1, ai2, ..., aik называется подпоследовательностью последовательности a, если 1 ≤ i1 < i2 < ... < ik ≤ n. Последовательность a называется возрастающей, если a1 < a2 < ... < an.

Вам дана последовательность, содержащая n целых чисел. Найдите ее самую длинную возрастающую подпоследовательность.

Входные данные
В первой строке задано одно число n (1 ≤ n ≤ 2000) — длина подпоследовательности. В следующей строке задано n целых чисел ai ( - 109 ≤ ai ≤ 109) — элементы последовательности.

Выходные данные
В первой строке выведите число k — длину наибольшей возрастающей подпоследовательности. В следующей строке выведите k чисел — саму подпоследовательность.


# D. Расстояние по Левенштейну
Дана текстовая строка. С ней можно выполнять следующие операции:

1. Заменить один символ строки на другой символ.

2. Удалить один произвольный символ.

3. Вставить произвольный символ в произвольное место строки.

Например, при помощи первой операции из строки «СОК» можно получить строку «СУК», при помощи второй операции — строку «ОК», при помощи третьей операции — строку «СТОК».

Минимальное количество таких операций, при помощи которых можно из одной строки получить другую, называется стоимостью редактирования или расстоянием Левенштейна.

Определите расстояние Левенштейна для двух данных строк.

Входные данные
Программа получает на вход две строки, длина каждой из которых не превосходит 1000 символов, строки состоят только из заглавных латинских букв.

Выходные данные
Требуется вывести одно число — расстояние Левенштейна для данных строк.


# E. Кафе
Около Петиного университета недавно открылось новое кафе, в котором действует следующая система скидок: при каждой покупке более чем на 100 рублей покупатель получает купон, дающий право на один бесплатный обед (при покупке на сумму 100 рублей и меньше такой купон покупатель не получает).

Однажды Пете на глаза попался прейскурант на ближайшие n дней. Внимательно его изучив, он решил, что будет обедать в этом кафе все n дней, причем каждый день он будет покупать в кафе ровно один обед. Однако стипендия у Пети небольшая, и поэтому он хочет по максимуму использовать предоставляемую систему скидок так, чтобы его суммарные затраты были минимальны. Требуется найти минимально возможную суммарную стоимость обедов и номера дней, в которые Пете следует воспользоваться купонами.

Входные данные
В первой строке входного файла записано целое число n (0 ≤ n ≤ 100). В каждой из последующих n строк записано одно целое число, обозначающее стоимость обеда в рублях на соответствующий день. Стоимость — неотрицательное целое число, не превосходящее 300.

Выходные данные
В первой строке выдайте минимальную возможную суммарную стоимость обедов. Во второй строке выдайте два числа k1 и k2 — количество купонов, которые останутся неиспользованными у Пети после этих n дней и количество использованных им купонов соответственно.

В последующих k2 строках выдайте в возрастающем порядке номера дней, когда Пете следует воспользоваться купонами. Если существует несколько решений с минимальной суммарной стоимостью, то выдайте то из них, в котором значение k1 максимально (на случай, если Петя когда-нибудь ещё решит заглянуть в это кафе). Если таких решений несколько, выведите любое из них.
