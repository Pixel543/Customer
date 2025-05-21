#include <app.h>

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
