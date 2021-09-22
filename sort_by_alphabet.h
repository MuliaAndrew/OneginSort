#ifndef SORT_BY_ALPHABET_H
#define SORT_BY_ALPHABET_H

#include <stdio.h>

struct str_t
{
    int len;
    char* value;
};

struct text_t
{
    int len;
    int n_str;
    char* value;
};

//-----------------------------------------------------------------------------

void Sort_Txt(text_t* txt);

//-----------------------------------------------------------------------------

char* Load_txt(text_t* txt);

void Upload_txt(text_t* txt);

void Num_Str(text_t* txt);

void Get_Len(text_t* txt, FILE* onegin);

//-----------------------------------------------------------------------------

int Str_Length(text_t* txt, int* txt_pos);

char* Str_Ctor(text_t* text, int* txt_pos, int str_index, str_t* str);

void Str_Dtor(str_t* str);

void Str_Rebuild(text_t* text, str_t* str);

//-----------------------------------------------------------------------------

void Str_Bubble_Sort(str_t* str, text_t* text);

void Str_LSwap(str_t* str, int str_index);

void Str_RSwap(str_t* str, int str_index);

void Str_Swapper(str_t* str, int str_index);

bool Str_LComp(str_t* str, int* ptr1, int* ptr2, int str_index);

bool Str_RComp(str_t* str, int* ptr1, int* ptr2, int str_index);

void Letter_LSearch(str_t* str, int* ptr, int str_index);

void Letter_RSearch(str_t* str, int* ptr, int str_index);


#endif // SORT_BY_ALPHABET_H
