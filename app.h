#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// ============== Logger ==============
class Logger
{
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);
};

// ============== Customer ==============
class Customer
{
private:
    int m_id;
    std::string m_firstName;
    std::string m_lastName;
    int m_cardNumber;
    int m_accountNumber;

public:
    Customer();
    Customer(int _id, const std::string& ln, const std::string& fn);
    Customer(int _id, const std::string& ln, const std::string& fn, int card, int acct);

    void setId(int _id);
    void setLastName(const std::string& ln);
    void setFirstName(const std::string& fn);
    void setCardNumber(int card);
    void setAccountNumber(int acct);

    int getId() const;
    std::string getLastName() const;
    std::string getFirstName() const;
    int getCardNumber() const;
    int getAccountNumber() const;

    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
};

// ============== CustomerManager==============
class CustomerManager
{
private:
    std::vector<Customer> m_customers;
    Logger& m_logger;
    const char m_xorKey = 0x5A;
public:
    CustomerManager(Logger& log);
    void add(const Customer& c);
    void sortByLastName();
    std::vector<Customer> filterByCardRange(int low, int high);
    void saveToFileEncrypted(const std::string& filename);
    void loadFromFileEncrypted(const std::string& filename);
    void printAll() const;
};