Алгортим Эрли
-------------

Сет-ап и запуск
---------------
Для установки проекта нужно исполнить комманду из корня репозитория

`cmake CMakeLists.txt && make`

Для запуска основной программы нужно исполнить комманду

`./pract_2`

Для запуска тестов нужно исполнить комманду

`./bin/unit_tests`

Тесты находятся в файле 

`testing/tests/main.cpp`

Протестированны грамматики: ПСП, палиндромы, арифмитические выражения.

Формат ввода грамматики и слова для проверки
-------
В первой строке задается *n* - количество правил и начальный символ

В следующих *n* строках идут правила в виде *leftSide* *rightSide*, где 
в *leftSide* находится 1 символ - нетерминал. В *rightSide* находится правая часть
правила.

В последней строке вводится слово для проверки

#### Пример
```
5 S
S C
D aDb
S SC
C cD
D _
cccccaaaabbbb
```

Формат вовода
----
В единственной строке выводится слово `YES` если слово принадлежит граммтике иначе `NO`.

