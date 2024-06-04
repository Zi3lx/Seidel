#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

struct Constraint {
    double a, b, c;
};

bool isUnbounded(const std::vector<Constraint>& constraints) {
    const double INF = std::numeric_limits<double>::infinity();
    double maxSlope = -INF;
    double minSlope = INF;

    for (const auto& constraint : constraints) {
        double slope = -constraint.a / constraint.b;
        if (constraint.b > 0) {
            maxSlope = std::max(maxSlope, slope); // ograniczaj y od gory
            minSlope = std::min(minSlope, slope); // ograniczaja y od dołu
        } else if (constraint.a == 0) {
            return true;
        }
    }

    // jeśli największe nachylenie jest mniejsze niż najmniejsze nachylenie, oznacza to, że nie ma skończonego przedziału nachyleń ograniczających y
    return maxSlope <= minSlope;
}

int main() {
    std::ifstream inputFile("file.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    int m;
    inputFile >> m;

    std::vector<Constraint> constraints(m);
    for (int i = 0; i < m; ++i) {
        inputFile >> constraints[i].a >> constraints[i].b >> constraints[i].c;
    }

    inputFile.close();

    if (isUnbounded(constraints)) {
        std::cout << "TAK" << std::endl;
    } else {
        std::cout << "NIE" << std::endl;
    }

    return 0;
}
