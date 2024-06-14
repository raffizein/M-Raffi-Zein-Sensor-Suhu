from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid data"}), 400

    temperature = data.get('temperature')
    humidity = data.get('humidity')

    if temperature is None or humidity is None:
        return jsonify({"error": "Missing temperature or humidity"}), 400

    print(f"Received data: Temperature={temperature}, Humidity={humidity}")

    return jsonify({"status": "success", "temperature": temperature, "humidity": humidity}), 200

if __name__ == '_main_':
    app.run(host='192.168.1.5', port=5000)