#include <iostream>
#include <ClassToTest.hh>

int main() {
    ClassToTest classTesting {};
    std::cout << "classTesting.isWinnerOfGamesOfThrones() " << classTesting.isWinnerOfGamesOfThrones("Daenarys") << "\n";
    std::cout << "classTesting.isGoodGamesOfThroneSeason() " << classTesting.isGoodGamesOfThroneSeason(8) << "\n";
    return 0;
}
