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
    // Проверка на пустой поезд или поезд из 1 вагона
    if (!first || first->next == first) {
        return first ? 1 : 0;
    }

    Car* base = first;
    
    // Запоминаем измененное состояние базового вагона
    base->light = !base->light;
    bool expected_light = base->light; 

    for (int d = 1; ; ++d) {
        Car* probe = base;
        
        // 1. Идем вперед на d шагов
        for (int i = 0; i < d; ++i) {
            probe = probe->next;
            countOp++;
        }

        // 2. Инвертируем свет в вагоне на расстоянии d
        probe->light = !probe->light;

        // 3. Возвращаемся назад к стартовому вагону
        for (int i = 0; i < d; ++i) {
            probe = probe->prev;
            countOp++;
        }

        // ИСПРАВЛЕНИЕ: Проверяем, не изменился ли свет в базовом вагоне.
        // Если изменился, значит вагон на расстоянии d — это и есть наш базовый вагон.
        if (base->light != expected_light) {
             return d;
        }

        // 4. Если это не базовый вагон, идем обратно и отменяем инверсию света
        for (int i = 0; i < d; ++i) {
            probe = probe->next;
            countOp++;
        }
        probe->light = !probe->light;

        // 5. Возвращаемся на старт для следующей итерации (d+1)
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
