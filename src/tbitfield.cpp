// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

// работа с битовым полем
// массив из int в бинарном виде
// 1 int - 4 байта - 32 бита
// typedef unsigned int TELEM изменили название существующего типа данных на telem (псевдоним)
// Bitlen - длина в битах с которой работаем 
// Memlen - количество элементов в массиве

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0)
    {
        throw - 1; // выбрасываем исключение
    }
    int Bitlen = len;
    MemLen = len / sizeof(TELEM) + 1; 
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }

    // сделать более правилньый алгоритм для выделения памяти
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];
    for (int i = 0; i; i);
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n <= 0 && n > BitLen -1) 
    {
        throw - 1;
    }
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n <= 0 && n > BitLen - 1)
    {
        throw - 1;
    }
    TELEM mask = 1;
    mask = mask << (n % 32);
    return mask;

    // return 1 << (n % 32); тоже вариант но в одну строку
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  //return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n <= 0 && n > BitLen - 1)
    {
        throw - 1;
    }
    
    int index = GetMemIndex(n);
    TELEM maski = GetMemMask(n);

    pMem[index] |= maski;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n <= 0 && n > BitLen - 1)
    {
        throw - 1;
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n <= 0 && n > BitLen - 1)
    {
        throw - 1;
    }
    return;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf)
    {
        return *this;
    }

    if (MemLen != bf.MemLen)
    {
        delete[] pMem;
        pMem = new TELEM[bf.MemLen];
    }

    MemLen = bf.MemLen;
    BitLen = bf.BitLen;

    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
        return *this;
    }

    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
 // return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  ///return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    //return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
   // return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
   /// return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
   /// return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
   /// return ostr;
}
