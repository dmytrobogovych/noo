import flask
from flask import request, jsonify
import mysql.connector

# Server software version
BACKEND_VERSION = '0.0.1'

app = flask.Flask(__name__)
app.config["DEBUG"] = True


@app.route('/', methods=['GET'])
def home():
    return "<p>Litt backend </p>"

@app.route('/version', methods=['GET'])
def version():
    return jsonify({'version': BACKEND_VERSION})

@app.route('/users', methods=['GET'])
def users():

    return None

@app.route('/users', methods=['POST'])
def user_post():
    return None


app.run()
