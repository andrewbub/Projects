import cherrypy
import json
import sys
from _college_database import _college_database

class ResultController(object):
	
	def __init__(self, cdb=None):
		self.cdb = cdb
	
	def PUT(self):
		output = {"result" : "success"}
		self.cdb.delete_all()
		self.cdb.load_all('data.csv')
		data = cherrypy.request.body.read().decode()
		formdata = json.loads(data)
		###-------saving form data sent from html page-------###
		city = formdata["city"]
		state = formdata["state"]
		region = formdata["regions"]
		sat = formdata["sat"]
		act = formdata["act"]
		cost = formdata["cost"]
		size = formdata["size"]
		x = 100000
		shortlist = []
		filters =[]
		###--------------------------------------------------###
		if city != 'null':
			citylist = self.cdb.get_by_city(city)
			filters.append(citylist)
			if len(citylist) < x:
				x = len(citylist)
				shortlist = citylist

		if state != 'null':
			statelist = self.cdb.get_by_state(state)
			filters.append(statelist)
			if len(statelist) < x:
				x = len(statelist)
				shortlist = statelist

		if region != 'null':
			regionlist = self.cdb.get_by_region(region)
			filters.append(regionlist)
			if len(regionlist) < x:
				x = len(regionlist)
				shortlist = regionlist

		if sat != 'null':
			satlist = self.cdb.get_by_sat(sat)
			filters.append(satlist)
			if len(satlist) < x:
				x = len(satlist)
				shortlist = satlist

		if act != 'null':
			actlist = self.cdb.get_by_act(act)
			filters.append(actlist)
			if len(actlist) < x:
				x = len(actlist)
				shortlist = actlist

		if size != None:
			sizelist = self.cdb.get_by_pop(size)
			filters.append(sizelist)
			if len(sizelist) < x:
				x = len(sizelist)
				shortlist = sizelist

		if cost != None:
			costlist = self.cdb.get_by_cost(cost)
			filters.append(costlist)
			if len(costlist) < x:
				x = len(costlist)
				shortlist = costlist
		
		for school in shortlist:
			for f in filters:
				if school in f:
					continue
				else:
					shortlist.remove(school)
					break
		
		output["colleges"] = shortlist
		response = json.dumps(output)
		return response 	


		
			
