#include <iostream>
#include <ClassToTest.hh>

int main() {
    ClassToTest classTesting {};
    std::cout << "classTesting.isWinnerOfGamesOfThrone() " << classTesting.isWinnerOfGamesOfThrone("Daenarys") << "\n";
    std::cout << "classTesting.isGoodGamesOfThroneSeason() " << classTesting.isGoodGamesOfThroneSeason(1) << "\n";
    return 0;
}
