from _college_database import _college_database
import unittest

class TestMovieDatabase(unittest.TestCase):
        """unit tests for OO API"""

        #@classmethod
        #def setUpClass(self):
        cdb = _college_database()

        def reset_data(self):
                "reset data is required because we cannot promise an order of test case execution"
                self.cdb.delete_all()
                self.cdb.load_all('data.csv')

        def test_get_by_state(self):
                self.reset_data()
                state = "IN"
                colleges = self.cdb.get_by_state(state)
                self.assertEquals(colleges[59], 'University of Notre Dame')

        def test_get_by_state_null(self):
                self.reset_data()
                state = self.cdb.get_by_state("NCAA")
                self.assertEquals(state, None)

        def test_get_by_city(self):
                self.reset_data()
                city = "Notre Dame"
                colleges = self.cdb.get_by_city(city)
                self.assertEquals(colleges[1], 'University of Notre Dame')

        def test_get_by_city_null(self):
                self.reset_data()
                city = self.cdb.get_by_city("NCAA")
                self.assertEquals(city, None)

        def test_get_by_region(self):
                self.reset_data()
                region = "3"
                colleges = self.cdb.get_by_region(region)
                self.assertEquals(colleges[238], 'University of Notre Dame')

        def test_get_by_region_null(self):
                self.reset_data()
                region = self.cdb.get_by_region("NCAA")
                self.assertEquals(region, None)

        def test_get_by_act(self):
                self.reset_data()
                act = "33"
                colleges = self.cdb.get_by_act(act)
                self.assertEquals(colleges[60], 'University of Notre Dame')

        def test_get_by_sat(self):
                self.reset_data()
                sat = "1455"
                colleges = self.cdb.get_by_sat(sat)
                self.assertEquals(colleges[28], 'University of Notre Dame')
	
if __name__ == "__main__":
    unittest.main()

