# Визуализация выпуклой оболочки (Алгоритм Грэхема)

## 📖 Постановка задачи
Реализовать программу в виде оконного приложения, реализующего ввод в графическое поле набора точек, построение на этом наборе точек минимальной выпуклой оболочки и вывод на экран результата.
Язык программирования — C++. Разрешается использовать любые доступные фреймворки для построения оконных приложений. Запрещается использовать готовые библиотечные решения для построения оболочек.

## 📝 Описание проекта
Данное приложение демонстрирует работу алгоритма Грэхема для построения минимальной выпуклой оболочки множества точек на плоскости. Пользователь может добавлять точки вручную, генерировать случайные наборы, редактировать координаты и наблюдать, как оболочка перестраивается в реальном времени.

## ⚙️ Технические требования
- **Язык:** C++17 / C++20
- **Библиотека:** SFML 3.x (Graphics, Window, System)
- **Сборка:** CMake 3.15+
- **Шрифт:** `resources/arial.ttf` (включён в репозиторий)
- **ОС:** Windows 10/11, Linux, macOS

## 🛠 Сборка и запуск

### 📦 Подготовка зависимостей
Убедитесь, что SFML 3 доступен в вашей системе:
- **Windows:** Скачайте готовые бинарники с [официального сайта SFML](https://www.sfml-dev.org/) или используйте vcpkg.
- **Linux:** `sudo apt install libsfml-dev` (Ubuntu/Debian) или аналог для вашего дистрибутива.
- **macOS:** `brew install sfml`

### 🚀 Сборка через CMake (кроссплатформенный способ)
```bash
# Создание папки сборки
mkdir build && cd build

# Конфигурация
cmake ..

# Компиляция
cmake --build . --config Release

# Запуск
Windows: .\Release\ConHull.exe
Linux/macOS: ./ConHull
```

### Windows
Важно: Укажите правильные пути к SFML (-I для заголовков, -L для библиотек). Если SFML установлен в другую папку, измените путь соответственно

#### Прямая компиляция через g++
```batch
:: Компиляция всех файлов + линковка SFML
g++ -std=c++17 -Wall -mwindows ^
    -I"C:\SFML\include" -L"C:\SFML\lib" ^
    ConHull.cpp ^
    Point.cpp GameState.cpp Renderer.cpp ^
    InputHandler.cpp Button.cpp InputField.cpp ^
    EditPointWindow.cpp ConvexHull.cpp ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -o ConHull.exe

:: Копирование ресурсов (обязательно!)
xcopy /E /I resources resources\

:: Запуск
ConHull.exe
```
### С помощью Makefile (рекомендуется)
```batch
:: Создание папки сборки
mkdir build && cd build

:: Генерация проекта
cmake .. -G "MinGW Makefiles" -DSFML_DIR="C:/SFML/lib/cmake/SFML"

:: Сборка
cmake --build . --config Release

:: Копирование ресурсов
xcopy /E /I ..\resources Release\resources\

:: Запуск
Release\ConHull.exe
```
### Linux|macOS
```batch
# Создание папки сборки
mkdir build && cd build

# Генерация + сборка
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Копирование ресурсов
cp -r ../resources ./

# Запуск
./ConHull
```

## 📊 Архитектура проекта

```mermaid
graph TD
    Main[ConHull.cpp] --> State[GameState]
    Main --> Input[InputHandler]
    Main --> Render[Renderer]
    Main --> EditWin[EditPointWindow]
    
    Input --> State
    Input --> Btn[Button]
    Input --> Field[InputField]
    
    Render --> State
    Render --> Btn
    Render --> Field
    Render --> EditWin
    
    EditWin --> Field
    EditWin --> Btn
    
    State --> Point[Point]
    State --> Hull[ConvexHull]
    
    Hull --> Point
```
### 📁 Структура проекта 

Convex-Hull/  
├── src/                 # Исходный код (.cpp)  
│   ├── ConHull.cpp      # Точка входа, цикл обработки событий SFML 3 (main)  
│   ├── ConvexHull.cpp   # Алгоритм Грэхема  
│   ├── Renderer.cpp     # Отрисовка графики и UI  
│   ├── InputHandler.cpp # Обработка ввода мыши и клавиатуры  
│   ├── GameState.cpp    # Состояние приложения и конфигурация  
│   ├── Button.cpp       # UI-компонент: кнопка  
│   ├── InputField.cpp   # UI-компонент: поле ввода  
│   ├── EditPointWindow.cpp # Всплывающее окно редактирования точки  
│   └── Point.cpp        # Утилиты для работы с точками  
├── include/             # Заголовочные файлы (.h)  
├── resources/           # Ресурсы (arial.ttf)  
├── CMakeLists.txt       # Конфигурация сборки CMake  
├── ConHull.sln          # Решение Visual Studio  
└── README.md            # Этот файл  

### 🎮 Работа программы
![Convex Hull Visualization 2026-04-08 16-42-54](https://github.com/user-attachments/assets/2dbbc756-1c1a-44c3-97a7-ee4a59fc8cad)

### Генерация множества из случайных 20 точек
<img width="1179" height="793" alt="image" src="https://github.com/user-attachments/assets/b9333e77-8407-4092-8575-252c4c8addea" />



### Генерация множества из случайных 50 точек
<img width="1180" height="794" alt="image" src="https://github.com/user-attachments/assets/67b65275-5435-43c2-9df9-0c7587548543" />


### Пустое поле после нажатия кнопки "Очистить"
<img width="1181" height="793" alt="image" src="https://github.com/user-attachments/assets/6fcb262e-7d5a-49df-a17f-d92f6c78969a" />


### Режим добавления точек
<img width="1188" height="800" alt="image" src="https://github.com/user-attachments/assets/0e368f1b-5034-4b45-ae5e-14b84fab4f2f" />


<img width="1188" height="799" alt="image" src="https://github.com/user-attachments/assets/f560951e-08a4-4c04-b24d-4f14dc787969" />


### Пошаговое удаление точек
<img width="1184" height="794" alt="image" src="https://github.com/user-attachments/assets/17dbee04-b259-42c3-99a8-56b816e81e09" />


<img width="1177" height="792" alt="image" src="https://github.com/user-attachments/assets/6d264011-be4e-4ee1-86de-5cb923f25d5d" />


### Режим изменения координат точки
<img width="1190" height="806" alt="image" src="https://github.com/user-attachments/assets/b907153a-b7aa-4c31-ace4-e4cf14304fcc" />

<img width="1176" height="796" alt="image" src="https://github.com/user-attachments/assets/ef9913ce-767f-4d44-bf7f-d9a5482426cd" />

<img width="1185" height="791" alt="image" src="https://github.com/user-attachments/assets/04497640-d5ca-4699-a3c9-8f3583bf6231" />


