import json
import cherrypy
from _college_database import _college_database

class ActController(object):

	def __init__(self,cdb=None):
		self.cdb = cdb
	
	def GET_KEY(self, key):
		output = {"result" : "success"}
		output["college"]=self.cdb.get_by_act(key)
		j = json.dumps(output)
		return j
