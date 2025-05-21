#include "app.h"

int main()
{
    Logger logger("app.log");
    CustomerManager mgr(logger);

    mgr.add(Customer(1, "Ivanenko", "Petro", 1234, 54321));
    mgr.add(Customer(2, "Bondar", "Mary", 2345, 12345));
    mgr.add(Customer(3, "Koval", "Igor", 3456, 67890));
    mgr.add(Customer(4, "Svyatoshinska", "Olena", 4567, 11111));

    std::cout << "\n --Initial list -- \n";
    mgr.printAll();

    mgr.sortByLastName();
    std::cout << "\n --Sorted by last name -- \n";
    mgr.printAll();

    int low = 2000, high = 4000;

    auto filtered = mgr.filterByCardRange(low, high);

    std::cout << "\n-- Filtered [" << low << ", " << high << "] --\n";
    for (auto& c : filtered)
        std::cout << c << std::endl;
    
    mgr.saveToFileEncrypted("customers.dat");
}