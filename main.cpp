#include <fstream>
#include <iostream>

class Address {
private:
    std::string city;
    std::string street;
    int house_number;
    int flat;

public:
    Address() = delete;
    Address(std::string city, std::string street, int house_number, int flat) {
        this->city = city;
        this->street = street;
        this->house_number = house_number;
        this->flat = flat;
    }

    std::string getCity () {
        return this->city;
    }
    std::string  getStreet() {
        return this->street;
    }
    int getHouse() {
        return this->house_number;
    }
    int getFlat() {
        return this->flat;
    }

    static void sort(Address** arr, int n) {
        std::stable_sort(arr, arr + n, [](Address* lhs, Address* rhs) {
            return lhs->getCity() < rhs->getCity();
        });
    }

};

int main() {

    int n = 0;

    std::ifstream fin("in.txt");
    if (!fin) {
        std::cerr << "Не удалось открыть файл in.txt";
        return 1;
    }

    fin >> n;
    Address** arr = new Address*[n];
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Текст в файле in.txt: " << std::endl;

    for (int i = 0; i < n; ++i) {
        std::string city;
        std::string street;
        int house_number;
        int flat;

        fin >> city >> street >> house_number >> flat;
        arr[i] = new Address(city, street, house_number, flat);

        std::cout << arr[i]->getCity();
        std::cout << " ";
        std::cout << arr[i]->getStreet();
        std::cout << " ";
        std::cout << arr[i]->getHouse();
        std::cout << " ";
        std::cout << arr[i]->getFlat();
        std::cout << std::endl;
    }
    fin.close();

    Address::sort(arr, n);

    std::ofstream out("out.txt");
    if (!out) {
        std::cerr << "Не удалось открыть out.txt для записи\n";
        return 1;
    }

    out << n << '\n';
    for (size_t i = 0; i < n; ++i) {
        out << arr[i]->getCity() << ", "
            << arr[i]->getStreet() << ", "
            << arr[i]->getHouse() << ", "
            << arr[i]->getFlat()  << '\n';
    }

    out.close();

    for (int i = 0; i < n; ++i) {
        delete arr[i];
    }
    delete[] arr;

    std::cout << std::endl;
    std::cout << "Текст в файле out.txt: " << std::endl;
    std::ifstream fin_out("out.txt");
    std::cout << fin_out.rdbuf();
    fin_out.close();

    return EXIT_SUCCESS;
}