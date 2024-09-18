// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int fieldElement;
const int SEGMENT_LENGTH_IN_BITS = sizeof(fieldElement) * 8;

class TBitField {
private:
    int bitLength; // длина битового поля - макс. к-во битов
    fieldElement* memory; // память для представления битового поля
    int memoryLength; // к-во эл-тов Мем для представления бит.поля

    // методы реализации
    int GetMemIndex(const int) const; // индекс в memory для бита n (#О2)
    fieldElement GetMemMask(const int) const; // битовая маска для бита n       (#О3)
public:
    TBitField(int);
    TBitField(const TBitField&);
    ~TBitField();

    // доступ к битам
    int GetLength(void) const; // получить длину (к-во битов) (#О)
    void SetBit(const int); // установить бит (#О4)
    void ClrBit(const int); // очистить бит (#П2)
    int GetBit(const int) const; // получить значение бита (#Л1)

    // битовые операции
    int operator==(const TBitField&) const; // сравнение
    int operator!=(const TBitField&) const; // сравнение
    TBitField& operator=(const TBitField&); // присваивание
    TBitField operator|(const TBitField&); // операция "или"
    TBitField operator&(const TBitField&); // операция "и"
    TBitField operator~(void); // отрицание

    friend istream& operator>>(istream&, TBitField&); // (#О7)
    friend ostream& operator<<(ostream&, const TBitField&); // (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до bitLength
//   массив pМем рассматривается как последовательность memoryLength элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif
