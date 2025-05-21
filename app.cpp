#include "app.h"

//Logger implementation
Logger::Logger(const std::string& filename)
{
    logFile.open(filename, std::ios::app);
    if (!logFile) std::cerr << "Error opening log file: " << filename << std::endl;
}

Logger::~Logger()
{
    if(logFile.is_open()) logFile.close();
}

void Logger::log(const std::string& message)
{
    time_t now = time(nullptr);
    char buff[20];
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", localtime(&now));
}

//Customer implementation
Customer::Customer()
    : m_id(0), m_lastName(""), m_firstName(""), m_cardNumber(0), m_accountNumber(0) {}

Customer::Customer(int _id, const std::string& ln, const std::string& fn)
    : m_id(_id), m_lastName(ln), m_firstName(fn), m_cardNumber(0), m_accountNumber(0) {}

Customer::Customer(int _id, const std::string& ln, const std::string& fn, int card, int acct)
    : m_id(_id), m_lastName(ln), m_firstName(fn), m_cardNumber(card), m_accountNumber(acct) {}

void Customer::setId(int _id) {m_id = _id;}
void Customer::setLastName(const std::string& ln) {m_lastName = ln;}
void Customer::setFirstName(const std::string& fn) {m_firstName = fn;}
void Customer::setCardNumber(int card) {m_cardNumber = card;}
void Customer::setAccountNumber(int acct) {m_accountNumber = acct;}

int Customer::getId() const {return m_id;}
std::string Customer::getLastName() const {return m_lastName;}
std::string Customer::getFirstName() const {return m_firstName;}
int Customer::getCardNumber() const {return m_cardNumber;}
int Customer::getAccountNumber() const {return m_accountNumber;}

std::string Customer::toString() const
{
    std::ostringstream oss;
    oss << "ID: " << m_id
        << ", LastName: " << m_lastName
        << ", FirstName: " << m_firstName
        << ", Card#: " << std::setw(4) << std::setfill('0') << m_cardNumber
        << ", Account#: " << std::setw(5) << std::setfill('0') << m_accountNumber;
    
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {return os << c.toString();}

//CustomerManager implementation
CustomerManager::CustomerManager(Logger& log)   : m_logger(log) {}

void CustomerManager::add(const Customer& c)
{
    m_customers.push_back(c);
    m_logger.log("Added: " + c.toString());
}
void CustomerManager:: sortByLastName()
{
    std::sort(m_customers.begin(), m_customers.end()),
                [](const Customer& a, const Customer& b) {return a.getLastName() < b.getLastName();};
    
    m_logger.log("Sorted by last name");
}

std::vector<Customer> CustomerManager::filterByCardRange(int low, int high)
{
    std::vector<Customer> res;
    for (auto& c : m_customers)
    {
        if (c.getCardNumber() >= low && c.getCardNumber() <= high)
            res.push_back(c);
    }
    m_logger.log("Filtered cards in ["+ std::to_string(low) + ", " + std::to_string(high) + "]");
    return res;
}

void CustomerManager::saveToFileEncrypted(const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::binary);

    for (auto& c : m_customers)
    {
        std::string line = c.toString() + "\n";
        for (char ch : line)
        {
            char enc = ch ^ m_xorKey;
            ofs.write(&enc, 1);
        }
    }
    m_logger.log("Saved " + std::to_string(m_customers.size()) + " customers to " + filename);
}

void CustomerManager::loadFromFileEncrypted(const std::string& filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
    {
        m_logger.log("Cannot open file: " + filename);
        return;
    }
    m_customers.clear();
    std::string accum;
    char ch;
    while (ifs.read(&ch, 1))
    {
        char dec = ch ^ m_xorKey;
        if (dec == '\n')
        {
            std::cout << "Loaded: " << accum << std::endl;
            accum.clear();
        } else {
            accum.push_back(dec);
        }
    }
    m_logger.log("Loaded and decrypted from " + filename);
}
void CustomerManager::printAll() const
{
    for (auto& c : m_customers)
        std::cout << c << std::endl;
}