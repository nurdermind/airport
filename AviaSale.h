//
// Created by nerdermind on 28.12.23.
//

#ifndef AIRPORT_H
#define AIRPORT_H
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Flight.h"

using namespace std;


// Аэропорт управляет рейсами
class AviaSale {
public:
    int test;

    AviaSale() : head_flight(nullptr) {
    }

    ~AviaSale() {
        delete_flights();
    }

    void delete_flights() {
        const Flight* current_flight = head_flight;
        while (current_flight) {
            Flight* next_flight = current_flight->get_next();
            delete current_flight;
            current_flight = next_flight;
        }
        head_flight = nullptr;
    }

    Flight* get_flight(const string& number_airplane) {
        Flight* founded_flight = head_flight;
        // Ищем нужный рейс пока список не кончился
        while (founded_flight && founded_flight->get_number_airplane() != number_airplane) {
            founded_flight = founded_flight->get_next();
        }
        if (founded_flight && founded_flight->get_number_airplane() == number_airplane) return founded_flight;
        return nullptr;
    }

    void buy_ticket(const string& number_airplane) {
        Flight* flight = get_flight(number_airplane);
        if (!flight) {
            cout << "Рейс с номером " << number_airplane << " не найден";
            return;
        }

        if (flight->get_total_number_of_seats() < flight->get_number_of_tickets_sold() + 1) {
            cout << "Свободные места кончились :(" << endl;
            return;
        }

        try {
            flight->set_number_of_tickets_sold(flight->get_number_of_tickets_sold() + 1);
            cout << "Билеты успешно приобретены!";
        } catch (const exception& e) {
            cerr << endl << e.what() << endl;
        }
    }

    // -------------------- CRUD ----------------------

    void delete_flight(const string& number_airplane) {
        Flight* flight = get_flight(number_airplane);
        if (!flight) {
            printf("Рейс с номер %s не найден", number_airplane.c_str());
            return;
        }

        Flight* prev_flight = flight->get_prev();
        Flight* next_flight = flight->get_next();

        if (!prev_flight) {
            head_flight = next_flight;
        }
        if (prev_flight) {
            prev_flight->set_next(next_flight);
        }
        if (next_flight) {
            next_flight->set_prev(prev_flight);
        }

        cout << "Рейс успешно удалён " << endl;
    }

    void add_flight() {
        string input_value;
        string number_airplane;
        string destination_airport;
        string departure_time;
        string arrival_time;
        int total_number_of_seats;
        int number_of_tickets_sold;

        Flight* new_flight = new Flight();

        cout << "Введите номер самолёта: ";
        cin >> number_airplane;

        // Check if the flight with the given number already exists
        if (get_flight(number_airplane) != nullptr) {
            cerr << "Рейс с номером " << number_airplane << " уже существует." << endl;
            return;
        }
        new_flight->set_number_airplane(number_airplane);

        while (1) {
            try {
                cout << "Введите аэропорт назначения: ";
                cin >> destination_airport;
                new_flight->set_destination_airport(destination_airport);

                cout << "Введите время вылета: ";
                cin >> departure_time;
                new_flight->set_departure_time(departure_time);

                cout << "Введите время прибытия: ";
                cin >> arrival_time;
                new_flight->set_arrival_time(arrival_time);

                cout << "Введите общее количество мест: ";
                cin >> total_number_of_seats;
                new_flight->set_total_number_of_seats(total_number_of_seats);

                cout << "Введите количество проданных билетов: ";
                cin >> number_of_tickets_sold;
                new_flight->set_number_of_tickets_sold(number_of_tickets_sold);


                new_flight->set_next(head_flight);
                if (head_flight) {
                    head_flight->set_prev(new_flight);
                }
                head_flight = new_flight;
                break;
            } catch (const exception& e) {
                cout << endl << e.what() << endl;
            }
        }
        save_to_file();
    }

    void edit_flight(const string& number_airplane) {
        string string_input_value;
        int number_input_value;


        Flight* flight = get_flight(number_airplane);
        if (!flight) {
            cout << "Рейс с номером " << number_airplane << " не найден";
            return;
        }
        try {
            int choice_variant;
            cout << "Выберите поле для изменения:\n"
                    "1. Номер самолёта\n"
                    "2. Аэропорт назначения\n"
                    "3. Время вылета\n"
                    "4. Время прилёта\n"
                    "5. Общее число мест\n"
                    "6. Количество проданных билетов\n";
            cin >> choice_variant;
            switch (choice_variant) {
                case 1: // Номер самолёта
                    cout << "Введите новый номер самолёта (" << flight->get_number_airplane() << "): ";
                    cin >> string_input_value;
                    flight->set_number_airplane(string_input_value);
                    break;

                case 2: // Аэропорта назначения
                    cout << "Введите новый Аэропорт назначения (" << flight->get_number_airplane() << "): ";
                    cin >> string_input_value;
                    flight->set_destination_airport(string_input_value);
                    break;

                case 3: // Время вылета
                    cout << "Введите новое время вылета (" << flight->get_number_airplane() << "): ";
                    cin >> string_input_value;
                    flight->set_departure_time(string_input_value);
                    break;

                case 4: // Время прибытия
                    cout << "Введите новое время прибытия (" << flight->get_number_airplane() << "): ";
                    cin >> string_input_value;
                    flight->set_arrival_time(string_input_value);
                    break;

                case 5: // Общее число мест
                    cout << "Введите новое количество мест (" << flight->get_number_airplane() << "): ";
                    cin >> number_input_value;
                    flight->set_total_number_of_seats(number_input_value);
                    break;

                case 6: // Количества проданных билетов

                    cout << "Введите новое количество проданных мест (" << flight->get_number_airplane() << "): ";
                    cin >> number_input_value;
                    flight->set_number_of_tickets_sold(number_input_value);
                    break;

                default:
                    break;
            }


            cout << "Данные обновлены " << endl;
        } catch (const exception& e) {
            cerr << endl << e.what() << endl;
        }
        save_to_file();
    }

