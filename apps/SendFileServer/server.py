# encoding: utf8

from flask import Flask, send_file
from flask_cors import CORS, cross_origin

app = Flask(__name__)
cors = CORS(app)


@app.route('/')
def index():
    return '<h1>Download file</h1>'


@app.route('/download')
def download():
    return send_file('/home/pavel/workspace/tmp/test_file', mimetype='text/plain')


@app.route('/test_file')
def test_file():
    print 'file was requested'
    return send_file('test_file', mimetype='text/plain')


@app.route('/ball')
@cross_origin()
def ball():
    print 'file was requested'
    return send_file('ball.png', mimetype='image/png')


if __name__ == '__main__':
    app.run(debug=True, port=9999)
