// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int length)
{
    if (length < 0) {
        throw invalid_argument("Negative length is not allowed.");
    }

    bitLength = length;
    memoryLength = (bitLength + (SEGMENT_LENGTH_IN_BITS - 1)) / (SEGMENT_LENGTH_IN_BITS);

    memory = new fieldElement[memoryLength];
    memset(memory, 0, memoryLength * sizeof(fieldElement));
}

TBitField::TBitField(const TBitField& given)
{
    bitLength = given.bitLength;
    memoryLength = given.memoryLength;
    memory = new fieldElement[memoryLength];

    memcpy(memory, given.memory, memoryLength * sizeof(fieldElement));
}

TBitField::~TBitField()
{
    delete[] memory;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= bitLength) {
        throw out_of_range("Bit index out of range.");
    }

    return n / SEGMENT_LENGTH_IN_BITS;
}

fieldElement TBitField::GetMemMask(const int i) const // битовая маска для бита n
{
    if (i < 0 || i >= bitLength) {
        throw out_of_range("Bit index out of range.");
    }

    return 1 << i % SEGMENT_LENGTH_IN_BITS; // оператор сдвига слево
}

// доступ к битам битового поля

int TBitField::GetLength(void) const
{
    return bitLength;
}

void TBitField::SetBit(const int i)
{
    if (i < 0 || i >= bitLength) {
        throw out_of_range("Bit index out of range.");
    }

    memory[GetMemIndex(i)] |= GetMemMask(i);
}

void TBitField::ClrBit(const int i) // очистить бит
{
    if (i < 0 || i >= bitLength) {
        throw out_of_range("Bit index out of range.");
    }

    memory[GetMemIndex(i)] &= ~GetMemMask(i);
}

int TBitField::GetBit(const int i) const // получить значение бита
{
    if (i < 0 || i >= bitLength) {
        throw out_of_range("Bit index out of range.");
    }

    return (memory[GetMemIndex(i)] & GetMemMask(i)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& given)
{
    if (this != &given) {
        delete[] memory;

        bitLength = given.bitLength;
        memoryLength = given.memoryLength;
        memory = new fieldElement[memoryLength];

        memcpy(memory, given.memory, memoryLength * sizeof(fieldElement));
    }

    return *this;
}

int TBitField::operator==(const TBitField& given) const
{
    if (bitLength != given.bitLength) {
        return 0;
    }

    for (int i = 0; i < memoryLength; i++) {
        if (memory[i] != given.memory[i]) {
            return 0;
        }
    }

    return 1;
}

int TBitField::operator!=(const TBitField& given) const
{
    return !(*this == given);
}

TBitField TBitField::operator|(const TBitField& given)
{
    const int length = bitLength > given.bitLength ? bitLength : given.bitLength;
    TBitField result(length);

    for (int i = 0; i < memoryLength; i++) {
        result.memory[i] = memory[i] | given.memory[i];
    }

    return result;
}

TBitField TBitField::operator&(const TBitField& given)
{
    int length = bitLength > given.bitLength ? bitLength : given.bitLength;
    TBitField result(length);

    for (int i = 0; i < result.memoryLength; i++) {
        result.memory[i] = memory[i] & given.memory[i];
    }

    return result;
}

TBitField TBitField::operator~(void)
{
    TBitField result(bitLength);

    for (int i = 0; i < memoryLength; i++) {
        result.memory[i] = ~memory[i];
    }

    int lastElementMask = (1 << (bitLength % SEGMENT_LENGTH_IN_BITS)) - 1;
    if (bitLength % SEGMENT_LENGTH_IN_BITS != 0) {
        result.memory[memoryLength - 1] &= lastElementMask;
    }

    return result;
}

istream& operator>>(istream& in, TBitField& given)
{
    for (int i = 0; i < given.bitLength; i++) {
        int bit;
        in >> bit;

        if (bit) {
            given.SetBit(i);
        } else {
            given.ClrBit(i);
        }
    }

    return in;
}

ostream& operator<<(ostream& out, const TBitField& given)
{
    for (int i = 0; i < given.bitLength; i++) {
        out << given.GetBit(i);
    }

    return out;
}
