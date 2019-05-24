#include <iostream>
#include <ClassToTest.hh>

int main() {
    ClassToTest classTesting {};
    std::cout << "classTesting.isOneOfBestGameInTheWorld() " << classTesting.isOneOfBestGameInTheWorld("Quentin", "StarcraftII") << "\n";
    std::cout << "classTesting.isFavoriteNumber() " << classTesting.isFavoriteNumber(42) << "\n";
    return 0;
}
