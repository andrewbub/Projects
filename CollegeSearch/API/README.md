OO API README

For our OO API, we parse through our CSV datafile using the csv library to extract every college's name, city, state, 
average ACT score, average SAT score, cost, undergraduate population, admission rate, region, website, and financial aid website.
This information is all loaded in the load_all method

We then made dictionaries, most of which have the value being a list of colleges that have the same key, whether that is the key
of the state, the city, the region, the act score, or the sat score. Another dictionary has the name as the key, and has a list
of all the other elements of the associated college.

We then have many get methods, in which a user will input the information they want to filter their search of the colleges, 
whether that is the state, city, region, act, or sat scores. Most of these get methods are simple, and just return the list of
the colleges that have that key value. The ACT and SAT methods are different. They return all a list of all colleges that have
an average score that is 3 or 200 points below your average score, respectively.

Finally, there is a delete_all method, which is used in the reset function of the test file
