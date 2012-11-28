#include "GenMot.hpp"
//#include "LireMot.hpp"
//#include "LireCode.hpp"


#define SINE_WAVE       0
#define SQUARE_WAVE     1
#define TRIANGLE_WAVE   2
#define SAW_WAVE        4
#define WHITE_NOISE     5

#define CURRENT SINE_WAVE

#define NB_MOTS 10
#define MODE MOT

int wave=CURRENT;

int main(int argc, char* argv[])
{
     srand(time(NULL));
    #if MODE == MOT
    int i=0;
    while (true)
    {
        printf("%s\t\t\t",GenMot::GenWord(4,9));
        ++i;
        if (i==3)
        {
            sleep(1);
            printf("\n");
            i=0;
        }
    }


    #elif MOD == LECTURE
    LireMot Lecteur(CURRENT,50,25);


   if (argc >1)
        Lecteur.ReadWord(argv[1]);
    else
        Lecteur.ReadWord("Mwaaa je suis sur que tu comprend tellement rie à se que je dis que ça te fait limite peur !!!");

    #else
    if (argc>1)
        wave=atoi(argv[1]);
    LireCode Code(wave,"/home/maxime/Bureau/anka dreles/Informatique/Anka_Dreles/website/views.py");
    Code.ReadCode();
    #endif


    return 0;
}
