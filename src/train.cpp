// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) {
        return;
    }
    Car* current = first->next;
    while (current != first) {
        Car* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
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

int Train::getLength() {
    countOp = 0;
    if (!first || first->next == first) {
        return first ? 1 : 0;
    }

    Car* base = first;
    base->light = !base->light;

    for (int d = 1; ; ++d) {
        Car* probe = base;
        for (int i = 0; i < d; ++i) {
            probe = probe->next;
            countOp++;
        }

        probe->light = !probe->light;

        for (int i = 0; i < d; ++i) {
            probe = probe->prev;
            countOp++;
        }

        if (base->light != probe->light) {
             return d;
        }

        for (int i = 0; i < d; ++i) {
            probe = probe->next;
            countOp++;
        }
        probe->light = !probe->light;

        for (int i = 0; i < d; ++i) {
            probe = probe->prev;
            countOp++;
        }
    }
    return -1;
}

int Train::getOpCount() {
    return countOp;
}
