#Colleges Controller

import cherrypy
import json
from _college_database import _college_database 

class CollegesController(object):

	def __init__(self, cdb=None):
		self.cdb=cdb

	def GET(self):
		output = {"result" : "success"}
		#outputting everyting in the self.cdb.college dictionary
		for colleges in self.cdb.college:
			output[colleges] = self.cdb.college[colleges]
		x = json.dumps(output)
		return x

	def GET_KEY(self, key):
		output = {"result" : "success"}
		
		#formatting dictionary
		try: 
			output["Name"] = key
			output["City"] = self.cdb.college[key][0]
			output["State"] = self.cdb.college[key][1]
			output["WebURL"] = self.cdb.college[key][2]
			output["FinURL"] = self.cdb.college[key][3]
			output["Region"] = self.cdb.college[key][4]
			output["Admi%"] = self.cdb.college[key][5]
			output["ACT"] = self.cdb.college[key][6]
			output["SAT"] = self.cdb.college[key][7]
			output["Population"] = self.cdb.college[key][8]
			output["Cost"] = self.cdb.college[key][9]
		except Exception as ex:
			output["Name"] 
			output['result'] = 'error'
			output['message'] = 'college does not exist'

		x=json.dumps(output)
		return x

	#for administrative uses only	
	def PUT_KEY(self,key):
		output = {"result" : "success"}
		#the data inputted should be structured the same way as formatted
		#if SAT avg and ACT avg change that affects our self.act and self.sat
		the_body = cherrypy.request.body.read()
		try:
			the_body = json.loads(the_body)
			college = the_body["college"]
			info = the_body["info"]
			for x, i in enumerate(info):
				self.cdb.college[college][x] = i
		
		except Exception as ex:
			output["Name"] = "error"
			output['result'] = 'error'
			output['message'] = str(ex)
		
		return json.dumps(output)

	def DELETE(self):
		output = {"result" : "success"}
		self.cdb.delete_all()
		j = json.dumps(output)
		return j

	def DELETE_KEY(self,key):
		output = {"result" : "success"}
		try:
			self.cdb.delete_college(key)
		except Exception as ex:
			output['result'] = 'error'
			output['message'] = str(ex)

		j=json.dumps(output)
		return j

		

