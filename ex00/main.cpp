#include <iostream>
#include <string>
#include "Bank.hpp"

static void	report(const std::string &action, bool done)
{
	std::cout << (done ? "[   OK   ] " : "[REFUSED ] ") << action << std::endl;
}

int	main()
{
	Bank	bank(1000);
	int		a = bank.createAccount();
	int		b = bank.createAccount();

	if (a == -1 || b == -1)
	{
		std::cerr << "Could not create the accounts" << std::endl;
		return (1);
	}

	std::cout << "--- Start ---" << std::endl;
	std::cout << bank << std::endl;

	std::cout << "--- Deposits : the bank keeps 5% ---" << std::endl;
	report("deposit 100 on account A", bank.deposit(a, 100));
	report("deposit 200 on account B", bank.deposit(b, 200));
	report("deposit -50 on account A", bank.deposit(a, -50));
	report("deposit 100 on account 42 (does not exist)", bank.deposit(42, 100));
	std::cout << bank << std::endl;

	std::cout << "--- Withdrawals ---" << std::endl;
	report("withdraw 50 from account A", bank.withdraw(a, 50));
	report("withdraw 1000 from account A (not enough money)", bank.withdraw(a, 1000));
	std::cout << bank << std::endl;

	std::cout << "--- Loans : limited by the funds of the bank ---" << std::endl;
	report("loan of 500 to account B", bank.giveLoan(b, 500));
	report("loan of 1000000 to account A (bank too poor)", bank.giveLoan(a, 1000000));
	std::cout << bank << std::endl;

	std::cout << "--- A loan has to be paid back ---" << std::endl;
	report("delete account B (still in debt)", bank.deleteAccount(b));
	report("account B repays 9999 (more than the debt)", bank.repayLoan(b, 9999));
	report("account B repays 500", bank.repayLoan(b, 500));
	report("delete account B", bank.deleteAccount(b));
	report("deposit 10 on account B (deleted)", bank.deposit(b, 10));
	std::cout << bank << std::endl;

	std::cout << "--- IDs are never reused ---" << std::endl;
	int	c = bank.createAccount();
	std::cout << "new account ID : " << c << std::endl;
	std::cout << bank << std::endl;

	std::cout << "--- Reading one account with the const getters ---" << std::endl;
	const Account	*account = bank.getAccount(a);
	if (account != NULL)
	{
		std::cout << "id    : " << account->getId() << std::endl;
		std::cout << "value : " << account->getValue() << std::endl;
		std::cout << "debt  : " << account->getDebt() << std::endl;
	}
	return (0);
}
