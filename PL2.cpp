#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Constraint {
    double a, b, c;
};

bool isUnbounded(const vector<Constraint>& constraints) {
    const double INF = numeric_limits<double>::infinity();
    double maxSlope = -INF;
    double minSlope = INF;

    for (const auto& constraint : constraints) {
        double slope = -constraint.a / constraint.b;
        cout << "A: " << constraint.a << " B: " << constraint.b << " C: " << constraint.c << endl;
        if (constraint.b > 0) {
            maxSlope = max(maxSlope, slope);
            minSlope = min(minSlope, slope);
            cout << "Slope: " << slope << " Max: " << maxSlope << " Min : " << minSlope << endl;
        } else if (constraint.a == 0) {
            return false;
        }
    }

    // nachylenie jest liczone jako alfa = arctan(-a/b) i otrzymujemy w radianach
    // arctan() * 180 / PI

     //oblicza nachylenia i sledzi najmniejsze jak i najwieksze nachylenie jednoczenisnie 

     //Po obliczeniu nachyleń program porównuje je, aby stwierdzić, czy są różne.
     //Jeśli najmniejsze i największe nachylenie są różne, oznacza to, że zbiór ograniczeń jest ograniczony.
         //Jeśli mamy różne wartości maksymalnego i minimalnego nachylenia, oznacza to, że mamy różne kąty nachylenia w różnych kierunkach. 
         //Oznacza to, że istnieje górna granica nachyleń(największe nachylenie) oraz dolna granica nachyleń(najmniejsze nachylenie), 
         //  co sugeruje, że wartości zmiennych decyzyjnych są ograniczone i nie mogą dążyć do nieskończoności.
         //Innymi słowy, dla ograniczonego zbioru ograniczeń istnieje sprecyzowany zakres, 
         //  w jakim mogą zmieniać się wartości zmiennych decyzyjnych, co umożliwia rozwiązanie problemu optymalizacji.


     /*
     Działanie warunku maxSlope <= minSlope:
         Jeśli maksymalne nachylenie jest mniejsze lub równe minimalnemu nachyleniu, oznacza to, że istnieje tylko jeden kąt nachylenia,
             którym można iść w kierunku zmiany wartości zmiennych decyzyjnych.
         W przypadku, gdy istnieje tylko jeden kąt nachylenia, możliwe jest, że wartości zmiennych decyzyjnych będą dążyć do nieskończoności
             w tym jednym kierunku.
         To oznacza, że zbiór ograniczeń jest nieograniczony, ponieważ nie ma żadnych górnych i dolnych granic dla kątów nachylenia,
             co sugeruje, że wartości zmiennych decyzyjnych mogą dążyć do nieskończoności.

     W kontekście problemu optymalizacji liniowej, gdy maksymalne nachylenie jest większe od minimalnego nachylenia, oznacza to, że mamy różne kierunki, w których zmienne decyzyjne mogą zmieniać się, aby spełnić ograniczenia. To sugeruje, że wartości zmiennych decyzyjnych mogą zmieniać się w różnych kierunkach, co z kolei sugeruje, że istnieje skończony obszar, w którym można znaleźć rozwiązanie optymalne.
         W związku z tym, gdy maxSlope > minSlope
         maxSlope>minSlope, zbiór ograniczeń jest ograniczony, co oznacza, że istnieje sprecyzowany zakres,
         w jakim można zmieniać wartości zmiennych decyzyjnych, aby znaleźć optymalne rozwiązanie.
     */
     // jeśli największe nachylenie jest mniejsze niż najmniejsze nachylenie, oznacza to, że nie ma skończonego przedziału nachyleń ograniczających y


    // jeśli największe nachylenie jest mniejsze niż najmniejsze nachylenie, oznacza to, że nie ma skończonego przedziału nachyleń ograniczających y
    return maxSlope <= minSlope;
}

int main() {
    ifstream inputFile("file.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int m;
    inputFile >> m;

    vector<Constraint> constraints(m);
    for (int i = 0; i < m; ++i) {
        inputFile >> constraints[i].a >> constraints[i].b >> constraints[i].c;
    }
    inputFile.close();

    if (isUnbounded(constraints)) {
        cout << "TAK, NIEOGRANICZONY" << endl;
    }
    else {
        cout << "NIE, OGRANICZONY" << endl;
    }

    return 0;
}