# Andrew Bub, Harry Gebremedhin, and Molly Pierce
# December 1, 2017
# CSE30332 - Final Project : Webserver
# main.py

import cherrypy
import json
from resetcont import ResetController
from collegescont import CollegesController
from statecont import StateController
from citycont import CityController
from regioncont import RegionController
from satcont import SatController
from actcont import ActController
from costcont import CostController
from popcont import PopController
from namescont import NamesController
from resultscont import ResultController
from optionscont import OptionsController
from _college_database import _college_database 

#implementation of CORS

def CORS():
	cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"
	cherrypy.response.headers["Access-Control-Allow-Methods"] = "GET, PUT, POST, DELETE"
	cherrypy.response.headers["Access-Control-Allow-Credentials"] = "*"

def start_service():
	#initialization of database objects
	cdb = _college_database()
	myreset = ResetController(cdb)
	mycolleges = CollegesController(cdb)
	mystates = StateController(cdb)
	mycity = CityController(cdb)
	myregions = RegionController(cdb)
	mysat = SatController(cdb)
	myact = ActController(cdb)
	mycost = CostController(cdb)
	mypop = PopController(cdb)
	mynames = NamesController(cdb)
	myresults = ResultController(cdb)
	myoptions = OptionsController()

	#initialization of controllers
	dispatcher = cherrypy.dispatch.RoutesDispatcher()

	#dispatcher connections
	dispatcher.connect('reset_put', '/reset/', controller=myreset, action='PUT', conditions=dict(method=['PUT']))
	dispatcher.connect('reset_put_key', '/reset/:key', controller=myreset, action='PUT_KEY', conditions=dict(method=['PUT']))
	dispatcher.connect('colleges_get', '/colleges/', controller=mycolleges, action='GET', conditions=dict(method=['GET']))	
	dispatcher.connect('colleges_get_key', '/colleges/:key', controller=mycolleges, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('colleges_put_key', '/colleges/:key', controller=mycolleges, action='PUT_KEY', conditions=dict(method=['PUT']))	
	dispatcher.connect('colleges_delete', '/colleges/', controller=mycolleges, action='DELETE', conditions=dict(method=['DELETE']))
	dispatcher.connect('colleges_delete_key', '/colleges/:key', controller=mycolleges, action='DELETE_KEY', conditions=dict(method=['DELETE']))
	dispatcher.connect('states_get_key', '/states/:key', controller=mystates, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('city_get_key', '/city/:key', controller=mycity, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('regions_get_key', '/regions/:key', controller=myregions, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('sat_get_key', '/sat/:key', controller=mysat, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('act_get_key', '/act/:key', controller=myact, action='GET_KEY', conditions=dict(method=['GET']))	
	dispatcher.connect('cost_get_key', '/cost/:key', controller=mycost, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('pop_get_key', '/pop/:key', controller=mypop, action='GET_KEY', conditions=dict(method=['GET']))
	dispatcher.connect('names_get', '/names/', controller=mynames, action='GET', conditions=dict(method=['GET']))
	dispatcher.connect('results_put', '/results/', controller=myresults, action='PUT', conditions=dict(method=['PUT']))
	dispatcher.connect('options_put', '/results/', controller=myoptions, action='OPTIONS', conditions=dict(method=['OPTIONS']))
	
	#configuration
	conf = {"global":{'server.socket_host':'student04.cse.nd.edu',
					  'server.socket_port': 51035},#used Harry's port number 
			"/" :{"request.dispatch": dispatcher, "tools.CORS.on":True}}

	cherrypy.config.update(conf)
	app=cherrypy.tree.mount(None, config=conf)
	cherrypy.quickstart(app)


if __name__=='__main__':
	cherrypy.tools.CORS = cherrypy.Tool("before_finalize",CORS)
	start_service()
	
