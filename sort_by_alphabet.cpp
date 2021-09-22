#include "sort_by_alphabet.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//-----------------------------------------------------------------------------

void Sort_Txt(text_t* text)
{
    Num_Str(text);

    str_t* str = (str_t*)calloc(text->n_str, sizeof(str_t));
    assert(str);

    printf("Successful str calloc\n\n");

    for(int str_index = 0, text_pos = 0; str_index < text->n_str && text_pos < text->len; str_index++)
        str[str_index].len = Str_Length(text, &text_pos);

    for(int str_index = 0, text_pos = 0; str_index < text->n_str && text_pos < text->len; str_index++)
        str[str_index].value = Str_Ctor(text, &text_pos, str_index, str);

    printf("Successful str->value Ctor\n\n");

    Str_Bubble_Sort(str, text);
    printf("Successful Str_Bubble_Sort\n\n");

    text->value = (char*)realloc(text->value, 2 * text->len + 3);
    assert(text->value);

    printf("Successful text realloc\n\n");

    Str_Rebuild(text, str);
    printf("Successful str rebuild\n\n");

    Str_Dtor(str);
    printf("Successful str->value Dtor\n\n");

    free(str);
    str = nullptr;
}

//-----------------------------------------------------------------------------

char* Load_txt(text_t* text)
{
    FILE *onegin = fopen("onegin2.txt", "rb");
    assert(onegin);

    fseek(onegin, 0, SEEK_END);

    text->len = ftell(onegin);

    printf("Num of symbols in text: %d\n\n", text->len);
    fseek(onegin, 0, SEEK_SET);

    text->value= (char*)calloc(text->len + 1, sizeof(char));
    assert(text->value);

    fread(text->value, sizeof(char), text->len, onegin);

    fclose(onegin);

    printf("\n\%s\n\n", text->value);

    return text->value;
}

void Upload_txt(text_t* text)
{
    assert(text);
    printf("\n\n\n\n\%s", text->value);

    FILE *onegin = fopen("onegin.txt", "wb");
    assert(onegin);

    int check = fwrite(text->value, sizeof(char), 2 * text->len + 1, onegin);
    assert(check);

    fclose(onegin);

    free(text->value);
    text->value = nullptr;

    printf("\n\nProgram completed successfully\n\n");
}

void Num_Str(text_t* text)
{
    text->n_str = 0;

    for(int txt_pos = 0; txt_pos < text->len; txt_pos ++)
    {
        if(text->value[txt_pos] == '\n')
            text->n_str++;
    }
    text->n_str++;
}

//-----------------------------------------------------------------------------

int Str_Length(text_t* text, int* text_pos)
{

    int str_pos = 0;

    while(text->value[*text_pos] != '\n' && *text_pos < text->len - 1)
    {

        (*text_pos) ++;
        str_pos ++;
    }

    str_pos++;

    (*text_pos)++;

    return str_pos;
}

char* Str_Ctor(text_t* text, int* txt_pos, int str_index, str_t* str)
{
    while(text->value[*txt_pos] > 'z' || text->value[*txt_pos] < 'A')
    {
        (*txt_pos)++;
        (str[str_index].len)--;
    }

    str[str_index].value = (char*)calloc(str[str_index].len, sizeof(char));
    assert(str[str_index].value);

    for(int str_pos = 0; str_pos < str[str_index].len && *txt_pos < text->len; str_pos ++, (*txt_pos)++)
        str[str_index].value[str_pos] = text->value[(*txt_pos)];

    return str[str_index].value;
}

void Str_Dtor(str_t* str)
{
    for(int str_index = 0; str_index <= str->len; str_index++)
    {
        free(str->value);
        str->value = nullptr;
    }
}

void Str_Rebuild(text_t* text, str_t* str)
{
    text->value[text->len] = '\n';
    for(int str_index = 0, ptr = text->len + 1; str_index < text->n_str; str_index++)
    {
        for(int str_pos = 0; str_pos < str[str_index].len; str_pos++)
        {
            text->value[ptr] = str[str_index].value[str_pos];
            ptr++;
        }
    }
}

//-----------------------------------------------------------------------------

void Str_Bubble_Sort(str_t* str, text_t* text)
{
    for(int n_pass = text->n_str; n_pass >= 0; n_pass--)
    {
        for(int str_index = 0; str_index < n_pass - 1; str_index++)
        {
            Str_RSwap(str, str_index);

        }
    }
}

void Str_LSwap(str_t* str, int str_index)
{
    int ptr1 = 0;
    int ptr2 = 0;

    Letter_LSearch(str, &ptr1, str_index);
    Letter_LSearch(str, &ptr2, str_index + 1);

    if(Str_LComp(str, &ptr1, &ptr2, str_index))
        Str_Swapper(str, str_index);
}

void Str_RSwap(str_t* str, int str_index)
{
    int ptr1 = str[str_index].len - 1;
    int ptr2 = str[str_index + 1].len - 1;

    Letter_RSearch(str, &ptr1, str_index);
    Letter_RSearch(str, &ptr2, str_index + 1);

    if(Str_RComp(str, &ptr1, &ptr2, str_index))
        Str_Swapper(str, str_index);
}

void Str_Swapper(str_t* str, int str_index)
{
    char* str_temp = str[str_index + 1].value;
    str[str_index + 1].value = str[str_index].value;
    str[str_index].value = str_temp;

    int n_temp = str[str_index + 1].len;
    str[str_index + 1].len = str[str_index].len;
    str[str_index].len  = n_temp;
}

//-----------------------------------------------------------------------------

void Letter_LSearch(str_t* str, int* ptr, int str_index)
{
    while(*ptr < str[str_index].len - 1)
    {
        if(str[str_index].value[*ptr] <= 'z' && str[str_index].value[*ptr] >= 'A')
            break;

        if(str[str_index].value[*ptr] > 'z' || str[str_index].value[*ptr] < 'A')
            (*ptr)++;

        if(*ptr == str[str_index].len - 1)
        {
            *ptr = -1;
            break;
        }
    }
}

void Letter_RSearch(str_t* str, int* ptr, int str_index)
{
    while(*ptr >= 0)
    {
        if(str[str_index].value[*ptr] <= 'z' && str[str_index].value[*ptr] >= 'A')
            break;

        if(str[str_index].value[*ptr] > 'z' || str[str_index].value[*ptr] < 'A')
            (*ptr)--;
    }
}

bool Str_LComp(str_t* str, int* ptr1, int* ptr2, int str_index)
{
    if(*ptr1 == -1)
        return 1;

    if(*ptr2 == -1)
        return 0;

    while(*ptr1 < str[str_index].len && *ptr2 < str[str_index + 1].len)
    {
        if(str[str_index].value[*ptr1] > str[str_index + 1].value[*ptr2])
            return 1;

        if(str[str_index].value[*ptr1] < str[str_index + 1].value[*ptr2])
            return 0;

        (*ptr1)++;
        (*ptr2)++;
    }
    return 0;
}

bool Str_RComp(str_t* str, int* ptr1, int* ptr2, int str_index)
{
    if(*ptr1 == -1)
        return 1;

    if(*ptr2 == -1)
        return 0;

    while(*ptr1 > 0 && *ptr2 > 0)
    {
        if(str[str_index].value[*ptr1] > str[str_index + 1].value[*ptr2])
            return 1;

        if(str[str_index].value[*ptr1] < str[str_index + 1].value[*ptr2])
            return 0;

        (*ptr1)--;
        (*ptr2)--;
    }
    return 0;
}
