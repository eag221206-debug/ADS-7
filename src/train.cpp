// Copyright 2022 NNTU-CS

#include <stdexcept>
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (first == nullptr) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    countOp = 0;
    if (first == nullptr) {
        return 0;
    }
    if (first->next == first) {
        return 1;
    }

    Car* home = first;
    home->light = true;

    int distance = 1;
    while (true) {
        // Идем вперед на `distance` шагов от дома
        Car* probe = home;
        for (int i = 0; i < distance; ++i) {
            probe = probe->next;
            countOp++;
        }

        if (probe->light) {
            probe->light = false; 

            Car* return_trip_car = probe;
            for (int i = 0; i < distance; ++i) {
                return_trip_car = return_trip_car->prev;
                countOp++;
            }

            if (!return_trip_car->light) {
                probe->light = true;
                return distance;
            } else {
                probe->light = true;
            }
        }
        distance++;
    }
}
