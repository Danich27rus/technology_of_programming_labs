//»значально в кузове игрушечного автомобил€ присутствует N песчинок, кажда€ из них имеет объем Vi и вес Ci, 
//сами песчинки расщепить на отдельные детали невозможно.“ак же существует лоток вместимостью V.
//ѕараметры: N, Vi, Ci Ц псевдорандомны и предопределены.
//
//“ребуетс€ разместить набор различных песчинок максимального веса, и при этом объем песчинок не превышает объем лотка.
//пеебором не вариант, нашел объ€снение решени€ на хабре

#include <iostream>

int main(void)
{
    const int k = 3; // количество предметов
    const double W = 4; // вместимость рюкзака
    double w[k] = { 4, 1, 3 }; // масса
    double p[k] = { 4000, 2500, 2000 }; // стоимость
    double mass[4][k]; //массив дл€ расчетов
    double weight = 0, pay = 0; //суммарный вес // суммарна€ стоимость

    for (int i = 0; i < k; ++i)  //подсчет коэффициентов и заполнение строк массива
    {
        mass[0][i] = (p[i] / w[i]);
        mass[1][i] = w[i];
        mass[2][i] = p[i];
        mass[3][i] = i + 1;

    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            double buffer;
            if (mass[0][i] > mass[0][j])
            {
                for (int z = 0; z < 4; ++z)
                {
                    buffer = mass[z][i];
                    mass[z][i] = mass[z][j];
                    mass[z][j] = buffer;
                }

            }
        }
    }

    std::cout << "Goods: ";

    for (int i = 0; i < k; ++i)
    {
        weight += mass[1][i];
        if (weight <= W)
        {
            std::cout << mass[3][i] << " ";
            pay += mass[2][i];
        }
        else
        {
            weight -= mass[1][i];
        }
    }

    std::cout << "\nTotal weight: " << weight << std::endl << "Amount: " << pay;
}