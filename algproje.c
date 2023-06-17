#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

const char matrix_bigram_strings[10][3] = {"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_string[10][4] = {"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8] = {"english", "german"};

const float frequency_eng[20] = {2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01,
                                 1.81, 0.73, 0.72, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01};

const float frequency_germ[20] = {0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98,
                                  0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62};

void filter_str(char str[]);
void calculated_frequencies_bi(char str[], float *calculated_frequencies1);
void calculated_frequencies_tri(char str[], float *calculated_frequencies2);
void calculated_distances(float *calculated_frequencies);
void detect_lang(float *calculated_frequencies);

int main()
{
    char str[10000];

    printf("Please enter a text: \n");
    fgets(str, sizeof(str), stdin);

    filter_str(str);

    float calculated_frequencies1[10] = {0.0};
    float calculated_frequencies2[10] = {0.0};

    calculated_frequencies_bi(str, calculated_frequencies1);
    calculated_frequencies_tri(str, calculated_frequencies2);

    int calculated_frequencies_len = sizeof(calculated_frequencies1) / sizeof(calculated_frequencies1[0]) +
                                     sizeof(calculated_frequencies2) / sizeof(calculated_frequencies2[0]);

    float *calculated_frequencies = malloc(calculated_frequencies_len * sizeof(float));

    memcpy(calculated_frequencies, calculated_frequencies1, sizeof(calculated_frequencies1));
    memcpy(calculated_frequencies + sizeof(calculated_frequencies1) / sizeof(calculated_frequencies1[0]),
           calculated_frequencies2, sizeof(calculated_frequencies2));

    calculated_distances(calculated_frequencies);
    detect_lang(calculated_frequencies);

    free(calculated_frequencies);

    return 0;
}

void filter_str(char str[])
{
    int count = 0;
    char newStr[10000] = "";

    for (int i = 0; i < strlen(str); i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            newStr[count] = tolower(str[i]);
            count++;
        }
    }

    strcpy(str, newStr);
}

void calculated_frequencies_bi(char str[], float *calculated_frequencies1)
{
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        char bigram[3];
        strncpy(bigram, str + i, 2);
        bigram[2] = '\0';

        for (int j = 0; j < 10; j++)
        {
            if (strcmp(bigram, matrix_bigram_strings[j]) == 0)
            {
                calculated_frequencies1[j]++;
                break;
            }
        }
    }
}

void calculated_frequencies_tri(char str[], float *calculated_frequencies2)
{
    for (int i = 0; i < strlen(str) - 2; i++)
    {
        char trigram[4];
        strncpy(trigram, str + i, 3);
        trigram[3] = '\0';

        for (int j = 0; j < 10; j++)
        {
            if (strcmp(trigram, matrix_trigram_string[j]) == 0)
            {
                calculated_frequencies2[j]++;
                break;
            }
        }
    }
}

void calculated_distances(float *calculated_frequencies)
{
    float distance_eng = 0.0;
    float distance_germ = 0.0;

    for (int i = 0; i < 10; i++)
    {
        distance_eng += pow(frequency_eng[i] - calculated_frequencies[i], 2);
        distance_germ += pow(frequency_germ[i] - calculated_frequencies[i], 2);
    }

    distance_eng = sqrt(distance_eng);
    distance_germ = sqrt(distance_germ);

    printf("Distance to English: %f\n", distance_eng);
    printf("Distance to German: %f\n", distance_germ);
}

void detect_lang(float *calculated_frequencies)
{
    if (calculated_frequencies[8] > calculated_frequencies[9])
    {
        printf("Language: German\n");
    }
    else
    {
        printf("Language: English\n");
    }
}
