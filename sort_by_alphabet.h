//! @file
//! @brief The header file which consist of functions of loading and uploading files, sorting text.
//!        Works only with text_t type variables.
//!
//! @warning Works only with files which consist of standard ASCII symbols (their numbers need to be less then 128)
#ifndef SORT_BY_ALPHABET_H
#define SORT_BY_ALPHABET_H
#include <stdio.h>

//-----------------------------------------------------------------------------

//! @brief Magic numbers
const int SWAP       = 1;  //!< If Str_L_Comp() or Str_R_Comp() return it then Str_Swap() is called
const int NO_SWAP    = 0;  //!< If Str_L_Comp() or Str_R_Comp() return it then Str_Swap() is not called
const int NO_LETTERS = -1; //!< Possible value of ptr which point on the first letter in string in case of their absence

//! @brief Describe strings. Consists of its value and length
struct str_t
{
    int len     = 0;       //!< The length of string
    char* value = nullptr; //!< String content
};

//! @brief Describe file buffer, where the contents of the file are copied
struct text_t
{
    int len     = 0;       //!< The length of text buffer
    int n_str   = 0;       //!< Number of string in text
    char* value = nullptr; //!< The buffer content
};

//-----------------------------------------------------------------------------

//! @brief Sorting of text
//!
//! @param text [in, out] Variable type of text_t (contains the information about length, number of strings and their content text in .txt file)
//!
//! @return Nothing return
//!
//! @warning It is used only after Load_Txt() called with param type of text_t
//!
//! This function sorts strings in text
void Sort_Txt(text_t* txt);

//-----------------------------------------------------------------------------

//! @brief Loading the text from file.txt into
//!
//! @param text [in, out] Variable type of text_t (contains the information about length, number of strings and their content text in .txt file)
//!
//! @return Nothing return
//!
//! @warning The name of file inputs to function fopen() in implementation of this function
void Load_Txt(text_t* txt);

//! @brief Uploading buffer content to chosen file
//!
//! @param text [in, out] Variable type of text_t (contains the information about length, number of strings and their content text in .txt file)
//!
//! @return Nothing return
//!
//! @warning The name of file inputs to function fopen() in implementation of this function
void Upload_Txt(text_t* txt);

//! @brief Counts number of strings in buffer and assigns this number to txt.len
//!
//! @param text [in, out] Variable type of text_t (contains the information about length, number of strings and their content text in .txt file)
//!
//! @return Nothing return
//!
//! Counts the number of '\n' symbols and assigns this number + 1 to txt.len
void Num_Str(text_t* txt);

//! @brief Counts number of symbols in file (type of int)
//!
//! @param txt [in] Variable type of FILE*
//!
//! @return Number of symbols
int Get_Len(FILE* txt);

//-----------------------------------------------------------------------------

//! @brief Counts length of every string in txt file
//!
//! @param txt [in] Variable type of text_t. Text buffer
//! @param txt_pos [in] Variable type of int*. The pointer to the beginning of string in buffer
//!
//! @return number of symbols in string
//!
//! @warning This function is only used by others functions from this program.
//!          it is not recommended to use it separately
int Str_Length(text_t* txt, int* txt_pos);

//! @brief Constructor of array of str_t strings
//!
//! @param text [in] Variable type of text_t. Text buffer
//! @param txt_pos [in, out] Variable type of int. The symbol index in text->value
//! @param str_index [in, out] Variable of int. The string index in text
//! @param str[in, out] Variable of str_t. Description below
//!
//! @return pointer on the beginning of str->value
//!
//! @warning This function is only used by others functions from this program.
//!          it is not recommended to use it separately
//!
//! This function is used in the second loop of Sort_Txt() and its divide the text buffer on created
//! array of pointers on str_t variables which are contain one string and its length from the text buffer
char* Str_Ctor(text_t* text, int* txt_pos, int str_index, str_t* str);

//! @brief Desctructor of array of str_t strings
//!
//! @param str[in] Variable type of str_t*. The array of strings type of str_t
//!
//! @return Nothing return
//!
//! @warning This function is only used by others functions from this program.
//!          it is not recommended to use it separately
//!
//! This function nullifies and destroys the array of strings type of str_t
void Str_Dtor(str_t* str);

//! @brief Writes sorted strings back to buffer
//!
//! @param text [in, out] Variable type of text_t. Text buffer
//! @param str [in] Variable type of str_t*. The array of strings type of str_t
//!
//! @return Nothing return
//!
//! @warning This function is only used by others functions from this program.
//!          it is not recommended to use it separately
void Str_Rebuild(text_t* text, str_t* str);

