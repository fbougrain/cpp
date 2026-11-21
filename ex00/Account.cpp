#include "Account.hpp"

Account::Account(int id) : _id(id), _value(0), _debt(0)
{
}

Account::~Account()
{
}

const int	&Account::getId() const
{
	return (_id);
}

const int	&Account::getValue() const
{
	return (_value);
}

const int	&Account::getDebt() const
{
	return (_debt);
}

std::ostream	&operator<<(std::ostream &os, const Account &account)
{
	os << "[" << account.getId() << "] - [" << account.getValue() << "]";
	if (account.getDebt() > 0)
		os << " (debt: " << account.getDebt() << ")";
	return (os);
}
