#include <limits>
#include <new>
#include <utility>
#include "Bank.hpp"

Bank::Bank() : _liquidity(0), _nextId(0)
{
}

Bank::Bank(int liquidity) : _liquidity(liquidity < 0 ? 0 : liquidity), _nextId(0)
{
}

Bank::~Bank()
{
	std::map<int, Account *>::iterator	it;

	for (it = _accounts.begin(); it != _accounts.end(); ++it)
		delete it->second;
}

const int	&Bank::getLiquidity() const
{
	return (_liquidity);
}

const Account	*Bank::getAccount(int id) const
{
	std::map<int, Account *>::const_iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		return (NULL);
	return (it->second);
}

Account	*Bank::findAccount(int id)
{
	std::map<int, Account *>::iterator	it = _accounts.find(id);

	if (it == _accounts.end())
		return (NULL);
	return (it->second);
}


int	Bank::createAccount()
{
	Account	*account;

	if (_nextId == std::numeric_limits<int>::max())
		return (-1);
	account = new (std::nothrow) Account(_nextId);
	if (account == NULL)
		return (-1);
	try
	{
		_accounts.insert(std::make_pair(_nextId, account));
	}
	catch (const std::bad_alloc &)
	{
		delete account;
		return (-1);
	}
	return (_nextId++);
}


bool	Bank::deleteAccount(int id)
{
	std::map<int, Account *>::iterator	it = _accounts.find(id);

	if (it == _accounts.end() || it->second->_debt > 0)
		return (false);
	delete it->second;
	_accounts.erase(it);
	return (true);
}

bool	Bank::creditAccount(Account &account, int amount)
{
	const int	max = std::numeric_limits<int>::max();
	const int	fee = amount / 100 * _feePercent + amount % 100 * _feePercent / 100;
	const int	net = amount - fee;

	if (account._value > max - net || _liquidity > max - fee)
		return (false);
	account._value += net;
	_liquidity += fee;
	return (true);
}

bool	Bank::deposit(int id, int amount)
{
	Account	*account = findAccount(id);

	if (account == NULL || amount <= 0)
		return (false);
	return (creditAccount(*account, amount));
}

bool	Bank::withdraw(int id, int amount)
{
	Account	*account = findAccount(id);

	if (account == NULL || amount <= 0 || amount > account->_value)
		return (false);
	account->_value -= amount;
	return (true);
}


bool	Bank::giveLoan(int id, int amount)
{
	Account	*account = findAccount(id);

	if (account == NULL || amount <= 0 || amount > _liquidity)
		return (false);
	if (account->_debt > std::numeric_limits<int>::max() - amount)
		return (false);
	_liquidity -= amount;
	
	if (!creditAccount(*account, amount))
	{
		_liquidity += amount;
		return (false);
	}

	account->_debt += amount;
	return (true);
}

bool	Bank::repayLoan(int id, int amount)
{
	Account	*account = findAccount(id);

	if (account == NULL || amount <= 0)
		return (false);
	if (amount > account->_debt || amount > account->_value)
		return (false);
	if (_liquidity > std::numeric_limits<int>::max() - amount)
		return (false);
	account->_value -= amount;
	account->_debt -= amount;
	_liquidity += amount;
	return (true);
}

std::ostream	&operator<<(std::ostream &os, const Bank &bank)
{
	std::map<int, Account *>::const_iterator	it;

	os << "Bank informations : " << std::endl;
	os << "Liquidity : " << bank._liquidity << std::endl;
	for (it = bank._accounts.begin(); it != bank._accounts.end(); ++it)
		os << *it->second << std::endl;
	return (os);
}
