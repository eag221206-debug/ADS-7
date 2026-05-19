// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;
    newCar->next = nullptr;
    newCar->prev = nullptr;
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
    if (first == nullptr) return 0;
    countOp = 0;
    first->light = false;
    Car* current = first;
    int length = 1;
    while (true) {
        for (int i = 0; i < length; ++i) {
            current = current->next;
            countOp++;
        }
        if (!current->light) {
            for (int i = 0; i < length; ++i) {
                current = current->prev;
                countOp++;
            }
            if (!current->light && current == first) {
                return length;
            }
            length++;
            current = current->next;
            countOp++;
        } else {
            current->light = false;
            length++;
        }
    }
}
