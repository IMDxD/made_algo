# A. k-я имперская порядковая статистика

Батальон клонов вышел на построение. Все имперцы стали в один ряд и пересчитались: первый, второй, третий, …, n-й. Каждый из них держит в руках бумажку с результатом своего тестирования IQ. Как известно, результатом тестирования IQ является число от 1 до 109.

Периодически к батальону подходит граф Дуко, размахивает мечом и делает запрос: «Если всех клонов с i-го по j-го упорядочить по результату теста, то какое значение будет у клона, стоящем на k-м месте?» — и быстро требует ответ, грозя всю партию пустить в расход. Большая просьба — решите эту задачу и помогите клонам выжить.

Входные данные
В первой строке входного файла содержится целое число n — количество клонов (1≤n≤1000).

Во второй строке содержатся эти n целых чисел, разделённые пробелами. Числа находятся в промежутке от 1 до 109.

В третьей строке содержится число m — количество запросов (1≤m≤105).

Последние m строк содержат запросы в формате «i j k». Гарантируется, что запросы корректны, то есть 1≤i≤j≤n и на отрезке от i-го до j-го элемента включительно есть хотя бы k элементов.

Выходные данные
На каждый запрос выведите единственное число — ответ на запрос.


# B. Сортировка подсчетом

Дан список из N элементов, которые принимают целые значения от 0 до 100. Отсортируйте этот список в порядке неубывания элементов. Выведите полученный список.

Входные данные
На одной строке дан массив из N элементов. (1 ≤ N ≤ 2·105) — количество элементов в массиве. Гарантируется, что все элементы массива принимают целые значения от 0 до 100.

Выходные данные
Выведите отсортированный список элeментов


# C. Цифровая сортировка

Дано n строк, выведите их порядок после k фаз цифровой сортировки.

В этой задаче требуется реализовать цифровую сортировку.

Входные данные
В первой строке входного файла содержится число n — количество строк, m — их длина и k – число фаз цифровой сортировки (1≤n≤1000, 1≤k≤m≤1000). В следующих n строках находятся сами строки.

Выходные данные
Выведите строки в порядке в котором они будут после k фаз цифровой сортировки.


# D. Гриша после дискотеки

На следующий день после дискотеки Гриша решил устроить детям «взрыв мозга». Он взял много карточек и написал на каждой из них одну латинскую букву в нижнем регистре. А после этого придумал свою строку и задал детям задание: составить как можно больше подстрок своей строки, используя карточки. Гришина строка состоит только из букв латинского алфавита в нижнем регистре. Вам нужно определить сколько её подстрок можно составить, используя только данные карточки.

Запишем буквы, написанные на карточках, подряд друг за другом. Тогда если Гришина строка — это «aaab», а карточки — это «aba», то можно составить три подстроки «a», подстроку «b», две подстроки «aa» и подстроки «ab» и «aab». А подстроки «aaa» и «aaab» нельзя, так как есть всего две карточки с буквой «a».

Входные данные
Первая строка входных данных содержит два целых числа n и m (1≤n,m≤105) — длину строки Гриши и длину строки карточек.

Вторая строка входных данных содержит Гришину строку s длины n, состоящую только из букв латинского алфавита в нижнем регистре.

Третья строка входных данных содержит строку карточек t длины m, состоящую только из букв латинского алфавита в нижнем регистре.

Выходные данные
Выведите одно целое число — количество подстрок в s, которые можно составить из символов строки t.