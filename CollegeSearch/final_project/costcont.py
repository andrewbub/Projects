import json
import cherrypy
from _college_database import _college_database

class CostController(object):

	def __init__(self,cdb=None):
		self.cdb = cdb
	
	def GET_KEY(self, key):
		output = {"result" : "success"}
		try:
			output["college"]=self.cdb.get_by_cost(key)
		except KeyError as ex:
			output['result'] = 'error'
			output['message'] = str(ex)

		j = json.dumps(output)
		return j 
