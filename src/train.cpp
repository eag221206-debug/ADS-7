#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) {
        return;
    }
    
    if (first->next == first) {
        delete first;
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
    Car* new_car = new Car{light, nullptr, nullptr};
    if (!first) {
        first = new_car;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = new_car;
        new_car->prev = last;
        new_car->next = first;
        first->prev = new_car;
    }
}

int Train::getLength() {
    countOp = 0;
    if (!first) {
        return 0;
    }
    if (first->next == first) {
        return 1;
    }

    Car* base_pos = first;
    Car* current_pos = first;
    base_pos->light = true;

    int steps_forward = 0;

    while (true) {
        current_pos = current_pos->next;
        countOp++;
        steps_forward++;

        if (current_pos->light) {
            current_pos->light = false;

            for (int i = 0; i < steps_forward; ++i) {
                current_pos = current_pos->prev;
                countOp++;
            }

            if (!base_pos->light) {
                return steps_forward;
            } else {
                for (int i = 0; i < steps_forward; ++i) {
                    current_pos = current_pos->next;
                    countOp++;
                }
            }
        }
    }
}

int Train::getOpCount() const {
    return countOp;
}
