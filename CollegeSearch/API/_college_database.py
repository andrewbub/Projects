# Andrew Bub, Harry Gebremedhim, & Molly Pierce
# CSE30332 - Final Project: OO API
# November 27, 2017
import csv

class _college_database:

	def __init__(self):
		self.college = {} # dictionary with name as key and all other info 
		self.state= {} # dictionary with state and then list of colleges  
		self.city = {} # dictionary with city and then list of colleges
		self.region = {} # dictionary with region and then list of colleges
		self.act = {} # dictionary with act and then list of colleges
		self.sat = {} # dictionary with sat and then list of colleges
		self.load_all('data.csv')

	# -------------------------------------------------------------------------------------
	
	def load_all(self, college_file):
		f = csv.reader(open(college_file))
		for line in f:
			# separate fields and store them into variables
			name = line[3] # College Name
			city = line[4] # City college is located in
			state = line[5] #State Abbreviation College is located
			url = line[8]  #College Website
			furl = line[9] #financial aid website  
			region = line[18] # Region College is located
			adm = line[36] # Admission Rate
			act = line[55] # Average ACT Score
			sat = line[59] # Average SAT Score
			pop = line[290] # Undergrad population
			cost = line[376] # Total Cost per year

			#adding to dictionary

			# self.college
			self.college[name]=[city, state, url, furl, region, adm, act, sat, pop, cost]
			
			# self.state
			if state in self.state:
				self.state[state].append(name)
			else:
				self.state[state]=[name]

			# self.city
			if city in self.city:
				self.city[city].append(name)
			else:
				self.city[city]=[name]

			# self.region
			if region in self.region:
				self.region[region].append(name)
			else:
				self.region[region]=[name]

			# self.act
			if act in self.act:
				self.act[act].append(name)
			else:
				self.act[act]=[name]

			# self.sat
			if sat in self.sat:
				self.sat[sat].append(name)
			else:
				self.sat[sat]=[name]

	# -------------------------------------------------------------------------------------
	def get_by_state(self, state):
		if state in self.state:
			return self.state[state]
		else:
			return None

	# -------------------------------------------------------------------------------------
	def get_by_city(self, city):
		if city in self.city:
			return self.city[city]
		else:
			return None

	# -------------------------------------------------------------------------------------
	def get_by_region(self, region):
		if region in self.region:
			return self.region[region]
		else:
			return None

	# -------------------------------------------------------------------------------------
	# Returns colleges with average ACT score up to 3 points below your average
	def get_by_act(self, act):
		colleges = []
		act = int(act)
		for score in self.act:
			if score == 'NULL':
				continue
			if int(score) <= act and (act-3) <= int(score):
				for school in self.act[score]:
					colleges.append(school)
		
		return colleges

	# -------------------------------------------------------------------------------------
	# Returns colleges with average SAT score up to 200 points below your average
	def get_by_sat(self, sat):
		colleges = []
		sat = int(sat)
		for score in self.sat:
			if score == 'NULL':
				continue
			if int(score) <= sat and (sat-200) <= int(score):
				for school in self.sat[score]:
					colleges.append(school)
		
		return colleges

	# -------------------------------------------------------------------------------------
	def delete_all(self):
		self.colleges = {}
		self.state = {}
		self.city = {}
		self.region = {}
		self.act = {}
		self.sat = {}

# ---------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------
if __name__ == "__main__":
	cdb = _college_database()

	##### COLLEGES #####
	newDict = cdb.load_all('data.csv')