//! @brief Consists of sorting algorithm (uses bubble sorting algorithm)
//!
//! @param str [in, out] The array of strings type of str_t.
//! @param text [in] Variable type of text_t. Text buffer
//!
//! @return Nothing return
//!
//! @warning This function is only used by others functions from this program.
//!          it is not recommended to use it separately
void Str_Bubble_Sort(str_t* str, text_t* text);

//-----------------------------------------------------------------------------

//! @brief Consists of comparing algorithm
//!
//! @param str [in, out] The array of strings type of str_t
//! @param str_index [in] The index of string in its array
//!
//! @return Nothing return
//!
//! @warning This function is only used by sorting function from this program.
//!          it is not recommended to use it separately
//!
//! This function consists of comparator, function, which swaps 2 selected strings in their array if its necessary,
//! and 2 functions, which are looking for the first letter in string from its beginning
void Str_L_Sort(str_t* str, int str_index);

//! @brief Consists of comparing algorithm
//!
//! @param str [in, out] The array of strings type of str_t
//! @param str_index [in] The index of string in its array
//!
//! @return Nothing return
//!
//! @warning This function is only used by sorting function from this program.
//!          it is not recommended to use it separately
//!
//! This function consists of comparator, function, which swaps 2 selected strings in their array if its necessary,
//! and 2 functions, which are looking for the first letter in string from its end
void Str_R_Sort(str_t* str, int str_index);

//! @brief Swaps two consecutive strings in their array
//!
//! @param str [in, out] The array of strings type of str_t
//! @param str_index [in] The index of string in its array
//!
//! @return Nothing return
//!
//! @warning This function is only used by Str_R_Swap() and Str_L_Swap() functions from this program.
//!          it is not recommended to use it separately
void Str_Swap(str_t* str, int str_index);

//! @brief Comparator of two consecutive strings from their array
//!
//! @param str [in, out] array of strings type of str_t
//! @param ptr1 [in, out] Variable type of int. The index of the first letter in the first comparing string
//! @param ptr2 [in, out] Variable type of int. The index of the first letter in the second comparing string
//! @param str_index [in] Variable type of int. The index of string from array, which is comparing with next string from this array
//!
//! @return SWAP or NO_SWAP (Magic numbers)
//!
//! @warning This function is only used by Str_R_Swap() and Str_L_Swap() functions from this program.
//!          it is not recommended to use it separately
//!
//! This function is comparing two strings by letters starting at the **beginning** of these strings
//! If string doesnt consist of letters, it will be it will move to the end of the array after sorting
bool Str_L_Comp(str_t* str, int* ptr1, int* ptr2, int str_index);

//! @brief Comparator of two consecutive strings from their array
//!
//! @param str [in, out] array of strings type of str_t
//! @param ptr1 [in, out] Variable type of int. The index of the first letter in the first comparing string
//! @param ptr2 [in, out] Variable type of int. The index of the first letter in the second comparing string
//! @param str_index [in] Variable type of int. The index of string from array, which is comparing with next string from this array
//!
//! @return SWAP or NO_SWAP (Magic numbers)
//!
//! @warning This function is only used by Str_R_Swap() and Str_L_Swap() functions from this program.
//!          it is not recommended to use it separately
//!
//! This function is comparing two strings by letters starting at the end of these strings
//! If string doesnt consist of letters, it will be it will move to the **end** of the array after sorting
bool Str_R_Comp(str_t* str, int* ptr1, int* ptr2, int str_index);

//! @brief Searching for the first letter in string from its **beginning**
//!
//! @param str [in, out] array of strings type of str_t
//! @param str_index [in] Variable type of int. The index of string from array, which is comparing with next string from this array
//!
//! @return The index of first letter from string (type of int)
//!
//! @warning This function is only used by Str_R_Swap() and Str_L_Swap() functions from this program.
//!          it is not recommended to use it separately
int Letter_L_Search(str_t* str, int str_index);

//! @brief Searching for the first letter in string from its **end**
//!
//! @param str [in, out] array of strings type of str_t
//! @param str_index [in] Variable type of int. The index of string from array, which is comparing with next string from this array
//!
//! @return The index of first letter from string (type of int)
//!
//! @warning This function is only used by Str_R_Swap() and Str_L_Swap() functions from this program.
//!          it is not recommended to use it separately
int Letter_R_Search(str_t* str, int str_index);

#endif // SORT_BY_ALPHABET_H
