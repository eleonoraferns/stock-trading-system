This is a simple online stock management system that manages the trading of shares in the stock market.
Its key classes include:
Stock: A base class to manage the price and symbol of the stocks.
Trade: Manages the prices and quantities of all tradeable stocks. It uses a parameterized constructor to set the initial price and quantity and has functions to update the same.
Portfolio: This class manages all the operations on the stocks. It includes the following functions:
add_stock: adds a new stock item to the database
get_total_value: returns the total worth of all available stocks.
display_portfolio: displays the available stocks.
find_stock: returns a pointer to an object of class trade if the requested stock is available, returns a nullptr otherwise.
buy/sell: Functions to  buy and sell stocks.


To check out the code feel free to copy and run it on any C++ compiler.
