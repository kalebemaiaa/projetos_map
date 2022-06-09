from flask import Flask, flash, jsonify, redirect, render_template, request, session

app = Flask(__name__)

# @app.route("/movimento", methods=["POST"])
# def movimento():
#     print(request.response)
#     length = request.headers["Content-Length"]
#     data = request.stream.read(length)
#     print(data)
#     print(length)
#     return "cheque mate"

@app.route("/queue", methods = ["GET"])
def queue():
    return redirect("chess.html")

@app.route('/')
def index():
    return render_template("change.html")