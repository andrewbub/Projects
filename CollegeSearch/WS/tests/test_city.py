import unittest
import requests
import json

class TestCity(unittest.TestCase):

    PORT_NUM = '51035' #change port number to match your port number
    print("Testing Port number: ", PORT_NUM)
    SITE_URL = 'http://student04.cse.nd.edu:' + PORT_NUM
    CITY_URL = SITE_URL + '/city/'
    RESET_URL = SITE_URL + '/reset/'

    def reset_data(self):
        m = {}
        r = requests.put(self.RESET_URL, data = json.dumps(m))

    def is_json(self, resp):
        try:
            json.loads(resp)
            return True
        except ValueError:
            return False

    def test_city_get(self):
        #print('Test city_get')
        self.reset_data()
        key = "Notre Dame"
        r = requests.get(self.CITY_URL + str(key))
        self.assertTrue(self.is_json(r.content.decode('utf-8')))
        resp = json.loads(r.content.decode('utf-8'))
        self.assertEqual(resp['college'][1], 'University of Notre Dame')

if __name__ == "__main__":
    unittest.main()

