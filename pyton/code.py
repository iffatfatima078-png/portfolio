# Lab No. 35
# Simple Banking System

accounts = {}

# Create a new account
def create_account():
    account_number = input("Enter a new account number: ")
    if account_number in accounts:
        print("Account already exists.")
    else:
        initial_deposit = float(input("Enter initial deposit amount: "))
        accounts[account_number] = initial_deposit
        print(f"Account {account_number} created with balance {initial_deposit}.")

# Deposit money
def deposit_money():
    account_number = input("Enter account number: ")
    if account_number in accounts:
        amount = float(input("Enter amount to deposit: "))
        accounts[account_number] += amount
        print(f"Deposited {amount}. New balance: {accounts[account_number]}.")
    else:
        print("Account not found.")

# Withdraw money
def withdraw_money():
    account_number = input("Enter account number: ")
    if account_number in accounts:
        amount = float(input("Enter amount to withdraw: "))
        if accounts[account_number] >= amount:
            accounts[account_number] -= amount
            print(f"Withdrew {amount}. New balance: {accounts[account_number]}.")
        else:
            print("Insufficient balance.")
    else:
        print("Account not found.")

# Check account balance
def check_balance():
    account_number = input("Enter account number: ")
    if account_number in accounts:
        print(f"Balance for account {account_number}: {accounts[account_number]}")
    else:
        print("Account not found.")

# Main program loop
def main():
    while True:
        print("\n--- Banking System Menu ---")
        print("1. Create Account")
        print("2. Deposit Money")
        print("3. Withdraw Money")
        print("4. Check Balance")
        print("5. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            create_account()
        elif choice == '2':
            deposit_money()
        elif choice == '3':
            withdraw_money()
        elif choice == '4':
            check_balance()
        elif choice == '5':
            print("Thank you for using the Banking System.")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
