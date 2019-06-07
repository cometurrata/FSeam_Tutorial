#include <iostream>
#include <ClassToTest.hh>

int main() {
    ClassToTest classTesting {};
    std::cout << "classTesting.isWinnerOfGameOfThrones() " << classTesting.isWinnerOfGameOfThrones("Daenarys") << "\n";
    std::cout << "classTesting.isGoodGameOfThronesSeason() " << classTesting.isGoodGameOfThronesSeason(1) << "\n";
    return 0;
}
