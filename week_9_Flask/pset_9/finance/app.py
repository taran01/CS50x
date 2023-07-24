import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    # Get current cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    # Get all purchased stock
    purchased = db.execute(
        "SELECT symbol, sum(shares) AS shares FROM transactions WHERE username = ? GROUP BY symbol HAVING sum(shares) > 0", session["username"])

    # For latest prices
    price = {}
    for item in purchased:
        search = lookup(item["symbol"])
        price[item["symbol"]] = search["price"]

    # For total sum of shares
    i = 0
    value = 0
    while i < len(price):
        for item in price:
            rate = price[item]
            value += rate * purchased[i]["shares"]
            i += 1

    return render_template("index.html", price=price, purchased=purchased, cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure all inputs are submitted
        if not all([symbol, shares]):
            return apology("Must provide symbol & shares")

        # Ensure if shares is a +tve number
        try:
            shares = int(shares)
        except ValueError as e:
            print(e)
            return apology("Please prove positive shares.")

        if shares < 1:
            return apology("Please prove positive shares.")

        print(type(shares))

        # Ensure symbol is valid
        search = lookup(symbol)
        if not search:
            return apology("Please check your symbol")

        # Ensure user has enough cash
        query = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        user_money = query[0]["cash"]
        total_amount = search["price"] * shares

        if user_money < total_amount:
            return apology("Not enough cash")

        # Buy the stock and add transaction detail in database
        db.execute("INSERT INTO transactions (username, symbol, type, shares, price, timestamp) VALUES (?,?,?,?,?, datetime('now', 'localtime'))",
                   session["username"], symbol, "bought", shares, search["price"])

        # Update user's cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_money - total_amount, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, type, shares, price, timestamp FROM transactions WHERE username = ?", session["username"])
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

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
        search = lookup(symbol)

        if not search:
            return apology("Please check your symbol")

        return render_template("quoted.html", search=search)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure all inputs were submitted
        if not all([username, password, confirmation]):
            return apology("Must provide username, password and confirmation")

        # Ensure both password and confirmation match
        if password != confirmation:
            return apology("Password and confirmation don't match")

        # Check database if username is already taken
        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(user) > 0:
            return apology("Username already exists")

        # Add user to database
        userid = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        session["user_id"] = userid
        session["username"] = username

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Ensure symbol is submitted
        if not symbol:
            return apology("Must provide symbol", 403)

        # Ensure shares are +tve number
        if not shares or shares < 1:
            return apology("Must provide positive shares")

        # Ensure if user have enough shares to sell and symbol is valid
        owned_shares = db.execute(
            "SELECT symbol, sum(shares) AS shares FROM transactions WHERE username = ? AND symbol = ? GROUP BY symbol HAVING sum(shares) > 0", session["username"], symbol)
        if not owned_shares:
            return apology("Not a valid symbol or not enough shares")
        if shares > owned_shares[0]["shares"]:
            return apology("Not enough shares")

        # Update transactions and user's cash
        search = lookup(symbol)
        amount = shares * search["price"]

        db.execute("INSERT INTO transactions (username, symbol, type, shares, price, timestamp) VALUES (?,?,?,?,?, datetime('now', 'localtime'))",
                   session["username"], symbol, "sold", -(shares), search["price"])

        db.execute("UPDATE users SET cash = cash + ? WHERE username = ?", amount, session["username"])

        return redirect("/")

    else:
        owned = db.execute(
            "SELECT symbol, sum(shares) AS shares FROM transactions WHERE username = ? GROUP BY symbol HAVING sum(shares) > 0", session["username"])
        return render_template("sell.html", owned=owned)


@app.route("/ch_password", methods=["GET", "POST"])
@login_required
def ch_password():
    """Change user's password"""
    if request.method == "POST":
        old = request.form.get("old")
        new = request.form.get("new")
        conform = request.form.get("conform")

        # Ensure all fields are submitted
        if not all([old, new, conform]):
            return apology("Must provide all fields.", 403)

        # Ensure new and conform password match
        if new != conform:
            return apology("New password and conform don't match", 403)

        # Check if old password is correct
        query = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        if not check_password_hash(query[0]["hash"], old):
            return apology("Invalid previous password")

        # Ensure new password is alpha-numerical
        if not new.isalnum():
            return apology("Your password must only contain letters and numbers", 403)

        # Update user's password
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new), session["user_id"])
        return redirect("/login")
    else:
        return render_template("password.html")