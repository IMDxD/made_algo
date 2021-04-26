# A. Set
Реализуйте множество с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 1000000. В каждой строке находится одна из следующих операций:

insert x — добавить элемент x в множество. Если элемент уже есть в множестве, то ничего делать не надо.
delete x — удалить элемент x. Если элемента x нет, то ничего делать не надо.
exists x — если ключ x есть в множестве выведите «true», если нет «false».
В множество помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists. Следуйте формату выходного файла из примера.


# B. Map
Реализуйте ассоциативный массив с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put x y — поставить в соответствие ключу x значение y. Если ключ уже есть, то значение необходимо изменить.
delete x — удалить ключ x. Если элемента x нет, то ничего делать не надо.
get x — если ключ x есть в ассоциативном массиве, то выведите соответствующее ему значение, иначе выведите «none».
Ключи и значения — строки из латинских букв длинной не более 20 символов.
Выходные данные
Выведите последовательно результат выполнения всех операций get. Следуйте формату выходного файла из примера.


# C. LinkedMap
Реализуйте прошитый ассоциативный массив с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put x y — поставить в соответствие ключу x значение y. Если элемент уже есть, то значение необходимо изменить.
delete x — удалить ключ x. Если элемента x нет, то ничего делать не надо.
get x — если ключ x есть в множестве выведите соответствующее ему значение, если нет выведите «none».
prev x — вывести значение соответствующее ключу находящемуся в ассоциативном массиве, который был вставлен позже всех, но до x или «none», если такого нет или в массиве нет x.
next x — вывести значение соответствующее ключу находящемуся в ассоциативном массиве, который был вставлен раньше всех, но после x или «none», если такого нет или в массиве нет x.
Ключи и значения — строки из латинских букв длинной не более 20 символов.
Выходные данные
Выведите последовательно результат выполнения всех операций get, prev, next. Следуйте формату выходного файла из примера.


# D. MultiMap
Реализуйте множественное отображение с использованием хеш таблиц.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put x y — добавить пару (x,y). Если пара уже есть, то второй раз её добавлять не надо.
delete x y — удалить пару (x,y). Если пары нет, то ничего делать не надо.
deleteall x — удалить все пары с первым элементом x.
get x — вывести количество пар с первым элементом x, а затем вторые элементы всех этих пар в произвольном порядке.
Ключи и значения — строки из латинских букв длинной не более 20 символов.
Выходные данные
Выведите последовательно результат выполнения всех операций get. Следуйте формату выходного файла из примера. Гарантируется, что размер выходного файла не превысит 10 мегабайт.