    void show_flight(const string& number_airplane) {
        Flight* flight = get_flight(number_airplane);
        if (flight) flight->show_info();
        else cout << "Рейс с номером " << number_airplane << " не найден";
    }

    void show_all_flights() {
        Flight* current_flight = head_flight;
        while (current_flight) {
            current_flight->show_info();
            current_flight = current_flight->get_next();
        };
    }

    void show_by_destination_airport(const string& destination_airport) {
        Flight* current_flight = head_flight;
        while (current_flight) {
            if (current_flight->get_destination_airport() == destination_airport)
                current_flight->show_info();
            current_flight = current_flight->get_next();
        };
    }

    // -------------------- CRUD ----------------------

    // Выводит вырианты действий в консоль
    static void show_menu() {
        cout << " |-----------------------------------------------------------------------|\n";
        cout << " |  Выберите пункт из меню:                                              |\n";
        cout << " |  1. Добавить рейс в список                                            |\n";
        cout << " |  2. Вывести данные о всех рейсах                                      |\n";
        cout << " |  3. Вывести данные рейса по номеру самолёта                           |\n";
        cout << " |  4. Вывести данные самолётов, направляющихся в назначенный аэропорт   |\n";
        cout << " |  5. Купить билет на самолёт                                           |\n";
        cout << " |  6. Редактировать рейс из списка                                      |\n";
        cout << " |  7. Удалить рейс из списка                                            |\n";
        cout << " |-----------------------------------------------------------------------|\n";
    }

    void enter() {
        int choice;
        string input_value;


        while (true) {
            system("clear");
            show_menu();

            cout << "Введите номер действия: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    system("clear");
                    cout << "\t\t\tДОБАВЛЕНИЕ РЕЙСА: \n";
                    add_flight();
                    break;

                case 2:
                    system("clear");
                    cout << "\t\t\tТАБЛО РЕЙСОВ: \n";
                    show_all_flights();
                    break;

                case 3:
                    system("clear");
                    cout << "Введите номер самолета: ";
                    cin >> input_value;
                    show_flight(input_value);
                    break;

                case 4:
                    cout << "Введите аэропорт назначения: \n";
                    cin >> input_value;
                    show_by_destination_airport(input_value);
                    break;

                case 5:
                    system("clear");
                    cout << "\t\t\tПОКУПКА БИЛЕТА:\n";
                    cout << "Введите номер самолета: \n";
                    cin >> input_value;
                    buy_ticket(input_value);
                    break;

                case 6:
                    system("clear");
                    cout << "\t\t\tРЕДАКТИРОВАНИЕ РЕЙСА:\n";
                    cout << "Введите номер самолета: \n";
                    cin >> input_value;
                    edit_flight(input_value);
                    break;

                case 7:
                    cin >> input_value;
                    delete_flight(input_value);
                    break;

                default:
                    cout << "Ошибка ввода данных!";
            }
            cout << endl;
            system("read -p \"Нажмите Ввод чтобы продолжить\"");
        }
    }

    void save_to_file() {
        ofstream csv_file("/home/nerdermind/CLionProjects/airport/flights.csv");
        if (!csv_file.is_open()) {
            cerr << "Невозможно открыть файл CSV для записи.." << endl;
            return;
        }

        Flight* current_flight = head_flight;
        while (current_flight) {
            // Записываем данные рейса в CSV файл
            csv_file << current_flight->get_number_airplane() << ","
                    << current_flight->get_destination_airport() << ","
                    << current_flight->get_departure_time() << ","
                    << current_flight->get_arrival_time() << ","
                    << current_flight->get_total_number_of_seats() << ","
                    << current_flight->get_number_of_tickets_sold() << ","
                    << current_flight->get_free_number_of_seats() << "\n";

            // Переходим к следующему рейсу
            current_flight = current_flight->get_next();
        }

        // Закрываем файл
        csv_file.close();

        cout << "Рейсы успешно сохранены в файле flight.csv." << endl;
    }

    void load_flights_from_csv() {
        ifstream csvFile("/home/nerdermind/CLionProjects/airport/flights.csv");
        if (!csvFile.is_open()) {
            cerr << "Unable to open CSV file for reading." << endl;
            return;
        }

        // Пропускаем заголовок CSV файла
        string line;

        while (getline(csvFile, line)) {
            istringstream ss(line);
            string token;

            Flight* new_flight = new Flight(); // Создаем новый объект рейса

            getline(ss, token, ',');
            new_flight->set_number_airplane(token);

            getline(ss, token, ',');
            new_flight->set_destination_airport(token);

            getline(ss, token, ',');
            new_flight->set_departure_time(token);

            getline(ss, token, ',');
            new_flight->set_arrival_time(token);

            getline(ss, token, ',');
            new_flight->set_total_number_of_seats(stoi(token));

            getline(ss, token, ',');
            new_flight->set_number_of_tickets_sold(stoi(token));

            new_flight->set_next(head_flight);
            if (head_flight) {
                head_flight->set_prev(new_flight);
            }
            head_flight = new_flight;

        }

        csvFile.close();

        cout << "Рейсы успешно загружены из файла flights.csv." << endl;
    }


private:
    Flight* head_flight;
};


#endif //AIRPORT_H
