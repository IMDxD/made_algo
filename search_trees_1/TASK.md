# A. Простое двоичное дерево поиска
Реализуйте просто двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 100. В каждой строке находится одна из следующих операций:

insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо;
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;
exists x — если ключ x есть в дереве выведите «true», если нет «false»;
next x — выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;
prev x — выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.


# B. Сбалансированное двоичное дерево поиска
Реализуйте сбалансированное двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 105. В каждой строке находится одна из следующих операций:

insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо;
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;
exists x — если ключ x есть в дереве выведите «true», если нет «false»;
next x — выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;
prev x — выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.


# C. K-й максимум
Напишите программу, реализующую структуру данных, позволяющую добавлять и удалять элементы, а также находить k-й максимум.

Входные данные
Первая строка входного файла содержит натуральное число n — количество команд (n≤100000). Последующие n строк содержат по одной команде каждая. Команда записывается в виде двух чисел ci и ki — тип и аргумент команды соответственно (|ki|≤109). Поддерживаемые команды:

+1 (или просто 1): Добавить элемент с ключом ki.
 0: Найти и вывести ki-й максимум.
-1: Удалить элемент с ключом ki.
Гарантируется, что в процессе работы в структуре не требуется хранить элементы с равными ключами или удалять несуществующие элементы. Также гарантируется, что при запросе ki-го максимума, он существует.

Выходные данные
Для каждой команды нулевого типа в выходной файл должна быть выведена строка, содержащая единственное число — ki-й максимум.


# D. И снова сумма
Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:

 — добавить в множество S число i (если он там уже есть, то множество не меняется);
 — вывести сумму всех элементов x из S, которые удовлетворяют неравенству l ≤ x ≤ r.
Входные данные
Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1 ≤ n ≤ 300 000).Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? l r». Операция «? l r» задает запрос .

Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию . Если же она идет после запроса «?», и результат этого запроса был y, то выполняется операция .

Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 109.

Выходные данные
Для каждого запроса выведите одно число — ответ на запрос.
