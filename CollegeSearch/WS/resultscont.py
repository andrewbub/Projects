import cherrypy
import json
import sys
from _college_database import _college_database

class ResultController(object):
	
	def __init__(self, cdb=None):
		self.cdb = cdb
	
	def PUT(self):
		output = {"result" : "success"}
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
		if city != None:
			citylist = self.cdb.get_by_city(city)
			filters.append(citylist)
			if citylist.size() < x:
				x = citylist.size()
				shortlist = citylist

		if state != None:
			statelist = self.cdb.get_by_state(state)
			filters.append(statelist)
			if statelist.size() < x:
				x = statelist.size()
				shortlist = statelist

		if region != None:
			regionlist = self.cdb.get_by_region(region)
			filters.append(regionlist)
			if regionlist.size() < x:
				x = regionlist.size()
				shortlist = regionlist

		if sat != None:
			satlist = self.cdb.get_by_sat(sat)
			filters.append(satlist)
			if satlist.size() < x:
				x = satlist.size()
				shortlist = satlist

		if act != None:
			actlist = self.cdb.get_by_act(act)
			filters.append(actlist)
			if actlist.size() < x:
				x = actlist.size()
				shortlist = actlist

		if size != None:
			sizelist = self.cdb.get_by_pop(size)
			filters.append(sizelist)
			if sizelist.size() < x:
				x = sizelist.size()
				shortlist = sizelist

		if cost != None:
			costlist = self.cdb.get_by_cost(cost)
			filters.append(costlist)
			if costlist.size() < x:
				x = costlist.size()
				shortlist = costlist
		
		for school in shortlist:
			for f in filters:
				if school in f:
					continue
				else:
					shortlist.remove(school)
		
		output["colleges"] = shortlist
		response = json.dumps(output)
		return response 	


		
			
