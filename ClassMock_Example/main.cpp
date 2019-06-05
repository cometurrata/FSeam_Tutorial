#include <iostream>
#include <ClassToTest.hh>

int main() {
    ClassToTest classTesting {};
    std::cout << "classTesting.isWinnerOfGameOfThrone() " << classTesting.isWinnerOfGameOfThrone("Daenarys") << "\n";
    std::cout << "classTesting.isGoodGameOfThroneSeason() " << classTesting.isGoodGameOfThroneSeason(1) << "\n";
    return 0;
}
