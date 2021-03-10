from sanic import Sanic
from sanic.response import json
from sanic import response
from pyArango.connection import *
import json

app = Sanic("App Name")

conn = Connection(arangoURL="http://localhost:1234",username="root", password="doorandy123")
db = conn["interruptor"]
@app.route("/guardarData", methods=["POST"])
async def echo(request):
	if request.json:
		doc=(request.json)
		bind = {"doc": doc}
		aql = "INSERT @doc INTO estados LET newDoc = NEW RETURN newDoc"
		queryResult = db.AQLQuery(aql, bindVars=bind)
		return json(request.json)
	return json({"R":"NO fue un json"})
	
@app.route('/obtenerData',methods=['GET'])
async def estados(request):
	aql = 'FOR doc IN estados RETURN doc'
	queryResult = db.AQLQuery(aql, rawResults = True, batchSize=100)
	res = [a for a in queryResult]
	return response.json(res)

if __name__ == "__main__":
	app.run(host="0.0.0.0", port=8000)
