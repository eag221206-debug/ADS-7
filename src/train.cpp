// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCar(bool light) {
  Car* newCar = new Car;
  newCar->light = light;
  
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

int Train::getLength() {
  if (first == nullptr) {
    return 0;
  }

  first->light = true;
  Car* current = first;
  int steps = 0;
  countOp = 0;

  while (true) {
    current = current->next;
    countOp++;
    steps++;

    if (current->light) {
      current->light = false;
      
      for (int i = 0; i < steps; i++) {
        current = current->prev;
        countOp++;
      }

      if (!first->light) {
        return steps;
      }

      for (int i = 0; i < steps; i++) {
        current = current->next;
        countOp++;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
