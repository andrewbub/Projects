#Reset Controller

import cherrypy
import json
from _college_database import _college_database

class ResetController(object):

	def __init__(self,cdb=None):
		self.cdb=cdb
	
	def PUT(self):
		output = {"result" : "success"}
		self.cdb.delete_all() # delete everything
		self.cdb.load_all("data.csv")# reload from file
		x=json.dumps(output)
		return x



	def PUT_KEY(self, key):
		# 	we need to write a delete with college id function
		#	and also a set_collge with college id function
		output = {"result" : "success"}
		self.cdb.delete_college(key)
		self.cdb.load_all("data.csv")
		j=json.dumps(output)
		return j
		
		
		
		 
