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
    
    if (!first->light) {
        int len = 1;
        Car* current = first->next;
        countOp++;
        while (current != first) {
            len++;
            current = current->next;
            countOp++;
        }
        return len;
    }
    
    first->light = false;
    int len = 1;
    Car* current = first->next;
    countOp++;
    
    while (current->light) {
        current->light = false;
        len++;
        current = current->next;
        countOp++;
    }
    
    if (current == first) {
        return len;
    }
    
    current->light = false;
    Car* marker = current;
    int count = 1;
    current = current->next;
    countOp++;
    
    while (current != marker) {
        count++;
        if (current->light) {
            current->light = false;
        }
        current = current->next;
        countOp++;
    }
    
    return count;
}
