#Names Controller

import cherrypy
import json
from _college_database import _college_database 

class NamesController(object):

	def __init__(self, cdb=None):
		self.cdb=cdb

	def GET(self):
		output = {"result" : "success"}
		output["college"] = self.cdb.names
		x = json.dumps(output)
		return x

