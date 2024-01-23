import os

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
# checking API key is set or not
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
    # Show portfolio
    rows_index = db.execute(
        "SELECT * FROM portfolios WHERE user_id = ?", session["user_id"]
    )
    # Show cash
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[
        0
    ]["cash"]
    # Calculate total
    tot = db.execute(
        "SELECT SUM(shares * price) FROM portfolios WHERE user_id = ?",
        session["user_id"],
    )[0]["SUM(shares * price)"]
    if tot == None:
        tot = 0
    return render_template("index.html", rows=rows_index, cash=user_cash, total=tot)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        buy_symbol = request.form.get("symbol")
        user_stock = lookup(buy_symbol)
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        # Is symbol valid ?
        if user_stock == None:
            return apology("symbol invalid !!!", 400)
        # Is shares number of numeric ?
        elif not request.form.get("shares").isdigit():
            return apology("shares invalid !!!", 400)
        # Is shares number of more than zero ?
        elif int(request.form.get("shares")) <= 0:
            return apology("shares invalid !!!", 400)
        # Is shares number of valid ?
        elif user_stock["price"] > user_cash[0]["cash"]:
            return apology("can't afford the number of shares", 400)
        else:
            # Update history
            shares = int(request.form.get("shares"))
            db.execute(
                "INSERT INTO history (user_id, symbol, name, shares, price, action) VALUES(?, ?, ?, ?, ?, ?)",
                session["user_id"],
                user_stock["symbol"],
                user_stock["name"],
                shares,
                user_stock["price"],
                "buy",
            )
            # Update user's portfolio and Check if user already owns the stock
            rows = db.execute(
                "SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                user_stock["symbol"],
            )
            if len(rows) == 1:
                shar = int(request.form.get("shares"))
                db.execute(
                    "UPDATE portfolios SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                    shar,
                    session["user_id"],
                    user_stock["symbol"],
                )
            else:
                db.execute(
                    "INSERT INTO portfolios (user_id, symbol, name, shares, price) VALUES(?, ?, ?, ?, ?)",
                    session["user_id"],
                    user_stock["symbol"],
                    user_stock["name"],
                    request.form.get("shares"),
                    user_stock["price"],
                )
            # cash ?
            db.execute(
                "UPDATE users SET cash = cash - ? WHERE id = ?",
                user_stock["price"] * int(request.form.get("shares")),
                session["user_id"],
            )

            # Redirect to index
            return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Show user's history
    r = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("user_history.html", rows=r)


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
            return apology("username or password invalid !!!", 403)

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
        # symbol was submitted
        symbol = request.form.get("symbol")
        user_stock = lookup(symbol)
        if user_stock == None:
            return apology("symbol invalid !!!", 400)
        # Show # Show user_stock
        else:
            return render_template(
                "user_quoted.html",
                name=user_stock["name"],
                price=user_stock["price"],
                symbol=user_stock["symbol"],
            )
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    user_name = request.form.get("username")
    pass_word = request.form.get("password")
    con = request.form.get("confirmation")

    if request.method == "POST":
        # were fields properly submitted ?
        if not user_name or not pass_word or not con:
            return apology("empty !!!", 400)
        # password and confirmation match ?
        elif pass_word != con:
            return apology("passwords do not match", 400)
        # make sure username is not already taken
        elif db.execute("SELECT * FROM users WHERE username = ?", user_name):
            return apology("username taken", 400)
        # Add to database
        else:
            hash_pass = generate_password_hash(pass_word)
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", user_name, hash_pass
            )
            return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    row = db.execute(
        "SELECT symbol FROM portfolios WHERE user_id = ?", session["user_id"]
    )
    if request.method == "POST":
        # make sure symbol is valid
        user_stock = lookup(request.form.get("symbol"))
        if user_stock == None:
            return apology("must chose a symbol !!!", 400)

        # make sure number of shares is numeric
        elif not request.form.get("shares").isdigit():
            return apology("number of shares invalid !!!", 400)

        # make sure number of shares is more than zero
        elif int(request.form.get("shares")) <= 0:
            return apology("number of shares invalid !!!", 400)

        # make sure number of shares is valid
        elif (
            int(request.form.get("shares"))
            > db.execute(
                "SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                request.form.get("symbol"),
            )[0]["shares"]
        ):
            return apology("invalid number of shares", 400)
        else:
            # Update history
            shares = int(request.form.get("shares"))
            db.execute(
                "INSERT INTO history (user_id, symbol, name, shares, price, action) VALUES(?, ?, ?, ?, ?, ?)",
                session["user_id"],
                user_stock["symbol"],
                user_stock["name"],
                shares,
                user_stock["price"],
                "sell",
            )

            # Update portfolio
            row = db.execute(
                "SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                user_stock["symbol"],
            )
            if len(row) == 1:
                sh = int(request.form.get("shares"))
                db.execute(
                    "UPDATE portfolios SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                    sh,
                    session["user_id"],
                    user_stock["symbol"],
                )
            # If the users'stock have zero shares, remove it
            db.execute(
                "DELETE FROM portfolios WHERE shares = 0 AND user_id = ? AND symbol = ?",
                session["user_id"],
                user_stock["symbol"],
            )
            

            # Increas cashed
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?",
                user_stock["price"] * int(request.form.get("shares")),
                session["user_id"],
            )

            # Redirect user
            return redirect("/")
    return render_template("sell.html", rows=row)


@app.route("/append", methods=["GET", "POST"])
@login_required
def append():
    """Add user's cash"""
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[
        0
    ]["cash"]
    if request.method == "POST":
        # make sure amount is numeric
        if not request.form.get("amount").isdigit():
            return apology("invalid !!", 400)

        # Ensure amount is more than zero
        elif int(request.form.get("amount")) <= 0:
            return apology("invalid !!", 400)

        # Update user_cash
        else:
            db.execute(
                "UPDATE users SET cash = cash  ? WHERE id = ?",
                request.form.get("amount"),
                session["user_id"],
            )
            return redirect("/")

    return render_template("append.html", cash=user_cash)
