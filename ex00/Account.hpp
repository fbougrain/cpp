#ifndef ACCOUNT_HPP
# define ACCOUNT_HPP

# include <ostream>

class Account
{
public:
	const int	&getId() const;
	const int	&getValue() const;
	const int	&getDebt() const;

private:
	explicit Account(int id);
	~Account();
	Account(const Account &other);
	Account	&operator=(const Account &other);

	const int	_id;
	int			_value;
	int			_debt;

	friend class Bank;
};

std::ostream	&operator<<(std::ostream &os, const Account &account);

#endif
