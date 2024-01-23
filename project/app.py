import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///comment.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
def index():
    return render_template("index.html")
@app.route("/01")
def one():
    return render_template("01.html")
@app.route("/02")
def two():
    return render_template("02.html")
@app.route("/03")
def three():
    return render_template("03.html")
@app.route("/04")
def four():
    return render_template("04.html")
@app.route("/05")
def five():
    return render_template("05.html")


@app.route("/greet", methods=["POST"])
def greet():
    if request.method == "POST":
        # Add the user's entry into the database
        result = ""
        if not request.form.get("name"):
            result = "Enter your name !!"
        elif not request.form.get("textarea"):
            result = "Enter your comment !!"
        elif not request.form.get("email"):
            result = "Enter your comment !!"
        else:
            db.execute(
                "INSERT INTO comments (name, text, email) VALUES(?, ?, ?)",
                request.form.get("name"),
                request.form.get("textarea"),
                request.form.get("email"),
            )
        c = db.execute("SELECT name,text FROM comments")
        return render_template("result.html", message=result, coment=c)

    else:
        # Display the entries in the database on index.html
        c = db.execute("SELECT name,text FROM comments")
        return render_template(
            "result.html", message="Successfully registered", coment=c
        )
