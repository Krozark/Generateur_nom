#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define Y_POS   6
#define MERDE   4
#define AUTRE   26 - Y_POS -MERDE  /*q+*/

#define VOY_RATIO 0.5
#define MERDE_RATIO  VOY_RATIO + 0.09

class GenMot
{
    public :
        static inline const double randRange(double fMin, double fMax)
        {
            return fMin + ((double)rand() / RAND_MAX)*(fMax - fMin);
        };

        static const int IsAEOIUY(char c)
        {
            const char L[]={ 'a','e','i','o','u','y'};
            int i;
            for (i=0;i<Y_POS;++i)
                if (c == L[i])
                    return 1;
            return 0;
        };

        static const char GenVoy()
        {
            const char L[]={ 'a','e','i','o','u','y'};
            return L[(int)randRange(0,Y_POS)];
        };

        static const char GenCon()
        {
            const char L[]={'b','c','d','g','h','j','k','l','m','n','p','r','s','t','v','w'};
            return L[(int)randRange(0,AUTRE)];
        };

        static const char GenMerde()
        {
            const char L[]={'q','x','z','f'};
            return L[(int)randRange(0,MERDE)];
        };

        static const char GenLet()
        {
            double i=randRange(0,1);

            if ( i < VOY_RATIO)
                return GenVoy();
            else if (i < MERDE_RATIO)
                return GenMerde();
            else
                return GenCon();
        };

        static const char* GenWord(const unsigned int min,const unsigned int max )
        {
            const int nb = (int)randRange(min,max);
            std::string res;
            for (int i=0;i<nb;++i)
            {
                char c;
                if (i <2)
                    c=GenLet();
                else
                {
                    int Voy=IsAEOIUY(res[i-1])+IsAEOIUY(res[i-2]);
                    if (Voy==1)//une Cons + 1 voy
                        c=GenLet();
                    else if (Voy == 0)
                        c=GenVoy();
                    else
                        c=GenCon();

                }
                res+=c;
            }
            res+='\0';
            return res.c_str();
        }


    private:
    GenMot()
    {

    }
};
