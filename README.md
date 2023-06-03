# К_34 Моделирование работы автозаправочной станции
Надо моделировать работу автозаправочной станции следующей конструкции.

## Система, автозаправочная станция состоит из следующих элементов:
+ оператора автозаправочной станции;
+ пульта управления;
+ множества бензоколонок, с определенной маркой топлива, исходным объемом топлива;
+ множество автомобилей, с запросом определенной марки и необходимого объема топлива;
+ экрана отображения информации о функционировании системы.

## Правила функционирования системы.
1. Время измеряется в тактах.
2. За один такт автомобиль заезжает на автозаправку и делает запрос у оператора на покупку топлива.
3. За один такт, оператор обрабатывает запрос. При наличии необходимого топлива нужной марки и в нужном объеме, оператор ставит автомобиль в очередь к бензоколонке. При отсутствии топлива в необходимом для автомобиля объеме, в обслуживании отказывают. Автомобиль покидает автозаправку.
4. Каждая бензоколонка имеет уникальный номер и заправляет топливо одной марки. Двух бензоколонок с одинаковой маркой топлива нет. Время обслуживания одного автомобиля зависит от объема приобретенного топлива. Около бензоколонки может образоваться очередь. За один такт из очереди к бензоколонке можно поставить автомобиль на заправку и начать заправку. За один такт бензоколонка заливает 10 литров топлива. На последнем такте заправки автомобиль покидает автозаправку.

Запрос от автомобилей объема топлива кратна 10 литрам. В течении одного такта оператор может поставить в очередь или отказать не более одному автомобилю. В течении такта на автозаправку может подъехать не более одного автомобиля.

## Команды системы.
Команда запроса от автомобиля.
> Fill up the tank «номер автомобиля» «тип топлива» «количество топлива»

_Данная команда моделирует запрос от автомобиля на топливо. Исходя из типа и объема топлива определяется наличие достаточного количества топлива (не проданного). Если топливо в достаточном количестве, то автомобиль ставиться в очередь к соответствующей бензоколонке. Если топлива недостаточно, то выдается отказ на обслуживание._

Команда вывода списка обслуженных автомобилей бензоколонкой.
> Display the petrol filling station status «номер бензоколонки»

_По данной команде выдается построчно список обслуженных автомобилей. После отработки команды элементы системы выполняют действия согласно такту._

Команда выдачи состояния системы.
> Display the system status

_По данной команде выводиться состояние системы в начале текущего такта. Информация содержит перечень бензоколонок, объем не проданного остатка топлива, величину очереди. Остаток считается с учетом автомобилей из очереди.  Еще выводится сколько автомобилей было заправлено на бензоколонке. Бензоколонки упорядочены по номерам. Относительно оператора выводиться информация: сколько автомобилей было всего заправлено и сколько еще стоят в очереди. После отработки команды элементы системы выполняют действия согласно такту._

Пустая команда (строка ничего не содержит). Элементы системы выполняют действия согласно такту.

Команда завершения работы системы.
> Turn off the system

## Построить систему, которая использует объекты:
1. Объект «система». Организует отработку тактов.
2. Объект для чтения команд и данных. Объект моделирует работу оператора. Считывает данные для подготовки и настройки системы. После чтения очередной строки данных для настройки или данных команды, объект выдает сигнал с текстом полученных данных. Все данные настройки и данные команд синтаксический корректны. Каждая строка команд соответствует одному такту. Если строка пустая, то система отрабатывает один такт.
3. Объект пульта управления моделирует работу оператора и его устройства управления, для отработки поступивших команд (запросов). Объект выдает соответствующий сигнал или сигналы. Содержит список номеров бензоколонок. Управляет распределением автомобилей по бензоколонкам. Определяет возможность выполнения запроса. Если возможно, то ставит автомобиль в очередь к соответствующей бензоколонке, иначе выдает сообщение об отказе. Готовит данные исходя из состояния системы. Оператор сообщает автомобилю номер бензоколонки. Действие выполняется в рамках одного такта.
4. Объект, моделирующий бензоколонку. Выдает сигнал о начале заправки или завершении заправки автомобиля. Обрабатывает содержимое очереди. По команде вывода списка обслуженных автомобилей выдает сигналы к устройству вывода с текстом необходимой информации.
5. Объект, моделирующий автомобиль. Объект создается (заходит на автозаправку) по команде запроса.  Содержит номе автомобиля, марку топлива и объем необходимой для заправки. При поступлении команды данный объект добавляется в подчиненные элементы к объекту пульта управления. После распределения объект перестыковывается к соответствующему объекту бензоколонки. После завершения обслуживания, объект удаляется из дерева объектов и уничтожается (покидает автозаправку). В базовый класс добавить метод удаления из дерева иерархии и уничтожения объекта.
6. Объект для вывода состояния или результата команды системы на консоль. Текст для вывода объект получает по сигналу от других объектов системы. Каждое присланное сообщение выводиться с новой строки.

