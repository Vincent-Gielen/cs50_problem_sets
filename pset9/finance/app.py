import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get the userID
    userID = session["user_id"]

    namedbpurchases = db.execute(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='purchases'")
    namedbsales = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='sales'")

    stocks = {}
    if namedbpurchases:
        # get every stock the user has bought
        stocks = db.execute("SELECT DISTINCT stock FROM purchases WHERE userID = ?", userID)

    # create a list of stocks with details
    stockDetails = []

    # create a grandTotal

    grandTotal = 0

    # for every one of those stocks
    for stock in stocks:

        # get the symbol of the stock
        stockSymbol = stock["stock"]

        # get the amount of stocks the user has bought
        stockAmountBought = db.execute(
            "SELECT SUM(amount) stock FROM purchases WHERE userID = ? AND stock = ?", userID, stockSymbol)[0]["stock"]

        # get the total amount of stocks the user has
        stockAmountTotal = stockAmountBought

        if namedbsales:
            # get the amount of stocks the user has sold
            stockAmountSold = db.execute(
                "SELECT SUM(amount) stock FROM sales WHERE userID = ? AND stock = ?", userID, stockSymbol)[0]["stock"]
            if stockAmountSold:
                stockAmountTotal -= stockAmountSold

        if stockAmountTotal > 0:

            # get the current price of te stock
            stockPrice = lookup(stockSymbol)["price"]
            stockPriceUsd = usd(float(stockPrice))

            # get the total value of what the owner has and add it to the grandTotal
            stockTotalValue = stockAmountTotal * stockPrice
            stockTotalValueUsd = usd(float(stockTotalValue))
            grandTotal += stockTotalValue

            stockDetails.append({
                "symbol": stockSymbol,
                "price": stockPriceUsd,
                "amount": stockAmountTotal,
                "total_value": stockTotalValueUsd
            })

    currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]
    currentCashUsd = usd(float(currentCash))
    grandTotal += currentCash
    grandTotalUsd = usd(float(grandTotal))

    return render_template("index.html", stockDetails=stockDetails, currentCashUsd=currentCashUsd, grandTotalUsd=grandTotalUsd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)

        if not symbol:
            return apology("must provide symbol", 400)
        if not stock:
            return apology("stock does not exist", 400)
        if not shares.isnumeric():
            return apology("Amount of shares must be positive", 400)
        if not shares or int(shares) <= 0:
            return apology("Amount of shares must be positive", 400)

        userID = session["user_id"]
        currentStockPrice = stock["price"]
        userCashDB = db.execute("SELECT cash FROM users WHERE id = ?", userID)
        userCash = userCashDB[0]["cash"]

        # Get today's date
        today = datetime.date.today()
        # Format the date as a string in the format YYYY-MM-DD
        formatted_date = today.strftime("%Y-%m-%d")

        if userCash < float(shares) * currentStockPrice:
            return apology("You do not have enough cash", 403)

        db.execute("CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, userID INTEGER NOT NULL, stock TEXT NOT NULL, price REAL NOT NULL, amount INTEGER NOT NULL, date TEXT NOT NULL, FOREIGN KEY (userID) REFERENCES users(id))")
        db.execute("INSERT INTO purchases (userID, stock, price, amount, date) VALUES (?, ?, ?, ?, ?)",
                   userID, symbol, currentStockPrice, shares, formatted_date)

        newUserCash = userCash - (float(shares) * currentStockPrice)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", newUserCash, userID)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    userID = session["user_id"]

    purchases = db.execute("SELECT * FROM purchases WHERE userID = ?", userID)
    sales = db.execute("SELECT * FROM sales WHERE userID = ?", userID)

    tradesList = []

    for purchase in purchases:
        tradesList.append({
            "symbol": purchase["stock"],
            "type": "purchase",
            "amount": purchase["amount"],
            "price": usd(purchase["price"]),
            "dateTime": purchase["date"]
        })

    for sale in sales:
        tradesList.append({
            "symbol": sale["stock"],
            "type": "sale",
            "amount": sale["amount"],
            "price": usd(sale["price"]),
            "dateTime": sale["date"]
        })

    return render_template("history.html", tradesList=tradesList)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        stock = lookup(symbol)
        if not stock:
            return apology("invalid ticker", 400)

        price = usd(stock["price"])

        return render_template("quoted.html", stock=stock, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide confirmation", 400)

        if password != confirmation:
            return apology("Password and confirmation must match", 400)

        hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except Exception as e:
            return apology("Username is already in use", 400)

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    userID = session["user_id"]

    # Check if tables exist
    namedb = db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='purchases'")

    stocks = {}
    if namedb:
        # get every stock the user has bought
        stocks = db.execute("SELECT DISTINCT stock FROM purchases WHERE userID = ?", userID)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)

        if not symbol:
            return apology("must provide symbol", 400)
        if not stock:
            return apology("stock does not exist", 400)
        if not shares or int(shares) <= 0:
            return apology("Amount of shares must be positive", 400)

        # check if user has the stock
        stocksOfUser = db.execute(
            "SELECT SUM(amount) stock FROM purchases WHERE userID = ? AND stock = ?", userID, symbol)[0]["stock"]
        if not stocksOfUser:
            return apology("You don't own this stock", 400)
        # check if user has the required amount of shares
        if stocksOfUser < int(shares):
            return apology("You don't have enough shares", 400)

        # get the current price of te stock and total value of stock to be sold
        currentStockPrice = stock["price"]
        soldValue = currentStockPrice * float(shares)

        # get the cash the user has
        userCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]
        # Add the soldValue to the cash of the owner and update the db
        newCash = userCash + soldValue
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userID)

        # Get today's date
        today = datetime.date.today()
        # Format the date as a string in the format YYYY-MM-DD
        formatted_date = today.strftime("%Y-%m-%d")

        # create a new sales table
        db.execute("CREATE TABLE IF NOT EXISTS sales (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, userID INTEGER NOT NULL, stock TEXT NOT NULL, price REAL NOT NULL, amount INTEGER NOT NULL, date TEXT NOT NULL, FOREIGN KEY (userID) REFERENCES users(id))")
        db.execute("INSERT INTO sales (userID, stock, price, amount, date) VALUES (?, ?, ?, ?, ?)",
                   userID, symbol, currentStockPrice, shares, formatted_date)

        return redirect("/")
    else:
        return render_template("sell.html", stocks=stocks)
