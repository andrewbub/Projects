 Web Service README

 The webservice is implemented using the _College_Database OOAPI and cherrypy library. 
 It runs on the student04.cse.nd.edu on the port 51035. We have 7 resources with 7 controller classes. 
 The client can make  certain http requests shown in the restful json specifications. 
 We have PUT and DELETE requests for administrative purposes on the colleges resource in order to update our data whenever there are changes. 
 A client can use GET requests on the differeten resources to obtain information on colleges based on ACT, SAT, Cost, Region, State, or City. 
 The client will get a json formatted string of relevant data pertinent to the query made.  
 