from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, timedelta

from helpers import apology, login_required, usd

INCOME_CATEGORIES = ["salary", "daddy", "bonus", "allowance", "other"]
EXPENSE_CATEGORIES = ["fuel", "food", "transportation", "education", "hotel", "recharge", "other"]


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///money.db")

def format_timestamp(s):
    datetime_obj = datetime.strptime(s, "%Y-%m-%dT%H:%M")
    normal_date = datetime_obj.strftime("%-d %b, %Y %I:%M %p")
    return normal_date


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# @app.context_processor
# @login_required
# def inject_username():
#     username = session["username"]
#     return dict(username=username)


@app.route("/")
@login_required
def index():
    income = db.execute("SELECT timestamp, amount, category, note FROM income WHERE username = ? ORDER BY timestamp DESC LIMIT 10", session["username"])
    sum_income = db.execute("SELECT SUM(amount) as amount FROM income WHERE username = ? ORDER BY timestamp DESC LIMIT 10", session["username"])
    expense = db.execute("SELECT timestamp, amount, category, note FROM expense WHERE username = ? ORDER BY timestamp DESC LIMIT 10", session["username"])
    sum_expense = db.execute("SELECT SUM(amount) as amount FROM expense WHERE username = ? ORDER BY timestamp DESC LIMIT 10", session["username"])
    income_parse = []
    for entry in income:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        income_parse.append(dictionary)

    expense_parse = []
    for entry in expense:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        expense_parse.append(dictionary)

    return render_template("index.html", income=income_parse, expense=expense_parse, income_sum=sum_income, expense_sum=sum_expense, username=session["username"])


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
        return render_template("password.html", username=session["username"])


@app.route("/add_income", methods=["GET", "POST"])
@login_required
def add_income():
    if request.method == "POST":
        amount = request.form.get("amount")
        category = request.form.get("category")
        date = request.form.get("date")
        note = request.form.get("note")

        if not all([amount, category, date]):
            return apology("Please prove all fields")

        if float(amount) < 1 or category not in INCOME_CATEGORIES:
            return apology("Invalid Input")

        db.execute("INSERT INTO income (username, timestamp, amount, category, note) VALUES (?, ?, ?, ?, ?)", session["username"], date, amount, category, note)

        return redirect("/")
    else:
        return render_template("income.html", in_cat=INCOME_CATEGORIES, username=session["username"])


@app.route("/add_expense", methods=["GET", "POST"])
@login_required
def add_expense():
    if request.method == "POST":
        amount = request.form.get("amount")
        category = request.form.get("category")
        date = request.form.get("date")
        note = request.form.get("note")

        if not all([amount, category, date]):
            return apology("Please prove all fields")

        if float(amount) < 1 or category not in EXPENSE_CATEGORIES:
            return apology("Invalid Input")

        db.execute("INSERT INTO expense (username, timestamp, amount, category, note) VALUES (?, ?, ?, ?, ?)", session["username"], date, amount, category, note)

        return redirect("/")
    else:
        return render_template("expense.html", ex_cat=EXPENSE_CATEGORIES, username=session["username"])


@app.route("/daily")
@login_required
def daily():
    today = datetime.now().strftime("%Y-%m-%d")

    today_income_entries = db.execute("SELECT timestamp, amount, category, note FROM income WHERE timestamp LIKE ? AND username = ?", today + "%", session["username"])
    sum_income = db.execute("SELECT SUM(amount) as amount FROM income WHERE username = ? AND timestamp LIKE ?", session["username"], today + "%")
    today_expense_entries = db.execute("SELECT timestamp, amount, category, note FROM expense WHERE timestamp LIKE ? AND username = ?", today + "%", session["username"])
    sum_expense = db.execute("SELECT SUM(amount) as amount FROM expense WHERE username = ? AND timestamp LIKE ?", session["username"], today + "%")

    income_parse = []
    for entry in today_income_entries:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        income_parse.append(dictionary)

    expense_parse = []
    for entry in today_expense_entries:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        expense_parse.append(dictionary)

    return render_template("daily.html", income=income_parse, expense=expense_parse, income_sum=sum_income, expense_sum=sum_expense, username=session["username"])


