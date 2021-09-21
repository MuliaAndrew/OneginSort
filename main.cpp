#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "TxLib.h"
#include "sort_by_alphabet.h"

//-----------------------------------------------------------------------------

int main()
{
    setlocale(LC_ALL ,"rus");

    text_t text;
    text.value = Load_txt(&text);

    Sort_Txt(&text);

    Upload_txt(&text);

    return 0;
}
