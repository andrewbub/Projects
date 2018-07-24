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
		self.cost = {} #dictionary with cost and then list of colleges
		self.pop = {} # dictionary with population and then list of colleges
		self.names = [] # list of all names
		self.load_all('data.csv')
		self.get_all_names()

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

			# self.pop
			if pop in self.pop:
				self.pop[pop].append(name)
			else:
				self.pop[pop]=[name]

			#self.cost 
			if cost in self.cost:
				self.cost[cost].append(name)
			else:
				self.cost[cost] = [name]

	# -------------------------------------------------------------------------------------
	def get_all_names(self):
		for name in self.college:
			self.names.append(name)

		return self.names

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
			if int(score) <= act + 1 and (act-3) <= int(score):
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
			if int(score) <= sat + 100 and (sat-200) <= int(score):
				for school in self.sat[score]:
					colleges.append(school)
		
		return colleges

	# -------------------------------------------------------------------------------------
	def delete_all(self):
		self.college = {}
		self.state = {}
		self.city = {}
		self.region = {}
		self.act = {}
		self.sat = {}
		self.cost = {}
		self.pop = {}
		self.names = []

	# -------------------------------------------------------------------------------------
	def delete_college(self,collegename):

		if collegename in self.college.keys():
			del self.college[collegename]
		else:
			print("")		
			


	# -------------------------------------------------------------------------------------
	def get_by_cost(self, cost):
		colleges = []
		cost = int(cost)
		for amount in self.cost:
			if amount == 'NULL':
				continue
			if int(amount) <= cost:
				for school in self.cost[amount]:
					colleges.append(school)

		return colleges

	# -------------------------------------------------------------------------------------
	def get_by_pop(self, pop):
		colleges = []
		pop = int(pop)
		if pop <= 2000:
			for size in self.pop:
				if size == 'NULL':
					continue
				if int(size) <= 2000:
					for school in self.pop[size]:
						colleges.append(school)
		elif pop <= 15000:
			for size in self.pop:
				if size == 'NULL':
					continue
				if int(size) > 2000 and int(size) <= 15000:
					for school in self.pop[size]:
						colleges.append(school)
		else:
			for size in self.pop:
				if size == 'NULL':
					continue
				if int(size) > 15000:
					for school in self.pop[size]:
						colleges.append(school)

		return colleges

# ---------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------
if __name__ == "__main__":
	cdb = _college_database()

	##### COLLEGES #####
	newDict = cdb.load_all('data.csv')
