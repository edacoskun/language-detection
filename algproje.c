#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

const char matrix_bigram_strings[10][3] = {"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_string[10][4] = {"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8] = {"english", "german"};

//Ingilizce dilinin frekans degerleri
const float frequency_eng[20] = {2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01,
                                 1.81, 0.73, 0.72, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Almanca dilinin frekans degerleri
const float frequency_germ[20] = {0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98,
                                  0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };

//float calculated_frequencies[20]; //dizi olusturma 10bi + 10tri
//float distances[2] = {0,0}; //{ingilizce ile fark, almanca ile fark}

void filter_str(char str[]);
void calculated_frequencies_bi(char str[]);
void calculated_frequencies_tri(char str[]);
void calculated_distances();
void detect_lang();
void add();

int main()
{
    char str[10000]; //kullanici tarafindan girilen metni tutmak icin char turunde dizi olustururuz

    printf("Lutfen bir metin giriniz: \n");
    gets(str); //girilen diziyi alma

    //fonksiyonlari mainde cagiririz
    filter_str(str);
    calculated_frequencies_bi(str);
    calculated_frequencies_tri(str);
    calculated_distances();
    detect_lang();

    return 0;
}

//Kullanicidan alinan metindeki yabanci karakterleri temizleme
void filter_str(char str[])
{
    int count = 0;
    char newStr[10000]; //yabanci karakterler yerine atanan bosluklarla birlikte yeni diziyi bu diziye atayacagiz

    printf("\n************************************\n");

    //butun karakterleri tarayip yabanci karakterleri bosluk yapmak icin dongu kullaniriz
    //strlen(str) kullanarak dizi boyutunca yani butun karakterleri, i kontrol degiskeni gezecek
    for(int i = 0; i < strlen(str); i++)
    {
        //yabanci karakter olup olmadigini kontrol etme
        //kucuk harf-buyuk harf ve bosluk varsa if yapisina girer
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ')
        {
            newStr[i] += str[i]; //o karakter, metnin yeni haline aynen gecirilir
        }
        //buyuk-kucuk harf ve bosluk haricinde bir karakter girilmisse else yapisina girer
        else
        {
            str[i] = ' '; //bu yabanci karakteri bosluk yapar
            newStr[i] = str[i]; // bosluk karakterini yeni diziye atar
            count++; //ve diger karaktere gecer
        }
    }
    printf("\nMetnin yabanci karakterleden temizlenmis hali:\n %s\n", newStr);

    printf("\n************************************\n");
}

//metindeki bigramlarin frekansini hesaplama
void calculated_frequencies_bi(char str[])
{
    printf("\n************************************\n");
    printf("Metin taraniyor. Lutfen bekleyiniz...\n");
    printf("\n************************************\n");

    printf("\n************************************\n");
    printf("Bigramlarin metindeki frekanslari hesaplaniyor...\n");
    printf("\n************************************\n");

    printf("\n************************************\n");

    float frekans[10]; //metindeki bigram frekanslarini tutacak 10 elemanli bir float dizi olustururuz
    float calculated_frequencies1[10]; //frekanslari tek tek bu diziye aktaririz

    //metindeki karakterleri ve bigramlari gezecek ve karsilastiracak
    //for dongusu ile metindeki karakterleri tek tek gezecek
    for(int i = 0; i < strlen(str); ++i)
    {
        //ikinci for dongusu ile bigram dizisini gezecek
        for(int j = 0; j < strlen(matrix_bigram_strings); ++j)
        {
            //metindeki karakteri ve bigrami karsilastiracak ikisi ayni ise
            if(str[i] == matrix_bigram_strings[j])
            {
                frekans[j] += 1.0; //o bigramin frekansini bir artiracak
                printf("%s frekansi: %.2f\n", matrix_bigram_strings, frekans); //th: 2.00 gibi ekrana bigramlarin frekanslarini yazacak
                calculated_frequencies1[j] = frekans[j]; //frekans dizisini yeni diziye aktaririz
            }
            //bigram bulunamiyorsa
            else
            {
                continue;
            }
        }
    }
}

//metindeki trigramlarin frekansini hesaplama
void calculated_frequencies_tri(char str[])
{
    printf("\n************************************\n");
    printf("Metin taraniyor. Lutfen bekleyiniz...\n");
    printf("\n************************************\n");

    printf("\n************************************\n");
    printf("Trigramlarin metindeki frekanslari hesaplaniyor...\n");
    printf("\n************************************\n");

    printf("\n************************************\n");

    float frekans[10];
    float calculated_frequencies2[10];

    //ilk for dongusu ile metindeki karakterleri gezecek
    for(int i = 0; i <= strlen(str); ++i)
    {
        //ikinci for dongusu ile trigram dizisindeki elemanlari gezecek
        for(int j = 0; i <= strlen(matrix_trigram_string) ; ++j)
        {
            //karakter ve trigram ayni ise
            if(str[i] == matrix_trigram_string[j])
            {
                frekans[j] += 1.0; //frekansi artiracak
                printf("%s frekansi: %.2f\n", matrix_trigram_string, frekans);
                calculated_frequencies2[j] = frekans[j]; //frekans degerlerini calculated_frequencies2 dizisine aktaracak
            }
            else
                continue;
        }
    }
}

//iki diziyi, calculated_frequencies dizisinde birlestirme
void add()
{
    calculated_frequencies_bi(char str[]); //bu fonksiyonu cagirarak calculted_frequencies1 dizisini alma
    calculated_frequencies_tri(char str[]); //fonksiyonu cagirarak calculted_frequencies2 dizisini alma

    //calculated_frequencies dizi icin 20 elemanlik yer tahsis edilir ve dizi float tipinde olusturulur
    calculated_frequencies = (float*)malloc(20 * sizeof(float));

    memcpy(calculated_frequencies, calculated_frequencies1, 10 * sizeof(float)); //memcpy fonksiyonu, dizinin ilk 10 elamanina calculated_frequencies1 dizisinin elemanlarini kopyalar/atar
    memcpy(calculated_frequencies, calculated_frequencies2, 10* sizeof(float)); //dizinin sonraki 10 elemanina calculated_frequencies2 dizisinin elemanlarini kopyalar/atar

    printf("Frekans dizisi: %.2f\n", calculated_frequencies); //bigram ve trigramlardan olusan 20 elemanli diziyi yazdirma
}

//frekanslarin uzakliklarini hesaplama
void calculated_distances()
{
    add(); //bigram ve trigramlardan olusan diziyi kullanabilmek icin fonksiyonu cagiririz

    printf("\n************************************\n");
    printf("\nIki dil icin de uzakliklar...\n");
    printf("\n************************************\n");

    float distances[2] = {0,0};

    //oklit uzaklik hesaplama formulunun kok icindeki kismi
    float distance_eng = ((calculated_frequencies[20] - frequency_eng[20]) * (calculated_frequencies[20] - frequency_eng[20]));

    printf("Ingilizce ile arasindaki uzaklik: %.4f", sqrt(distance_eng)); //'sqrt' fonksiyonu ile kok islemi yapýp ekrana sonuc bastiririz
    printf("\n");

    printf("\n************************************\n");

    //ayni islemi almanca dilindeki frekanslar ile de yapariz
    float distance_germ = ((calculated_frequencies[20] - frequency_germ[20]) * (calculated_frequencies[20] - frequency_germ[20]));

    printf("Almanca ile arasindaki uzaklik: %.4f", sqrt(distance_germ)); //kok alma islemi 'sqrt' fonksiyonu ile
    printf("\n");

    distances = (float*)malloc(2 * sizeof(float)); //malloc ile distances dizisi icin iki elemanli yer tahsis edilir
    memcpy(distances, distance_eng, sizeof(float));//float distance_eng i distances dizisine aktaririz
    memcpy(distances, distance_germ, sizeof(float)); //daha sonra da distance_germ degerini aktaririz

    printf("\n************************************\n");
}

//metnin hangi dile daha yakin oldugunu secip ekrana yazdirma
void detect_lang()
{
    printf("\n************************************\n");
    printf("Girilen metnin dili...\n");
    printf("\n************************************\n");

    const char languages[2][8] = {"english", "german"};
    calculated_distances();
    float distance_eng;
    float distance_germ;

    //eger uzaklik ingilizce dilinde almanca diline gore daha azsa
    if(distance_eng < distance_germ)
    {
        printf("Metin %s dilinde yazilmistir...\n", languages[0]); //ingilizce dilini ekrana basar
    }
    //eger almanca dilindekiyle uzaklik daha azsa
    else if(distance_germ < distance_eng)
    {
        printf("Metin %s dilinde yazlmistir...\n", languages[1]); //almanca dilini ekrana basar
    }

    printf("\n************************************\n");
}
