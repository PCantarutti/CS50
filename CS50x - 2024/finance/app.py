import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, is_int

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
    wallet = db.execute(
        "SELECT * FROM wallet WHERE user_id = ? ORDER BY total DESC", session["user_id"])
    wallet_total = db.execute("SELECT total FROM wallet WHERE user_id = ?", session["user_id"])
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    cash = user[0]["cash"]

    total_cash = 0

    for stock in wallet_total:
        total_cash += stock["total"]

    return render_template("index.html", wallet=wallet, cash=cash, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("missing symbol", 400)

        elif not shares:
            return apology("missing shares", 400)

        elif not is_int(shares):
            return apology("fractional not supported", 400)

        elif int(shares) <= 0:
            return apology("share can't be a negative number or zero!", 400)

        quote_lookup = lookup(symbol)

        if not quote_lookup:
            return apology("invalid symbol", 400)
        else:
            denero = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = denero[0]["cash"]
            total = int(shares) * quote_lookup["price"]

        if cash < total:
            return apology("not enought money", 400)
        else:
            transaction_id = db.execute(
                "SELECT transaction_id FROM wallet WHERE symbol = ? AND user_id = ?", quote_lookup['symbol'], session["user_id"])

            if not transaction_id:
                db.execute("INSERT INTO wallet (user_id, symbol, shares, price, total) VALUES(?, ?, ?, ?, ?)",
                           session["user_id"], quote_lookup['symbol'], int(shares), quote_lookup['price'], total)
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           cash - total, session["user_id"])
                db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                           session["user_id"], quote_lookup['symbol'], ("+" + str(shares)), quote_lookup['price'])

                return redirect("/")
            elif transaction_id:
                transaction_id = transaction_id[0]["transaction_id"]
                shares_update = db.execute(
                    "SELECT shares FROM wallet WHERE transaction_id = ? AND user_id = ?", transaction_id, session["user_id"])
                shares_update = shares_update[0]["shares"]
                db.execute("UPDATE wallet SET shares = ? WHERE transaction_id = ? AND user_id = ?", int(
                    shares) + shares_update, transaction_id, session["user_id"])
                db.execute("UPDATE wallet SET price = ? WHERE transaction_id = ? AND user_id = ?",
                           quote_lookup['price'], transaction_id, session["user_id"])
                db.execute("UPDATE wallet SET total = ? WHERE transaction_id = ? AND user_id = ?", (int(
                    shares) + shares_update) * quote_lookup['price'], transaction_id, session["user_id"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           cash - total, session["user_id"])
                db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                           session["user_id"], quote_lookup['symbol'], ("+" + str(shares)), quote_lookup['price'])

                return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute(
        "SELECT * FROM history WHERE user_id = ? ORDER BY transacted DESC", session["user_id"])

    return render_template("history.html", history=history)


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
        symbol = symbol.strip()

        if not symbol:
            return apology("missing symbol", 400)

        quote_lookup = lookup(symbol)

        if not quote_lookup:
            return apology("invalid symbol", 400)
        else:
            return render_template("quoted.html", symbol=quote_lookup)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not confirmation:
            return apology("must confirm password", 400)

        elif password != confirmation:
            return apology("passwords don't match", 400)

        try:
            hashed_password = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed_password)
        except ValueError:
            return apology("username taken", 400)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    symbol = db.execute("SELECT * FROM wallet WHERE user_id = ?", session["user_id"])

    if request.method == "POST":
        qtd = request.form.get("shares")
        qtd = int(qtd)
        selected_symbol = request.form.get("symbol")

        if not qtd:
            return apology("missing shares", 400)

        elif not selected_symbol:
            return apology("missing symbol", 400)

        elif not is_int(qtd):
            return apology("fractional not supported", 400)

        elif int(qtd) <= 0:
            return apology("share can't be a negative number or zero!", 400)

        else:
            shares_qtd = db.execute(
                "SELECT shares FROM wallet WHERE symbol = ? AND user_id = ?", selected_symbol, session["user_id"])
            shares_qtd = shares_qtd[0]["shares"]
            atual_price = db.execute(
                "SELECT total FROM wallet WHERE symbol = ? AND user_id = ?", selected_symbol, session["user_id"])
            atual_price = atual_price[0]["total"]
            cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
            quote_lookup = lookup(selected_symbol)
            quote_price = quote_lookup["price"]
            price = quote_price * qtd
            cash = cash[0]["cash"]
            new_cash = cash + price

            if shares_qtd < qtd:
                return apology("not enought in your wallet", 400)

            elif shares_qtd == qtd:
                db.execute("DELETE FROM wallet WHERE symbol = ? AND user_id = ?",
                           selected_symbol, session["user_id"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
                db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                           session["user_id"], quote_lookup['symbol'], ("-" + str(qtd)), quote_lookup['price'])
                return redirect("/")

            elif shares_qtd > qtd:
                db.execute("UPDATE wallet SET shares = ? WHERE symbol = ? AND user_id = ?",
                           shares_qtd - qtd, selected_symbol, session["user_id"])
                db.execute("UPDATE wallet SET total = ? WHERE symbol = ? AND user_id = ?",
                           (atual_price - price), selected_symbol, session["user_id"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
                db.execute("INSERT INTO history (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                           session["user_id"], quote_lookup['symbol'], ("-" + str(qtd)), quote_lookup['price'])
                return redirect("/")

    return render_template("sell.html", symbol=symbol)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    """perfil settings"""
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    wallet = db.execute("SELECT * FROM wallet WHERE user_id = ?", session["user_id"])
    username = user[0]["username"]
    cash = user[0]["cash"]
    value = 0

    for share in wallet:
        value += share["total"]

    return render_template("settings.html", username=username, cash=cash, value=round(value, 2))


@app.route("/passwordchange", methods=["GET", "POST"])
@login_required
def passwordchange():
    """password change"""

    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("current")
        ):
            return apology("invalid password", 403)

        # Ensure password was submitted
        if not password:
            return apology("must provide password", 403)

        # Ensure password confirmation was submitted
        elif not confirmation:
            return apology("must confirm password", 403)

        elif password != confirmation:
            return apology("passwords don't match", 403)

        try:
            hashed_password = generate_password_hash(password)
            db.execute("UPDATE users SET hash = ? WHERE id = ?",
                       hashed_password, session["user_id"])
        except ValueError:
            return apology("error", 404)

        # Redirect user to home page
        return redirect("/settings")

    return render_template("passwordchange.html")