## Написать программу, реализующую следующий алгоритм:
1. Вызов метода объекта «система» build_tree_objects().
    1. Построение дерева иерархии объектов. Характеристики объектов вводятся.
    2. Цикл для обработки вводимых данных и загрузки исходного состояния системы.
        1. Выдача сигнала объекту чтения для ввода данных.
        2. Отработка операции загрузки очередной порции данных.
        3. Установка связей сигналов и обработчиков с новым объектом.
    3. Установка связей сигналов и обработчиков между объектами.
2. Вызов метода объекта «система» exec_app().
    1. Приведение всех объектов в состояние готовности.
    2. Цикл для обработки вводимых команд.
        1. Выдача сигнала объекту для ввода команды.
        2. Отработка команды.
    3. После ввода команды «Turn off the system» завершить работу.

Все приведенные сигналы и соответствующие обработчики должны быть реализованы. Запрос от объекта означает выдачу сигнала. Все сообщения на консоль выводятся с новой строки.

В набор поддерживаемых команд добавить команду «SHOWTREE» и по этой команде вывести дерево иерархии объектов системы с отметкой о готовности и завершить работу системы (программы).

_При решении задачи необходимо руководствоваться методическим пособием и приложением к методическому пособию_

## Входные данные
Ввод информации о бензоколонках:
> «номер бензоколонки» «тип топлива» «объем топлива в литрах»

Завершение ввода информации о бензоколонках.
> End of information about petrol filling station

Далее следуют команды. Каждая команда выполняется в рамках одного такта.

Последней командой является:
> Turn off the system

__Пример ввода:__
```
PS_1 A-72  100
PS_2 A-76  1000
PS_3 AI-91 1000
PS_4 AI-93 1000
PS_5 AI-95 1000
End of information about petrol filling stations
Fill up the tank rus77-001 A-72 30
 
Fill up the tank rus77-002 AI-93 50
Fill up the tank rus77-003 AI-93 50
Fill up the tank rus77-004 AI-93 50
 
 
 
 
 
Display the petrol filling station status PS_1
 
 
Display the system status
 
Display the petrol filling station status PS_4
 
 
 
 
 
 
Display the petrol filling station status PS_4
Display the system status
Turn off the system
```
## Выходные данные
После завершения построения дерева иерархии объектов и загрузки исходных данных отображается:
> Ready to work

Шаблон вывода информации о состоянии бензоколонки:
> Petrol filling station status «номер бензоколонки» «количество автомобилей в очереди» «количество обслуженных»

Далее построчно:
> «номер уже обслуженного автомобиля согласно очереди»\n
. . . .

Шаблон выдачи состояния системы:
>  Petrol station «номер бензоколонки» «объем не проданного остатка» «длина очереди»\
. . . .\
Operator «количество заправленных» «стоят в очереди»

Сообщение при отказе в обслуживании:
> Denial of service «номер автомобиля»

Сообщение завершения работы системы:
> Turn off the system

__Пример вывода:__
```
Ready to work
Petrol filling station status PS_1 0 1
rus77-001
Petrol station PS_1 70 0
Petrol station PS_2 1000 0
Petrol station PS_3 1000 0
Petrol station PS_4 850 1
Petrol station PS_5 1000 0
Operator 3 1
Petrol filling station status PS_4 0 2
rus77-002
rus77-003
Petrol filling station status PS_4 0 3
rus77-002
rus77-003
rus77-004
Petrol station PS_1 70 0
Petrol station PS_2 1000 0
Petrol station PS_3 1000 0
Petrol station PS_4 850 0
Petrol station PS_5 1000 0
Operator 4 0
Turn off the system
```