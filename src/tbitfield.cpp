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
    BitLen = len;
    int tmp = sizeof(TELEM) * 8;
    MemLen = (BitLen + (tmp - 1)) / tmp;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n > BitLen - 1)
    {
        throw - 1;
    }
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n > BitLen - 1)
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
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

    int index = GetMemIndex(n);
    TELEM maski = GetMemMask(n);

    pMem[index] |= maski;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int index = GetMemIndex(n);
    TELEM maski = GetMemMask(n);

    pMem[index] &= ~maski;

}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int index = GetMemIndex(n);
    TELEM maski = GetMemMask(n);

    return ((pMem[index] & maski) == maski);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
    {
        return *this;
    }

    if (MemLen != bf.MemLen)
    {
        delete[] pMem;
        pMem = new TELEM[bf.MemLen];
        MemLen = bf.MemLen;
    }

    BitLen = bf.BitLen;

    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->BitLen != bf.BitLen)
    {
        return 0;
    }

    for (int i = 0; i < MemLen - 1; i++)
    {
        if (this->pMem[i] != bf.pMem[i])
        {
            return 0;
        }
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
    {
        if (this->GetBit(i) != bf.GetBit(i))
        {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return (!(*this == bf));
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int reslen = this->BitLen;
    if (reslen < bf.BitLen) {
        reslen = bf.BitLen;
    }
    int minlen = bf.MemLen;
    int maxlen = bf.MemLen;
    if (this->MemLen < bf.MemLen) {
        minlen = this->MemLen;
    }
    if (this->MemLen > bf.MemLen) {
        maxlen = this->MemLen;
    }
    int i = 0;
    TBitField res(reslen);
    for (i = 0; i < minlen; i++)
    {
        res.pMem[i] = (this->pMem[i] | bf.pMem[i]);
    }
    if (maxlen == this->MemLen) {
        while (i < maxlen) {
            res.pMem[i] = pMem[i];
            i++;
        }
    }
    else {
        while (i < maxlen) {
            res.pMem[i] = bf.pMem[i];
            i++;
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int reslen = bf.BitLen;
    if (this->BitLen > reslen) {
        reslen = this->BitLen;
    }
    int minlen = bf.MemLen;
    if (this->MemLen < bf.MemLen) {
        minlen = this->MemLen;
    }
    TBitField res(reslen);
    for (int i = 0; i < minlen; i++)
    {
        res.pMem[i] = (this->pMem[i] & bf.pMem[i]);
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res = TBitField(BitLen);
    for (int i = 0; i < MemLen - 1; i++)
    {
        res.pMem[i] = ~pMem[i];
    } 

    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
    {
        if (!GetBit(i))
        {
            res.SetBit(i);
        }
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> bit;

        if (bit)
        {
            bf.SetBit(i);
        }
        else
        {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
   for (int i = 0; i < bf.BitLen; i++)
    {
       if (bf.GetBit(i) == 0)
       {
           ostr << 0;
       }
       else
       {
           ostr << 1;
       }
    }
    return ostr;
}
