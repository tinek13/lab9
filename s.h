#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <limits>

struct visit
{
    std::string patient;
    int insurance;
    int card;
    std::string doctor;
    std::string date;
    std::string diagnosis;
    std::string therapy;
};

void findlastvisit(visit *collection, int *N)
{
    std::string LastDate = "00.00.0000"; // начальная дата
    int LastIndex = 0;

    for (int i = 0; i < *N; i++)
    {
        if (collection[i].date > LastDate)
        {
            LastDate = collection[i].date;
            LastIndex = i;
        }
    }

    // вывод информации о пациенте с самой поздней датой обращения
    std::cout << "Пациент с самой поздней датой обращения в поликлинику" << std::endl;
    std::cout << "Пациент: " << collection[LastIndex].patient << std::endl;
    std::cout << "Дата обращения: " << collection[LastIndex].date << std::endl;
    std::cout << '\n';
}

void DoctorPatients(visit *collection, int *N)
{
    std::string doctors[*N];
    int doctorCount = 0;

    // Собираем уникальный список врачей
    for (int i = 0; i < *N; i++)
    {
        bool isUnique = true;
        for (int j = 0; j < doctorCount; j++)
        {
            if (collection[i].doctor == doctors[j])
            {
                isUnique = false;
                break;
            }
        }
        if (isUnique)
        {
            doctors[doctorCount] = collection[i].doctor;
            doctorCount++;
        }
    }

    // Выводим список врачей
    std::cout << "Список врачей:" << std::endl;
    for (int i = 0; i < doctorCount; i++)
    {
        std::cout << i + 1 << ". " << doctors[i] << std::endl;
    }

    // Предлагаем пользователю выбрать врача
    int choice;
    do
    {
        std::cout << "Выберите номер врача (1-" << doctorCount << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > doctorCount);

    std::string selectedDoctor = doctors[choice - 1];

    // Подсчитываем количество пациентов для выбранного врача
    int count = 0;
    for (int i = 0; i < *N; i++)
    {
        if (collection[i].doctor == selectedDoctor)
        {
            count++;
        }
    }

    std::cout << "Общее количество пациентов, принятых врачом " << selectedDoctor << ": " << count << std::endl;
}

void vivo(visit *collection, int *N)
{
    for (int i = 0; i < *N; i++)
    {
        std::cout << "Пациент: " << collection[i].patient << std::endl;
        std::cout << "Полис: " << collection[i].insurance << std::endl;
        std::cout << "Мед. карта: " << collection[i].card << std::endl;
        std::cout << "Доктор: " << collection[i].doctor << std::endl;
        std::cout << "Дата: " << collection[i].date << std::endl;
        std::cout << "Диагноз: " << collection[i].diagnosis << std::endl;
        std::cout << "Лечение: " << collection[i].therapy << std::endl;
        std::cout << '\n';
    }
}

visit* infles(int *N)
{   
    // Открытие файла
    std::ifstream inputFile("data1.txt");
    visit *collection;
    // Проверка, открылся ли файл или нет
    if (!inputFile)
    {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return nullptr;
    }

    // Чтение информации из файла
    //for (int i = 0; i < N; i++)
    visit *col;
    
    int collection1 = 0;  //  +1 
    int tempopenis = *N;
    collection = new visit[tempopenis]; 
    while(inputFile >> collection[collection1].patient)
    {

        //std::getline(inputFile, collection[i].patient);
        inputFile >> collection[collection1].insurance;
        inputFile >> collection[collection1].card;
        inputFile >> collection[collection1].doctor;
        inputFile >> collection[collection1].date;
        inputFile >> collection[collection1].diagnosis;
        inputFile >> collection[collection1].therapy;
        collection1 += 1 ;
        if(tempopenis == collection1 + 1)
        {
          col = new visit[tempopenis * 2];
          for(int i = 0 ; i < tempopenis; i++) // перенос из одного массива в другой
          {
            col[i] = collection[i];
          }
          delete[] collection;
          collection = col;
          tempopenis *= 2;

        }

        
    }
    *N = collection1;
    return collection;   
}

int main()
{
    // Возможность использовать русские символы
    setlocale(LC_ALL, "Russian");

    int *N = new int;
    *N = 10;
    visit *collection;

    collection = infles(N);

    // Вывод на экран информации из файла

    std::cout << "Количество записей после чтения файла: " << *N << std::endl;

    int choice;
    do
    {
        std::cout << "Меню:\n";
        std::cout << "1. Вывести все записи\n";
        std::cout << "2. Найти пациента с самой поздней датой обращения\n";
        std::cout << "3. Вывести список пациентов для выбранного врача\n";
        std::cout << "4. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            vivo(collection, N);
            break;
        case 2:
            findlastvisit(collection, N);
            break;
        case 3:
            DoctorPatients(collection, N);
            break;
        case 4:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова.\n";
        }

    } while (choice != 4);

    delete[] collection;
    return 0;
}


//шоколадки