@app.route("/search")
@login_required
def search():
    return render_template("search.html", username=session["username"])


@app.route("/query")
@login_required
def query():
    _from = request.args.get("from")
    _to = request.args.get("to")

    if not all([_from, _to]):
        return "error"

    to_date_str = datetime.strptime(_to, "%Y-%m-%d")
    day_added = to_date_str + timedelta(days=1)
    to = day_added.strftime("%Y-%m-%d")

    income_entries = db.execute("SELECT timestamp, amount, category, note FROM income WHERE username = ? AND timestamp >= ? AND timestamp <= ? ORDER BY timestamp DESC", session["username"], _from, to)
    sum_income = db.execute("SELECT SUM(amount) as amount FROM income WHERE username = ? AND timestamp >= ? AND timestamp <= ?", session["username"], _from, to)
    expense_entries = db.execute("SELECT timestamp, amount, category, note FROM expense WHERE username = ? AND timestamp >= ? AND timestamp <= ? ORDER BY timestamp DESC", session["username"], _from, to)
    sum_expense = db.execute("SELECT SUM(amount) as amount FROM expense WHERE username = ? AND timestamp >= ? AND timestamp <= ?", session["username"], _from, to)

    income_parse = []
    for entry in income_entries:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        income_parse.append(dictionary)

    expense_parse = []
    for entry in expense_entries:
        dictionary = {
            "timestamp": format_timestamp(entry["timestamp"]),
            "amount": entry["amount"],
            "category": entry["category"],
            "note": entry["note"]
        }
        expense_parse.append(dictionary)

    return render_template("query.html", income=income_parse, expense=expense_parse, income_sum=sum_income, expense_sum=sum_expense)


@app.route("/delete", methods=["GET", "POST"])
@login_required
def delete():
    if request.method == "POST":
        data = request.get_json()
        print(data)
        _from = data["from"]
        _to = data["to"]

        if not all([_from, _to]):
            return "error"

        to_date_str = datetime.strptime(_to, "%Y-%m-%d")
        day_added = to_date_str + timedelta(days=1)
        to = day_added.strftime("%Y-%m-%d")

        income_entries = db.execute("SELECT id, timestamp, amount, category, note FROM income WHERE username = ? AND timestamp >= ? AND timestamp <= ? ORDER BY timestamp DESC", session["username"], _from, to)
        expense_entries = db.execute("SELECT id, timestamp, amount, category, note FROM expense WHERE username = ? AND timestamp >= ? AND timestamp <= ? ORDER BY timestamp DESC", session["username"], _from, to)

        income_parse = []
        for entry in income_entries:
            dictionary = {
                "id": entry["id"],
                "timestamp": format_timestamp(entry["timestamp"]),
                "amount": entry["amount"],
                "category": entry["category"],
                "note": entry["note"]
            }
            income_parse.append(dictionary)

        expense_parse = []
        for entry in expense_entries:
            dictionary = {
                "id": entry["id"],
                "timestamp": format_timestamp(entry["timestamp"]),
                "amount": entry["amount"],
                "category": entry["category"],
                "note": entry["note"]
            }
            expense_parse.append(dictionary)

        return render_template("delete_entry.html", income=income_parse, expense=expense_parse)

    else:
        return render_template("delete.html", username=session["username"])


@app.route("/delete_entry")
@login_required
def delete_entry():
    id = request.args.get("id")
    type = request.args.get("type")
    if type == "income":
        db.execute("DELETE FROM income WHERE username = ? AND id = ?", session["username"], id)
        return "deleted"
    if type == "expense":
        db.execute("DELETE FROM expense WHERE username = ? AND id = ?", session["username"], id)
        return "deleted"
