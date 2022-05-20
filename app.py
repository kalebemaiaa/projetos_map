import os

# vcs podem remover esta lib cs50 e usar diretamente a lib de SQLLite
# https://docs.python.org/3/library/sqlite3.html
from cs50 import SQL

from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?,?,?)",name,month,day)

        return redirect("/")

    else:
        data = db.execute("SELECT * FROM birthdays")
        data_aniversario = []
        
        for pessoa in data:
            dia = pessoa["day"]
            mes = pessoa["month"]
            birthday = f"{dia} / {mes}"
            data_aniversario.append(birthday)

        return render_template("index.html", data = data, tamanho = len(data), data_aniversario = data_aniversario)


