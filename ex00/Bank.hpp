#ifndef BANK_HPP
# define BANK_HPP

# include <map>
# include <ostream>
# include "Account.hpp"


class Bank
{
public:
	Bank();
	explicit Bank(int liquidity);
	~Bank();

	
	const int		&getLiquidity() const;
	
	const Account	*getAccount(int id) const;

	// Returns the ID of the new account, or -1 if it could not be created.
	int		createAccount();
	bool	deleteAccount(int id);

	bool	deposit(int id, int amount);
	bool	withdraw(int id, int amount);
	bool	giveLoan(int id, int amount);
	bool	repayLoan(int id, int amount);

private:
	// Not implemented on purpose: the bank owns its accounts through
	// pointers, a copy would delete them twice.
	Bank(const Bank &other);
	Bank	&operator=(const Bank &other);

	Account	*findAccount(int id);
	// The only place where money enters an account: the 5% fee is taken here.
	bool	creditAccount(Account &account, int amount);

	static const int	_feePercent = 5;

	int							_liquidity;
	int							_nextId;
	std::map<int, Account *>	_accounts;

	friend std::ostream	&operator<<(std::ostream &os, const Bank &bank);
};

#endif
