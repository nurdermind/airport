//
// Created by nerdermind on 28.12.23.
//

#ifndef FLIGHT_H
#define FLIGHT_H

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

// Класс для хранения данных о рейсе
class Flight {
public:
    Flight() : total_number_of_seats(0),
               number_of_tickets_sold(0),
               free_number_of_seats(0),
               next(nullptr),
               prev(nullptr) {
    }


    Flight* copy() {
        Flight* new_flight = new Flight();

        new_flight->number_airplane = this->number_airplane;
        new_flight->destination_airport = this->destination_airport;
        new_flight->departure_time = this->departure_time;
        new_flight->arrival_time = this->arrival_time;
        new_flight->total_number_of_seats = this->total_number_of_seats;
        new_flight->number_of_tickets_sold = this->number_of_tickets_sold;
        new_flight->free_number_of_seats = this->free_number_of_seats;

        new_flight->next = nullptr;
        new_flight->prev = nullptr;

        return new_flight;
    }

    const std::string& get_number_airplane() {
        return number_airplane;
    }

    void set_number_airplane(const std::string& number) {
        number_airplane = number;
    }

    const std::string& get_destination_airport() {
        return destination_airport;
    }

    void set_destination_airport(const std::string& destination) {
        destination_airport = destination;
    }

    const std::string& get_departure_time() {
        return departure_time;
    }

    void set_departure_time(const std::string& new_departure_time) {
        if(!is_valid_time(new_departure_time)) {
            throw runtime_error("Неккоректный формат времени!");
        }
        departure_time = new_departure_time;
    }

    const std::string& get_arrival_time() {
        return arrival_time;
    }

    void set_arrival_time(const std::string& new_arrival_time) {
        if(!is_valid_time(new_arrival_time)) {
            throw runtime_error("Неккоректный формат времени!");
        }
        arrival_time = new_arrival_time;
    }

    int get_total_number_of_seats() const {
        return total_number_of_seats;
    }

    void set_total_number_of_seats(int total_seats) {
        if (total_seats < number_of_tickets_sold)
            throw runtime_error("Количество всех мест"
                " не может быть меньше купленных билетов");
        total_number_of_seats = total_seats;
        _recalc_free_number_of_seats();
    }

    int get_free_number_of_seats() const {
        return free_number_of_seats;
    }

    int get_number_of_tickets_sold() const {
        return number_of_tickets_sold;
    }

    void set_number_of_tickets_sold(int tickets_sold) {
        if (tickets_sold > total_number_of_seats) {
            throw runtime_error("Количество всех мест"
                " не может быть меньше купленных билетов!");
        }
        number_of_tickets_sold = tickets_sold;
        _recalc_free_number_of_seats();
    }

    Flight* get_next() const {
        return next;
    }

    void set_next(Flight* next_flight) {
        next = next_flight;
    }

    Flight* get_prev() const {
        return prev;
    }

    void set_prev(Flight* prev_flight) {
        prev = prev_flight;
    }

    void show_info() {
        cout << " |-------------------------------------------------------------" << endl;
        cout << " | Номер Самолета: " << number_airplane << endl; // Вывод Номера самолета
        cout << " | Аэропорт назначения: " << destination_airport << endl; // вывод Аэропорта назначения
        cout << " | Время вылета: " << departure_time << endl; // Вывод время вылета
        cout << " | Время прибытия: " << arrival_time << endl; // Вывод время прибытия
        cout << " | Общее число мест: " << total_number_of_seats << endl; //Вывод общего числа мест
        cout << " | Количество проданных билетов: " << number_of_tickets_sold << endl;
        //Вывод количества проданных билетов
        cout << " | Количество свободных мест: " << free_number_of_seats << endl;
        cout << " |------------------------------------------------------------- " << endl << endl;
    }


    bool is_valid_time(const std::string& time) {
        // Регулярное выражение для проверки формата времени (часы:минуты)
        std::regex timeRegex("([01]?[0-9]|2[0-3]):[0-5][0-9]");

        // Проверка соответствия строки формату времени
        return std::regex_match(time, timeRegex);
    }


private:
    std::string number_airplane; // Номер Самолета
    std::string destination_airport; // Аэропорт назначения
    std::string departure_time; // Время вылета
    std::string arrival_time; // Время прибытия
    int total_number_of_seats; // Общее число мест
    int number_of_tickets_sold; // Количество проданных билетов
    int free_number_of_seats; // Количество свободных мест
    Flight* next; // следующий
    Flight* prev; // предыдущий

    void _recalc_free_number_of_seats() {
        free_number_of_seats = total_number_of_seats - number_of_tickets_sold;
    }

};


#endif //FLIGHT_H
