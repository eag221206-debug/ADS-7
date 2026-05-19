// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "train.h"

int main() {
  Train train;
  int count = 60;

  while (count--)
    train.addCar(false);

  std::cout << "Длина поезда (шаблон): " << train.getLength() << std::endl;
  std::cout << "Число операций (шаблон): " << train.getOpCount() << std::endl;
  std::cout << "------------------------------------------\n";


  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  std::ofstream outFile("experiment_results.csv");
  
  if (!outFile.is_open()) {
      std::cerr << "Не удалось открыть файл для записи результатов!" << std::endl;
      return 1;
  }


  outFile << "N,AllOff,AllOn,Random\n";
  std::cout << "Проведение вычислительного эксперимента..." << std::endl;

  for (int n = 10; n <= 1000; n += 10) {
      // 1. Все лампочки выключены (лучший случай)
      Train trainOff;
      for (int i = 0; i < n; i++) trainOff.addCar(false);
      trainOff.getLength();
      int opsOff = trainOff.getOpCount();


      Train trainOn;
      for (int i = 0; i < n; i++) trainOn.addCar(true);
      trainOn.getLength();
      int opsOn = trainOn.getOpCount();


      Train trainRand;
      for (int i = 0; i < n; i++) trainRand.addCar(std::rand() % 2);
      trainRand.getLength();
      int opsRand = trainRand.getOpCount();


      outFile << n << "," << opsOff << "," << opsOn << "," << opsRand << "\n";
  }

  outFile.close();
  std::cout << "Эксперимент завершен. Данные сохранены в 'experiment_results.csv'" << std::endl;
  
  return 0;
}
